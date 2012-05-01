#ifndef _ScatterDraw_DrawingFunctions_h_
#define _ScatterDraw_DrawingFunctions_h_

void DrawLine(Draw &w, double x0, double y0, double x1, double y1, double width, const Color &color);
void DrawLine(Painter &w, double x0, double y0, double x1, double y1, double width, const Color &color);
void DrawLineOpa(Draw& w, const int x0, const int y0, const int x1, const int y1, const int &scale, const double opacity, double thick, const Color &_color, String pattern, const Color &background = Null);	
void DrawLineOpa(Painter& w, const int x0, const int y0, const int x1, const int y1, const int &scale, const double opacity, double thick, const Color &_color, String pattern, const Color &background = Null);	
void FillRectangleOpa(Draw &w, double x0, double y0, double x1, double y1, const int &scale, const double opacity, const Color &background, const Color &color);
void FillRectangleOpa(Painter &w, double x0, double y0, double x1, double y1, const int &scale, const double opacity, const Color &background, const Color &color);
void DrawPolylineOpa(Draw& w, const Vector<Point> &p, const int &scale, const double opacity, double thick, const Color &color, String pattern = "", const Color &background = Null);
void DrawPolylineOpa(Painter& w, const Vector<Point> &p, const int &scale, const double opacity, double thick, const Color &color, String pattern = "", const Color &background = Null);
void FillPolylineOpa(Draw& w, const Vector<Point> &p, const int &scale, const double opacity, const Color &background, const Color &fillColor);
void FillPolylineOpa(Painter& w, const Vector<Point> &p, const int &scale, const double opacity, const Color &background, const Color &fillColor);
void DrawVArrow(Draw &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
void DrawVArrow(Painter &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
void DrawHArrow(Draw &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
void DrawHArrow(Painter &w, double x0, double y0, double x1, double y1, double width, double aWidth, double aHeight, const Color &color);
void DrawText(Draw &w, double x, double y, int angle, const String &text, Font font, Color color);
void DrawText(Painter &w, double x, double y, int angle, const String &text, Font font, Color color);
void Clip(Draw &w, double x, double y, double cx, double cy);
void Clip(Painter &w, double x, double y, double cx, double cy);
void ClipEnd(Draw &w);
void ClipEnd(Painter &w);

#endif
