#include "SearchPoints.h"

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
	RTIMESTOP("Finish");
	
	Index<int> centeri;
	ball.SetCount((int)(2 * sqrt(count)));
	for(Ball& b : ball) { // k-means - assign random points as initial centers
		int ii;
		for(;;) {
			ii = Random(count);
			if(centeri.Find(ii) < 0)
				break;
		}
		centeri.Add(ii);
		b.center.Alloc(dims);
		Copy(b.center, At(ii));
	}

	for(int j = 0; j < GetCount(); j++) { // Assign each point to closest ball
		double qbest = DBL_MAX; // best distance squared
		int    besti = -1; // index of best ball
		
		for(int i = 0; i < ball.GetCount(); i++) {
			double q = SquaredDistance(At(j), ball[i].center);
			if(q < qbest) {
				qbest = q;
				besti = i;
			}
		}
		
		ASSERT(besti >= 0);
		Ball& b = ball[besti];
		b.point.Add(j);
	}

	for(Ball& b : ball) { // calculate new center as average of all points
		Buffer<double> mean(dims, 0);
		for(int i : b.point)
			Add(mean, At(i));
		Mul(mean, 1.0 / b.point.GetCount());
		Copy(b.center, mean);
	}

	for(Ball& b : ball) {
		b.point_distance.SetCount(b.point.GetCount());
		for(int i = 0; i < b.point.GetCount(); i++)
			b.point_distance[i] = Distance(At(b.point[i]), b.center);
		IndexSort(b.point_distance, b.point);
		b.radius = b.point_distance.GetCount() ? b.point_distance.Top() : 0;
	}

#if 0
	for(int j = 0; j < GetCount(); j++) // Also add points that are withing 2x radius
		for(Ball& b : ball) {
			double q = Distance(j, b.center);
			if(q > b.radius && q < 2 * b.radius)
				b.point.Add(j);
		}
#endif
	
#if 1
	for(int i = 0; i < min(3, ball.GetCount()); i++)
		LOG(i << " " << AsString(ball[i]));
#endif
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
