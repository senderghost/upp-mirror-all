#include "SearchPoints.h"

void SearchPoints::DumpCounters()
{
	DUMP(distance_tests);
	DUMP(excluded_balls);
	DUMP(balls_tested);
}

String SearchPoints::AsString(const Ball& b)
{
	return String() << "Ball " << AsString(b.center) << ", radius " << Format("%.1f", b.radius) << ", projected radius: "
	                << Format("%.1f", b.projected_radius) << ", points " << b.point.GetCount();
}

void SearchPoints::Dump(const Ball& b)
{
	LOG(AsString(b));
	String s;
	for(const PI& p : b.point) {
		if(s.GetCount()) s << ", ";
		s << Format("%.1f", p.distance);
	}
	LOG("   subs: " << s);
}

double SearchPoints::SquaredDistance(const double *a, const double *b)
{
	double d = 0;
	for(int i = 0; i < dims; i++)
		d += sqr(a[i] - b[i]);
	return d;
}

void SearchPoints::Add(const double *p)
{
	for(int i = 0; i < dims; i++)
		point.Add(*p++);
	count++;
}

void SearchPoints::Finish()
{
	if(!count)
		return;
	TIMESTOP("Finish");
	projected.SetCount(GetCount());
	for(int i = 0; i < GetCount(); i++)
		projected[i] = Projected(At(i));
	
	Index<int> centeri;
	int ball_count = min(100, max(GetCount() / 2, 1));
	for(int i = 0; i < ball_count; i++) { // Find ball_count random center points of balls
		int ii;
		for(;;) {
			ii = Random(GetCount());
			if(centeri.Find(ii) < 0)
				break;
		}
		centeri.Add(ii);
		ball.Add().center = ii;
	}
	
	for(int j = 0; j < GetCount(); j++) { // Assign each point to closest ball
		double qbest = DBL_MAX; // best distance squared
		int    besti = -1; // index of best ball
		
		for(int i = 0; i < ball.GetCount(); i++) {
			double q = SquaredDistance(j, ball[i].center);
			if(q < qbest) {
				qbest = q;
				besti = i;
			}
		}
		
		ASSERT(besti >= 0);
		PI& p = ball[besti].point.Add();
		p.index = j;
		p.distance = sqrt(qbest);
	}
	
	for(Ball& b : ball) { // Sort all ball points by distance and set radius
		b.projected_radius = 0;
		for(const PI& p : b.point)
			b.projected_radius = max(b.projected_radius, Length(projected[b.center] - projected[p.index]));
		Sort(b.point);
		b.radius = b.point.Top().distance;
		DDUMP(AsString(b));
	}
	
	DDUMP(ball.GetCount());

#if 0
	for(int i = 0; i < min(3, ball.GetCount()); i++)
		Dump(ball[i]);
#endif
}

int gsteps = 0;

bool SearchPoints::FindCloserPoint(const Ball& b, const double *p, int fromi, int& besti, double& qbest)
{ // refine the search for the closest point in the ball
	balls_tested++;
	bool refined = false;
	for(int i = fromi; i < b.point.GetCount(); i++) {
		const PI& pi = b.point[i];
		distance_tests++;
		double q = SquaredDistance(p, At(pi.index));
		if(q < qbest) {
			qbest = q;
			besti = pi.index;
			refined = true;
		}
	}
	return refined;
}

int SearchPoints::Search(const double *p)
{
	if(count == 0)
		return -1;

	Vector<double> ball_distance; // distance of ball i (distance of p, center minus radius)
	
	for(const Ball& b : ball)
		ball_distance.Add(Distance(p, At(b.center)) - b.radius);
	
	Vector<int> ball_order = GetSortOrder(ball_distance); // order from closest ball
	
	int besti = -1; // closest point index
	double qbest = DBL_MAX; // closest point distance squared
	double best = DBL_MAX / 10; // closest point distance
	for(int bi : ball_order) {
		const Ball& b = ball[bi];
		double distance = ball_distance[bi];
		double from_radius = best - distance; // outer ball portion that needs to be tested
		if(from_radius < 0) { // all points from now on are further than best one
			LOG("Stopping: Ball " << AsString(b) << " too far at distance " << ball_distance[bi] << " while closest point at " << best);
			break;
		}
		double min_radius = b.radius - from_radius;
		int fromi = FindLowerBound(b.point, min_radius, [](const PI& pi, double min_radius) { return pi.distance < min_radius; });
		LOG("Ball at distance " << distance << ", center distance " << Distance(p, At(b.center)) << " needs to be tested from radius " << min_radius << " which is from point " << fromi);
		Dump(b);
		if(FindCloserPoint(b, p, fromi, besti, qbest)) {
			best = sqrt(qbest);
			LOG("* New best point: " << besti << " " << AsString(besti) << ", distance: " << best);
		}
	}
		
	LOG("Final best point: " << besti << " " << AsString(besti) << ", distance: " << best);

	return besti;
}

String SearchPoints::AsString(const double *p)
{
	String s = "[";
	for(int i = 0; i < dims; i++) {
		if(i)
			s << ", ";
		s << p[i];
	}
	return s + "]";
}

int ssteps;

int SearchPoints::SimpleSearch(const double *p)
{
	int besti = -1;
	double best = DBL_MAX;
	for(int i = 0; i < count; i++) {
		ssteps++;
		double d = SquaredDistance(At(i), p);
		if(d < best) {
			best = d;
			besti = i;
		}
	}
	
	return besti;
}

void SearchPoints::Dimensions(int n)
{
	count = 0;
	dims = n;
	point.Clear();
}

const int M = 10000;
const int R = 1000;
const int N = 100;

double *RandomPoint()
{
	static double x[20];
	for(int i = 0; i < 20; i++)
		x[i] = Random(R);
	return x;
}

double *Zero()
{
	static double x[20];
	return x;
}

double *MaxR()
{
	static double x[20];
	for(int i = 0; i < 20; i++)
		x[i] = R;
	return x;
}

CONSOLE_APP_MAIN {
	SeedRandom(0);

	SearchPoints sp;
	sp.Dimensions(2);
	for(int i = 0; i < M; i++) {
		sp.Add(RandomPoint());
	}

	DDUMP(sp.Distance(Zero(), MaxR()));
	
	sp.Finish();
	
	
//	for(int i = 0; i < sp.GetCount(); i++)
//		RLOG(sp.AsString(i));
	

	for(int i = 0; i < 1; i++) {
		double *p = RandomPoint();
		RLOG("==========================");
		RLOG(sp.AsString(p));
//		int ii = sp.SimpleSearch(p);
		sp.ClearCounters();
		int fi = sp.Search(p);
		sp.DumpCounters();
//		double d1 = sqrt(sp.SquaredDistance(p, sp.At(ii)));
//		double d2 = sqrt(sp.SquaredDistance(p, sp.At(fi)));
//		RLOG(sp.AsString(p) << ", closest point " << ii << " " << sp.AsString(ii) << ", distance: " << d1
//		      << ", fast: " << fi << " " << sp.AsString(fi) << ", distance: " << d2);

//		ASSERT(d1 == d2);
	}

	RLOG("Total steps " << 2 * gsteps << " vs " << ssteps);
}
