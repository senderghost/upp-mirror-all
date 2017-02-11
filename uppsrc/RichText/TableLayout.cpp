#include "RichText.h"

namespace Upp {

bool RichTable::Reduce(RichContext& rc) const
{
	Rect br = rc.page;
	rc.page.left += format.lm;
	rc.page.right -= format.rm;
	rc.page.Deflate(format.frame);
	if(rc.page.IsEmpty())
		rc.page = br;
	return !rc.page.IsEmpty();
}

const RichTable::TabLayout& RichTable::Realize(RichContext rc) const
{ // Create page layout with header
	if(rc.py != cpy || rc.page != cpage) {
		rc.py.y += format.before;
		if(rc.py.y > rc.page.bottom)
			rc.Page();
		cpage = rc.page;
		cpy = rc.py;
		Reduce(rc);
		clayout.first_page = rc.page;
		RichContext nextpage_rc = rc;
		nextpage_rc.Page();
		clayout.next_page = nextpage_rc.page;
		clayout.hasheader = false;
		clayout.sz = GetSize();
		if(format.header && cell.GetCount()) {
			int hy = min(format.header, cell.GetCount());
			clayout.header = Realize(nextpage_rc, hy); // realize header as if first on next page
			if(clayout.header[0].py.page == clayout.header[hy - 1].pyy.page) { // header fits single page
				Layout x = Realize(rc, cell.GetCount());
				if(cell.GetCount() > hy && rc.py.page != x[hy].py.page) // first header would break the end of page
					rc.Page();
				clayout.hasheader = true; // if it fits, we repeat header on each new page
				int header_height = clayout.header[hy - 1].pyy.y + format.grid - nextpage_rc.py.y;
				clayout.next_page.top += header_height; // so have to reduce the page size for nonheader rows
				rc.page.top += header_height;
			}
		}
		clayout.page0 = rc.py.page;
		(Layout&)clayout = Realize(rc, cell.GetCount());
		if(format.keep && cell.GetCount()) {
			if(clayout[0].py.page != clayout[cell.GetCount() - 1].pyy.page)
				rc.Page();
			clayout.page0 = rc.py.page;
			(Layout&)clayout = Realize(rc, cell.GetCount());
		}
	}
	return clayout;
}

RichTable::Layout RichTable::Realize(RichContext arc, int ny) const
{ // create layout for first ny rows
	Layout tab;
	
	PageY py = arc.py;
	int page0 = arc.py.page;
	Rect first_page = arc.page;
	RichContext nrc = arc;
	nrc.Page();
	Rect next_page = nrc.page;

	int nx = format.column.GetCount();
	tab.row.Alloc(ny);
	for(int i = 0; i < ny; i++)
		tab[i].cell.Alloc(nx);
	
	int sum = 0;
	for(int i = 0; i < nx; i++)
		sum += format.column[i];

	Buffer<int> column_left, column_right;
	column_left.Alloc(nx);
	column_right.Alloc(nx);

	int x = 0;
	int xx = first_page.left;
	int dcx = first_page.Width();
	for(int i = 0; i < nx; i++) {
		column_left[i] = xx;
		x += format.column[i];
		xx = column_right[i] = x * dcx / sum + first_page.left;
	}

	int f2 = format.grid / 2;
	int ff2 = format.grid - f2;

	py.y += format.frame;
	for(int i = 0; i < ny; i++) {
		bool is_next_page = py.page > page0;
		Rect page = is_next_page ? next_page : first_page;
		const Array<RichCell>& row = cell[i];
		PaintRow& pr = tab[i];
		pr.first = i == 0;
		pr.gpy = py;
		if(i)
			py.y += format.grid;
		for(int j = 0; j < nx;) {
			PaintCell& pc = pr[j];
			const RichCell& cell = row[j];
			if(pc.top) {
				pc.page = page;
				pc.page.left = column_left[j];
				pc.page.right = column_right[min(nx - 1, j + cell.hspan)];
				pc.bottom = false;
				int ms = min(ny - 1, i + cell.vspan);
				for(int k = i + 1; k <= ms; k++) {
					PaintCell& pc = tab[k][j];
					pc.top = pc.bottom = false;
				}
				tab[ms][j].bottom = true;
				pc.left = pc.page.left;
				pc.right = pc.page.right;
				if(j)
					pc.page.left += f2;
				if(j + cell.hspan < nx - 1)
					pc.page.right -= ff2;
			}
			j += cell.hspan + 1;
		}
		bool keep = i < format.header || format.keep;
		for(int j = 0; j < nx;) {
			const RichCell& cell = row[j];
			if(pr[j].top && cell.format.keep) {
				keep = true;
				break;
			}
			j += cell.hspan + 1;
		}
		bool span = false;
		for(int j = 0; j < nx;) {
			const RichCell& cell = row[j];
			if(!pr[j].top) {
				span = true;
				break;
			}
			j += cell.hspan + 1;
		}
		if(!span)
			for(int j = 0; j < nx;) {
				const RichCell& cell = row[j];
				PaintCell& pc = pr[j];
				if(pc.top) {
					RichContext rc = is_first_page ? arc : nrc;
					PageY ty = cell.GetTop(rc);
					PageY ky = rc.py;
					if(keep)
						ky = cell.GetHeight(rc);
					if(ty.page != rc.py.page || ky.page != rc.py.page) {
						rc.Page();
						pr.gpy = rc.py;
						pr.first = true;
						break;
					}
				}
				j += cell.hspan + 1;
			}
		pr.py = rc.py;
		for(int j = 0; j < nx;) {
			const RichCell& cell = row[j];
			PaintCell& pc = pr[j];
			if(pc.top) {
				rc.page = pc.page;
				tab[min(ny - 1, i + cell.vspan)][j].hy = cell.GetHeight(rc);
			}
			j += cell.hspan + 1;
		}
		for(int j = 0; j < nx;) {
			const RichCell& cell = row[j];
			if(pr[j].bottom)
				rc.py = max(pr[j].hy, rc.py);
			j += cell.hspan + 1;
		}
		tab.rc = rc;
		pr.pyy = rc.py;
	}
	return tab;
}

}
