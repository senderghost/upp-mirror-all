#include "SearchPoints.h"

void SearchPoints::DumpCounters()
{
	DUMP(distance_tests);
	DUMP(excluded_balls);
	DUMP(balls_tested);
	DUMP(best_count);
	DUMP(best_maxi);
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
	
	Index<int> centeri;
	int ball_count = min(128, max(GetCount() / 2, 1));
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
		Ball& b = ball[besti];
		b.point.Add(j);
		b.radius = max(b.radius, qbest);
	}

	for(Ball& b : ball) {
		b.inner_points = b.point.GetCount();
		b.radius = sqrt(b.radius);
	}

#if 0
	for(int j = 0; j < GetCount(); j++) // Also add points that are withing 2x radius
		for(Ball& b : ball) {
			double q = Distance(j, b.center);
			if(q > b.radius && q < 2 * b.radius)
				b.point.Add(j);
		}
#endif

	for(Ball& b : ball) {
		b.closest.SetCount(ball_count);
		for(int i = 0; i < ball.GetCount(); i++) {
			int besti = -1;
			double qbest = DBL_MAX;
			FindCloserPoint(b, At(ball[i].center), 0, besti, qbest);
			b.closest[i] = besti;
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
		int ii = b.point[i];
		distance_tests++;
		double q = SquaredDistance(p, At(ii));
		if(q < qbest) {
			qbest = q;
			besti = ii;
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
		ball_distance.Add(Distance(p, At(b.center))/* - b.radius*/);
	
	Vector<int> ball_order = GetSortOrder(ball_distance); // order from closest ball
	
	int best_ball = ball_order[0];
	int besti = ball[best_ball].center; // closest point index
	double qbest = DBL_MAX; // closest point distance squared
	double best = DBL_MAX; // closest point distance
	int ii = 0;
	for(int bi : ball_order) {
		const Ball& b = ball[bi];
		DLOG("--- " << ii << ", radius " << b.radius << ", points " << b.point.GetCount()
		            << ", inner points " << b.inner_points
		            << ", from best_center: " << Distance(b.center, ball[best_ball].center)
		            << ", from p: " << Distance(At(b.center), p)
		            << ", from best: " << Distance(b.center, besti)
	                << ", current best: " << best);
		double distance = ball_distance[bi];
		double from_radius = best - distance + b.radius; // outer ball portion that needs to be tested
		if(from_radius < 0) { // all points from now on are further than best one
			LOG("* Stopping: Ball " << AsString(b) << " too far at distance " << ball_distance[bi] << " while closest point at " << best);
			break;
		}
		
		if(best_ball >= 0) {
			Buffer<double> pv = Copy(At(b.center)); // make unit projection vector from best ball to current one
			Sub(pv, At(ball[best_ball].center));
			Unit(pv);
			
			const double *best_center = At(ball[best_ball].center);
			
			auto Project = [&](const double *p) { // project p onto line best_center -> b.center
				return Scalar(pv, Sub(Copy(p), best_center));
			};
			
//			DDUMP(Distance(p, At(b.center)));
//			DDUMP(Distance(p, best_center));
			DDUMP(b.closest[best_ball]);

			const double *closest = At(b.closest[best_ball]);

			DDUMP(Project(p));
			DDUMP(Project(At(besti)));
			DDUMP(Project(closest));
			
			DDUMP(Distance(p, best_center));
			DDUMP(Distance(best_center, closest));
			DDUMP(Distance(p, closest));
			DDUMP(Distance(best_center, At(b.center)) / 2);
		}

		if(FindCloserPoint(b, p, 0, besti, qbest)) {
			best = sqrt(qbest);
			best_count++;
			best_maxi = max(best_maxi, ii);
			best_ball = bi;
			LOG("* " << ii << " New best point: " << besti << ", distance: " << best << ", point radius " << Distance(besti, b.center) << ", " << AsString(besti));
		}
		ii++;
	}
		
//	LOG("Final best point: " << besti << " " << AsString(besti) << ", distance: " << best);

	return besti;
}

int SearchPoints::SimpleSearch(const double *p)
{
	int besti = -1;
	double best = DBL_MAX;
	for(int i = 0; i < count; i++) {
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
