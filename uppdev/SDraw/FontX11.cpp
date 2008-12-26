#include "SDraw.h"

NAMESPACE_UPP

#ifdef PLATFORM_X11

static inline double ft_dbl(int p)
{
    return double(p) / 64.0;
}

bool RenderOutline(const FT_Outline& outline, SDraw& path)
{   
	FT_Vector   v_last;
	FT_Vector   v_control;
	FT_Vector   v_start;
	double x1, y1, x2, y2, x3, y3;
	FT_Vector*  point;
	FT_Vector*  limit;
	char*       tags;
	int   n;         // index of contour in outline
	char  tag;       // current point's state
	int   first = 0; // index of first point in contour
	for(n = 0; n < outline.n_contours; n++) {
		int  last = outline.contours[n];
		limit = outline.points + last;
		v_start = outline.points[first];
		v_last  = outline.points[last];
		v_control = v_start;
		point = outline.points + first;
		tags  = outline.tags  + first;
		tag   = FT_CURVE_TAG(tags[0]);
		if(tag == FT_CURVE_TAG_CUBIC) return false;
		if(tag == FT_CURVE_TAG_CONIC) {
			if(FT_CURVE_TAG(outline.tags[last]) == FT_CURVE_TAG_ON) {
				// start at last point if it is on the curve
				v_start = v_last;
				limit--;
			}
			else {
				// if both first and last points are conic,
				// start at their middle and record its position
				// for closure
				v_start.x = (v_start.x + v_last.x) / 2;
				v_start.y = (v_start.y + v_last.y) / 2;
				v_last = v_start;
			}
			point--;
			tags--;
		}
		path.MoveTo(ft_dbl(v_start.x), -ft_dbl(v_start.y));
		while(point < limit) {
			point++;
			tags++;

			tag = FT_CURVE_TAG(tags[0]);
			switch(tag) {
			case FT_CURVE_TAG_ON:
				path.LineTo(ft_dbl(point->x), -ft_dbl(point->y));
				continue;
			case FT_CURVE_TAG_CONIC:
				v_control.x = point->x;
				v_control.y = point->y;
			Do_Conic:
				if(point < limit) {
					FT_Vector vec;
					FT_Vector v_middle;
					point++;
					tags++;
					tag = FT_CURVE_TAG(tags[0]);
					vec.x = point->x;
					vec.y = point->y;
					if(tag == FT_CURVE_TAG_ON) {
						path.Quadratic(ft_dbl(v_control.x), -ft_dbl(v_control.y),
						               ft_dbl(vec.x), -ft_dbl(vec.y));
						continue;
					}
					if(tag != FT_CURVE_TAG_CONIC) return false;
					v_middle.x = (v_control.x + vec.x) / 2;
					v_middle.y = (v_control.y + vec.y) / 2;
					path.Quadratic(ft_dbl(v_control.x), -ft_dbl(v_control.y),
					               ft_dbl(v_middle.x), -ft_dbl(v_middle.y));
					v_control = vec;
					goto Do_Conic;
				}
				path.Quadratic(ft_dbl(v_control.x), -ft_dbl(v_control.y),
				               ft_dbl(v_start.x), -ft_dbl(v_start.y));
				goto Close;

			default:
				FT_Vector vec1, vec2;
				if(point + 1 > limit || FT_CURVE_TAG(tags[1]) != FT_CURVE_TAG_CUBIC)
				    return false;
				vec1.x = point[0].x; 
				vec1.y = point[0].y;
				vec2.x = point[1].x; 
				vec2.y = point[1].y;
				point += 2;
				tags  += 2;
				if(point <= limit) {
					FT_Vector vec;
					vec.x = point->x;
					vec.y = point->y;
					path.Cubic(ft_dbl(vec1.x), -ft_dbl(vec1.y),
					           ft_dbl(vec2.x), -ft_dbl(vec2.y),
					           ft_dbl(vec.x), -ft_dbl(vec.y));
					continue;
				}
				path.Cubic(ft_dbl(vec1.x), -ft_dbl(vec1.y),
				           ft_dbl(vec2.x), -ft_dbl(vec2.y),
				           ft_dbl(v_start.x), -ft_dbl(v_start.y));
				goto Close;
            }
		}
		path.Close();
	Close:
		first = last + 1; 
    }
	return true;
}

void RenderCharacter(SDraw& sw, int ch, Font fnt)
{
	FontInfo fi = fnt.Info();
	FT_Face face = XftLockFace(fi.GetXftFont());
	int glyph_index = FT_Get_Char_Index(face, ch);
	if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT) == 0)
		RenderOutline(face->glyph->outline, sw);
	XftUnlockFace(fi.GetXftFont());
}

#endif

END_UPP_NAMESPACE
