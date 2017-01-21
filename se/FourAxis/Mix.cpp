#include "Hot4d.h"

void Mix(const Vector<Pt>& left, int li, int lcount,
         const Vector<Pt>& right, int ri, int rcount,
         Vector<Pt>& left_out, Vector<Pt>& right_out)
{ // mixes left and right path into 4D path with equal number of points
	ASSERT(lcount > 0 && rcount > 0);
	
	double ratio = PathLength(left, li, lcount) / PathLength(right, ri, rcount);

	int lh = li + lcount;
	int rh = ri + rcount;

	Pt la = left[li++];
	Pt ra = right[ri++];
	
	left_out.Add(la);
	right_out.Add(ra);
	
	while(li < lh && ri < rh) {
		Pt lb = left[li];
		Pt rb = right[ri];
		
		double ld = Distance(la, lb);
		double rd = ratio * Distance(ra, rb);
		
		if(abs(rd - ld) < ld / 100000) {
			left_out.Add(la = lb);
			li++;
			right_out.Add(ra = rb);
			ri++;
		}
		else
		if(rd < ld) {
			right_out.Add(ra = rb);
			ri++;
			left_out.Add(la = (lb - la) * (rd / ld) + la);
		}
		else {
			left_out.Add(la = lb);
			li++;
			right_out.Add(ra = (rb - ra) * (ld / rd) + ra);
		}
	}
	
	while(li < lh || ri < rh) { // in case that rcount == 1
		left_out.Add(li < lh ? left[li++] : la);
		right_out.Add(ri < rh ? right[ri++] : ra);
	}
}

void MixAll(const Vector<Pt>& left, const Vector<Pt>& right,
            Vector<Pt>& left_out, Vector<Pt>& right_out)
{
	if(left.GetCount() == 0 || right.GetCount() == 0) {
		left_out = clone(left);
		right_out = clone(right);
		return;
	}
	int segment = 0;
	int li = 0;
	int ri = 0;
	DLOG("----------------");
	while(li < left.GetCount() && ri < right.GetCount()) {
		int li0 = li;
		while(li < left.GetCount() && left[li].segment == segment)
			li++;
		int ri0 = ri;
		while(ri < right.GetCount() && right[ri].segment == segment)
			ri++;
		DLOG(segment << " " << li - li0 << " " << ri - ri0);
		int i0 = left_out.GetCount();
		if(li > li0 && ri > ri0) {
			DDUMP(SubRange(left, li0, li - li0));
			DDUMP(SubRange(right, ri0, ri - ri0));
			Mix(left, li0, li - li0, right, ri0, ri - ri0, left_out, right_out);
		}
		while(i0 < left_out.GetCount()) {
			LOG(left_out[i0] << " " << right_out[i0]);
			i0++;
		}
		segment++;
	}
	while(li < left.GetCount()) {
		left_out.Add(left[li++]);
		right_out.Add(right.Top());
	}
	while(ri < right.GetCount()) {
		left_out.Add(left.Top());
		right_out.Add(right[ri++]);
	}
}

void CncPath(Vector<Pt>& left, Vector<Pt>& right, double width, double tower_distance, double left_distance)
{ // adjusts "foam block border" path to "end of the wire" path (at CNC tower)
	ASSERT(left.GetCount() == right.GetCount());
	
	double right_distance = tower_distance - width - left_distance;
	
	for(int i = 0; i < left.GetCount(); i++) {
		Pt& l = left[i];
		Pt& r = right[i];
		
		double yslope = (l.y - r.y) / width;
		l.y += yslope * left_distance;
		r.y -= yslope * right_distance;

		double xslope = (l.x - r.x) / width;
		l.x += xslope * left_distance;
		r.x += xslope * right_distance;
	}
}

void TestMix()
{
	struct TestWin : TopWindow {
		void DrawPath(Draw& w, const Vector<Pt>& path, Color c, Pointf offset) {
			Pointf p = 10 * path[0] + offset;
			for(int i = 1; i < path.GetCount(); i++) {
				Pointf b = path[i] * 10 + offset;
				
				w.DrawLine((int)p.x, (int)p.y, (int)b.x, (int)b.y, 0, c);
				
				w.DrawRect((int)b.x - 1, (int)b.y - 1, 3, 3, c);
				
				p = b;
			}
		}
		
		virtual void Paint(Draw& w) {
			Vector<Pt> left, right;
			
			left << Pt(4, 4) << Pt(10, 10) << Pt(15, 20) << Pt(10, 20);
			right << Pt(4, 4) << Pt(5, 5) << Pt(20, 5);
			
			Vector<Pt> lout, rout;
			lout.Add(left[0]);
			rout.Add(right[0]);
			Mix(left, 0, left.GetCount(), right, 0, right.GetCount(), lout, rout);

			w.DrawRect(GetSize(), White());
			
			DrawPath(w, left, Blue(), Pointf(0, 0));
			DrawPath(w, right, Red(), Pointf(600, 0));

			LOG("+++++++++");

			DDUMP(lout.GetCount());
			DDUMP(lout);
			DDUMP(rout.GetCount());
			DDUMP(rout);
			DrawPath(w, lout, Blue(), Pointf(0, 300));
			DrawPath(w, rout, Red(), Pointf(600, 300));
			LOG("---------");
		}
	};
	
	Vector<Pt> left, right;
	
	auto Test = [](const Vector<Pt>& left, const Vector<Pt>& right) {
		LOG("============================");
		DUMP(left);
		DUMP(right);

		Vector<Pt> lout, rout;
		Mix(left, 0, left.GetCount(), right, 0, right.GetCount(), lout, rout);
		DUMP(lout);
		DUMP(rout);
	};

	left << Pt(4, 4);
	right << Pt(4, 4);
	Test(left, right);
			
	left << Pt(10, 10) << Pt(15, 20) << Pt(10, 10);
	Test(left, right);
	
	right << Pt(5, 5) << Pt(20, 5);
	Test(left, right);

	right << Pt(5, 5) << Pt(20, 5) << Pt(20, 5);
	Test(left, right);

	right << Pt(20, 5);
	Test(left, right);
	
	TestWin().Run();
}