#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyApp : TopWindow {
	virtual void Paint(Draw& w);
};

Color AvgColor(const Image& m, const Rect& rr)
{
	int n = rr.GetWidth() * rr.GetHeight();
	if(n <= 0)
		return White();
	int r = 0;
	int g = 0;
	int b = 0;
	for(int y = rr.top; y < rr.bottom; y++)
		for(int x = rr.left; x < rr.right; x++) {
			RGBA c = m[y][x];
			r += c.r;
			g += c.g;
			b += c.b;
		}
	return Color(r / n, g / n, b / n);
}

Color AvgColor(const Image& m, int margin = 0)
{
	return AvgColor(m, Rect(m.GetSize()).Deflated(margin));
}


GtkStyleContext* style;

void New(GtkWidget *w)
{
	// TODO
	gtk_widget_realize(w);
	style = gtk_widget_get_style_context(w);
}

Color GetRenderBackgroundColor()
{
    gtk_style_context_add_class(style, GTK_STYLE_CLASS_BACKGROUND);
    
    ImageDraw iw(16, 16);
    gtk_render_background(style, iw, 0, 0, 16, 16);

	return AvgColor(iw);
}

Color GetPaperColor(int state)
{
	GdkRGBA color;
	gtk_style_context_get_background_color(style, static_cast<GtkStateFlags>(state), &color);
	return Color(int(255 * color.red), int(255 * color.green), int(255 * color.blue));
}

Color GetInkColor(int state)
{
	GdkRGBA color;
	gtk_style_context_get_color(style, static_cast<GtkStateFlags>(state), &color);
	return Color(int(255 * color.red), int(255 * color.green), int(255 * color.blue));
}

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

void MyApp::Paint(Draw& w)
{
	w.DrawRect(GetSize(), LtYellow());
	
	int y = 100;
	auto ShowColor = [&](Color c) {
		w.DrawRect(400, y += 30, 100, 30, c);
	};
	
	auto ShowGetColor = [&]() {
		ShowColor(GetRenderBackgroundColor());
	};
	
	auto ShowStateColor = [&](int state)
	{
		ShowColor(GetPaperColor(state));
		ShowColor(GetInkColor(state));
	};

	{
		New(gtk_window_new(GTK_WINDOW_POPUP));
		ShowGetColor();
	}
	{
		New(gtk_entry_new());
		gtk_style_context_add_class(style, GTK_STYLE_CLASS_ENTRY);
		gtk_style_context_set_state(style, static_cast<GtkStateFlags>(GTK_STATE_FLAG_SELECTED));
		ShowGetColor();
		ShowStateColor(GTK_STATE_FLAG_NORMAL);
		ShowStateColor(GTK_STATE_FLAG_ACTIVE);
		ShowStateColor(GTK_STATE_FLAG_INSENSITIVE);
		ShowStateColor(GTK_STATE_FLAG_SELECTED);
	}

	ImageDraw iw(DPI(16), DPI(16));
	cairo_t *cr = iw;
	
	GtkStyleContext* context = gtk_widget_get_style_context(gtk_check_button_new());
	
    gtk_style_context_add_class(context, /*widgetType == GTK_TYPE_CHECK_BUTTON ? */GTK_STYLE_CLASS_CHECK/* : GTK_STYLE_CLASS_RADIO*/);

/*
    guint flags = 0;
    if (!theme->isEnabled(renderObject) || theme->isReadOnlyControl(renderObject))
        flags |= GTK_STATE_FLAG_INSENSITIVE;
    else if (theme->isHovered(renderObject))
        flags |= GTK_STATE_FLAG_PRELIGHT;
    if (theme->isIndeterminate(renderObject))
        flags |= GTK_STATE_FLAG_INCONSISTENT;
    else if (theme->isChecked(renderObject))
        flags |= GTK_STATE_FLAG_ACTIVE;
    if (theme->isPressed(renderObject))
        flags |= GTK_STATE_FLAG_SELECTED;
*/
	gtk_style_context_set_state(context, static_cast<GtkStateFlags>(GTK_STATE_FLAG_CHECKED));

	gtk_render_check(context, cr, 0, 0, DPI(16), DPI(16));
	
	w.DrawImage(100, 100, iw);

}

GUI_APP_MAIN
{
	MyApp().Run();
}
