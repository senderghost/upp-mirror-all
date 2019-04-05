#include "SearchPoints.h"

void SearchPoints::DumpCounters()
{
	DUMP(distance_tests);
	DUMP(excluded_balls);
	DUMP(balls_tested);
	DUMP(best_count);
	DUMP(best_maxi);
}

String SearchPoints::AsString(const Ball& b)
{
	return String() << "Ball radius " << Format("%.1f", b.radius) << ", projected size: "
	                << Format("%.1f", abs(b.projected_min - b.projected_max))
	                << ", points " << b.point.GetCount()
	                << ": " << AsString(b.center);
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
	
	MakeV(projector[0]);
	
	Index<int> centeri;
	int ball_count = min(64, max(GetCount() / 2, 1));
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
		b.projected_min = DBL_MAX;
		b.projected_max = 0;
		for(const PI& p : b.point) {
			double projected = Project(p.index);
			b.projected_min = min(b.projected_min, projected);
			b.projected_max = max(b.projected_max, projected);
		}
		Sort(b.point);
		b.radius = b.point.Top().distance;
		
		RTIMING("Closest");
		b.closest.SetCount(ball.GetCount());
		b.closest_distance.SetCount(ball.GetCount());
		for(int i = 0; i < ball.GetCount(); i++) {
			int besti = -1;
			double qbest = DBL_MAX;
			FindCloserPoint(ball[i], At(b.center), 0, besti, qbest);
			b.closest[i] = besti;
			b.closest_distance[i] = sqrt(qbest);
		}
	}
	
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
	
	double projected = Project(p);
	
	int besti = -1; // closest point index
	double qbest = DBL_MAX; // closest point distance squared
	double best = DBL_MAX / 10; // closest point distance
	int best_center = 0;
	double best_radius = 0;
	int best_ball = 0;
	int ii = 0;
	for(int bi : ball_order) {
		DLOG("------------ " << ii << ", current best: " << best << ", best radius: " << best_radius);
		const Ball& b = ball[bi];
		double distance = ball_distance[bi];
		double from_radius = best - distance; // outer ball portion that needs to be tested
		if(from_radius < 0) { // all points from now on are further than best one
			LOG("* Stopping: Ball " << AsString(b) << " too far at distance " << ball_distance[bi] << " while closest point at " << best);
			break;
		}
		double min_radius = b.radius - from_radius;
		double max_radius = b.radius + distance + best;
		int fromi = FindLowerBound(b.point, min_radius, [](const PI& pi, double min_radius) { return pi.distance < min_radius; });
		int toi = FindUpperBound(b.point, max_radius, [](double max_radius, const PI& pi) { return pi.distance > max_radius; });
//		LOG(AsString(b));
		Dump(b);
		LOG("     at distance " << distance << ", center distance " << Distance(p, At(b.center)) << " minmax radius <" << min_radius << ", " << max_radius << ">" << " which is " << fromi << " - " << toi);
		DDUMP(Distance(best_center, b.center));
		DDUMP(b.closest_distance[best_ball]);
		if(besti >= 0) {
			DDUMP(Distance(besti, b.closest[best_ball]));
			DDUMP(Distance(p, At(b.center)));
		}
		if(FindCloserPoint(b, p, fromi, besti, qbest)) {
			best = sqrt(qbest);
			best_count++;
			best_maxi = max(best_maxi, ii);
			best_center = b.center;
			best_radius = b.radius;
			best_ball = bi;
			LOG("* " << ii << " New best point: " << besti << ", distance: " << best << ", point radius " << Distance(besti, b.center) << ", " << AsString(besti));
		}
		DDUMP(Distance(besti, b.center));
		DDUMP(Distance(besti, b.center) - b.radius);
		DDUMP(Distance(besti, b.center) - b.radius + best);
		ii++;
	}
		
//	LOG("Final best point: " << besti << " " << AsString(besti) << ", distance: " << best);

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

void SearchPoints::MakeV(Buffer<double>& v)
{
	v.Alloc(dims);
	double l = 0;
	for(int i = 0; i < GetDimensions(); i++) {
		v[i] = Randomf() - 0.5;
		l += sqr(v[i]);
	}
	l = sqrt(l);
	for(int i = 0; i < GetDimensions(); i++)
		v[i] /= l;
}

double SearchPoints::Project(const double *p, int pi) const
{
	ASSERT(pi >= 0 && pi < 10);
	double r = 0;
	const double *v = projector[pi];
	for(int i = 0; i < GetDimensions(); i++)
		r += v[i] * p[i];
	return r;
}
