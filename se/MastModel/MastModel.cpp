#include <Core/Core.h>

using namespace Upp;

class SearchPoints {
	int            dims;
	int            count;
	Vector<double> point;

	struct PI : Moveable<PI> { // point & distance
		int    index;
		double distance;
		
		bool   operator<(const PI& b) const            { return distance < b.distance; }
	};
	
	struct Ball : Moveable<Ball> { // hypersphere with its points
		int        center;
		double     radius;
		Vector<PI> point; // index is index of SerachPoints::point
		Vector<PI> neighbor; // index is index of SerachPoints::ball, distance is closest distance (accounting radius)
	};
	
	Vector<Ball> ball;

	const double *At(int i) const                      { return (const double *)point + dims * i; }
	double  SquaredDistance(const double *a, const double *b);
	double  Distance(const double *a, const double *b) { return sqrt(SquaredDistance(a, b)); }
	double  SquaredDistance(int ai, int bi)            { return SquaredDistance(At(ai), At(bi)); }
	double  Distance(int ai, int bi)                   { return Distance(At(ai), At(bi)); }
	bool    FindCloserPoint(const Ball& b, const double *p, int& besti, double& qbest);

public:
	void Dimensions(int n);
	void Add(const double *p);
	void Finish();

	int  GetDimensions() const                    { return dims; }
	int  GetCount() const                         { return count; }
	const double *operator[](int i) const         { return At(i); }

	int  Search(const double *p);

// performance counters
	int distance_tests = 0; // performance counter
	int excluded_balls = 0;
	int balls_tested = 0;
	
	void ClearCounters() { distance_tests = excluded_balls = balls_tested = 0; }
	void DumpCounters();
	
// diagnostics only...
	int  SimpleSearch(const double *p);
	String AsString(const double *p);
	String AsString(int i)                        { return AsString(At(i)); }
	String AsString(const Ball& b);
	void   Dump(const Ball& b);
};

void SearchPoints::DumpCounters()
{
	DUMP(distance_tests);
	DUMP(excluded_balls);
	DUMP(balls_tested);
}

String SearchPoints::AsString(const Ball& b)
{
	return String() << "Ball " << AsString(b.center) << ", radius " << Format("%.1f", b.radius);
}

void SearchPoints::Dump(const Ball& b)
{
	LOG(AsString(b));
	String s;
	for(const PI& p : b.point) {
		if(s.GetCount()) s << ", ";
		s << AsString(p.index) << ":" << Format("%.1f", p.distance);
	}
	LOG("   subs: " << s);
	s.Clear();
	for(const PI& p : b.neighbor) {
		if(s.GetCount()) s << ", ";
		const Ball& n = ball[p.index];
		s << AsString(n.center) << ", radius " << Format("%.1f", n.radius) << ", distance " << Format("%.1f", p.distance);
	}
	LOG("   neighbor: " << s);
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

	Index<int> centeri;
	int ball_count = min(512, max(GetCount() / 2, 1));
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
	
	for(int j = 0; j < count; j++) { // Assign each point to closest ball
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
		Sort(b.point);
		b.radius = b.point.Top().distance;
		DLOG("=====================");
		DDUMP(b.radius);
		
		int    besti;
		double best = DBL_MAX;
		for(int i = 0; i < b.point.GetCount(); i++) {
			double maxr = 0;
			for(PI& p : b.point)
				maxr = max(maxr, Distance(p.index, b.point[i].index));
			DLOG(i << ": " << maxr);
			if(maxr < best) {
				best = maxr;
				besti = i;
			}
		}
		DDUMP(best);
		
		for(int i = 0; i < ball_count; i++) { // Add and sort all neighbor balls by distance
			if(i != b.center) {
				PI& p = b.neighbor.Add();
				p.index = i;
				p.distance = Distance(i, b.center) - b.radius;
			}
		}
		Sort(b.neighbor);
	}

#if 1
	for(int i = 0; i < min(3, ball.GetCount()); i++)
		Dump(ball[i]);
#endif
}

int gsteps = 0;

bool SearchPoints::FindCloserPoint(const Ball& b, const double *p, int& besti, double& qbest)
{ // refine the search for the closest point in the ball
	balls_tested++;
	bool refined = false;
	for(const PI& pi : b.point) {
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

	double qbest = DBL_MAX; // best distance squared
	int    besti = -1; // index of the ball with closest center
	
	for(int i = 0; i < ball.GetCount(); i++) {
		double q = SquaredDistance(p, At(ball[i].center));
		if(q < qbest) {
			qbest = q;
			besti = i;
		}
	}
		
	ASSERT(besti >= 0);

	const Ball& b = ball[besti];
	LOG("Closest ball, distance to center: " << sqrt(qbest));
	Dump(b);

	besti = 0; // center point of ball has index 0
	FindCloserPoint(b, p, besti, qbest); // find closest point in the ball
	double best = sqrt(qbest); // distance of best from from the ball center
	
	double center_distance = Distance(besti, b.center); // distance from the best point to the center of the ball

	LOG("* Best point in ball: " << besti << " " << AsString(besti) << ", distance: " << best << ", center distance " << center_distance);
	
	for(const PI& pi : b.neighbor) {
		const Ball& nb = ball[pi.index];
		if(pi.distance - center_distance > best) { // starting with this ball, too far to affect the results
			LOG("Neighbor " << AsString(nb) << " too far at distance " << pi.distance);
			break;
		}
		double test_point_distance = Distance(p, At(nb.center)) - nb.radius;
		if(test_point_distance <= best) {
			LOG("Testing neighbor at distance " << pi.distance << ", test point distance " << test_point_distance);
			Dump(nb);
			if(FindCloserPoint(nb, p, besti, qbest)) {
				best = sqrt(qbest);
				center_distance = Distance(besti, b.center);
				LOG("* Best point in neighbor: " << besti << " " << AsString(besti) << ", distance: " << best << ", center distance " << center_distance);
			}
		}
		else {
			excluded_balls++;
			LOG("Neighbor " << AsString(nb) << " at distance " << pi.distance << " too far from test point " << Distance(p, At(nb.center)) - nb.radius);
		}
	}

	LOG("Best point: " << besti << " " << AsString(besti) << ", distance: " << best);

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
	static double x[10];
	for(int i = 0; i < 20; i++)
		x[i] = Random(R);
	return x;
}

CONSOLE_APP_MAIN {
	SeedRandom(0);

	SearchPoints sp;
	sp.Dimensions(20);
	for(int i = 0; i < M; i++) {
		sp.Add(RandomPoint());
	}
	
	sp.Finish();
	
	return;

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
