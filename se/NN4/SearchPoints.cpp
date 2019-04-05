#include "SearchPoints.h"

void SearchPoints::DumpCounters()
{
	RDUMP(distance_tests);
	RDUMP(excluded_points);
	RDUMP(first_count);
}

int SearchPoints::Search(const double *q)
{
	if(count == 0)
		return -1;

	Vector<double> ball_distance; // distance of ball i (distance of p, center minus radius)
	
	for(const Ball& b : ball)
		ball_distance.Add(Distance(q, b.center) - b.radius);
	
	Vector<int> ball_order = GetSortOrder(ball_distance); // order from closest ball
	
	int    besti = -1; // closest point index
	double best2 = DBL_MAX; // closest point distance squared
	double best = DBL_MAX / 10; // closest point distance
	int    foundi;
	
	bool   found_in_first = false;
	
	for(int oi : ball_order) { // search from the closest cluster
		Ball& b = ball[oi];
		double q_center = Distance(q, b.center);
		for(int i = b.point.GetCount(); --i >= 0;) {
			if(q_center > b.point_distance[i] + best) {
				excluded_points += i;
				break;
			}
			distance_tests++;
			double d2 = SquaredDistance(q, At(b.point[i]));
			if(d2 < best2) {
				best2 = d2;
				best = sqrt(d2);
				found_in_first = oi == 0;
				foundi = oi;
			}
		}
	}
	
	RDUMP(foundi);
	if(found_in_first)
		first_count++;
		
//	LOG("Final best point: " << besti << " " << AsString(besti) << ", distance: " << best);

	return besti;
}
