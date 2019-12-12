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


static GtkStyleContext *style;

static GtkWidget* window;
static GtkWidget* layout;

void New(GtkWidget *w)
{
	// TODO (store them and delete them...)
	ONCELOCK {
		window = gtk_window_new(GTK_WINDOW_POPUP);
		gtk_widget_realize(window);
		layout = gtk_fixed_new();
		gtk_container_add(GTK_CONTAINER(window), layout);
		gtk_widget_realize(layout);
	}
    gtk_container_add(GTK_CONTAINER(layout), w);
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

Image CairoImage(int cx, int cy, Event<cairo_t *> draw)
{
	Image m[2];
	for(int i = 0; i < 2; i++) {
		ImageDraw iw(DPI(cx), DPI(cy));
		iw.DrawRect(0, 0, DPI(cx), DPI(cy), i ? Black() : White());
		cairo_t *cr = iw;
		cairo_surface_set_device_scale(cairo_get_target(cr), 2, 2);
		draw(cr);
		m[i] = iw;
	}
	return RecreateAlpha(m[0], m[1]);
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
		ShowStateColor(GTK_STATE_FLAG_NORMAL);
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

	{
		int x = 100;
		for(int radio = 0; radio < 2; radio++) {
			New(gtk_check_button_new());
		    gtk_style_context_add_class(style, radio ? GTK_STYLE_CLASS_RADIO : GTK_STYLE_CLASS_CHECK);
			for(int st = -1; st <= 1; st++)
				for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
					
					
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
					dword flags = 0;
					flags = st < 0 ? GTK_STATE_FLAG_INCONSISTENT : st > 0 ? GTK_STATE_FLAG_CHECKED : 0;
					flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

					gtk_style_context_set_state(style, static_cast<GtkStateFlags>(flags));


					Image img = CairoImage(16, 16, [&](cairo_t *cr) {
						gtk_render_check(style, cr, 0, 0, 16, 16);
					});
					w.DrawImage(x, 100, img);
					
					x += DPI(20);
				}
		}
	}
	
	{
		int x = 100;
		for(int radio = 0; radio < 1; radio++) {
			New(gtk_button_new());
		    gtk_style_context_add_class(style, radio ? GTK_STYLE_CLASS_RADIO : GTK_STYLE_CLASS_CHECK);
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				
				
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
				dword flags = 0;
				flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_ACTIVE, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

				gtk_style_context_set_state(style, static_cast<GtkStateFlags>(flags));


				Image img = CairoImage(DPI(50), DPI(20), [&](cairo_t *cr) {
					gtk_render_background(style, cr, 0, 0, DPI(50), DPI(20));
					gtk_render_frame(style, cr,  0, 0, DPI(50), DPI(20));
				});
				w.DrawImage(x, 150, img);
				
				x += img.GetWidth() + 5;
			}
		}
	}

	{
		int x = 100;
		for(int radio = 0; radio < 2; radio++) {
			New(radio ? gtk_vscrollbar_new(NULL) : gtk_hscrollbar_new(NULL));
		//	gtk_style_context_add_class(style, GTK_STYLE_CLASS_SCROLLBAR);
		//	gtk_style_context_add_class(style, GTK_STYLE_CLASS_TROUGH);
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				dword flags = 0;
				flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_ACTIVE, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

				gtk_style_context_set_state(style, static_cast<GtkStateFlags>(flags));

				Image img = CairoImage(DPI(50), DPI(20), [&](cairo_t *cr) {
					gtk_render_background(style, cr, 0, 0, DPI(50), DPI(20));
					gtk_render_frame(style, cr,  0, 0, DPI(50), DPI(20));
				});
				w.DrawImage(x, 450, img);
				
				x += img.GetWidth() + 5;
			}
		}
	}

	{
		int x = 100;
		for(int radio = 0; radio < 2; radio++) {
			New(radio ? gtk_vscrollbar_new(NULL) : gtk_hscrollbar_new(NULL));
			gtk_style_context_add_class(style, GTK_STYLE_CLASS_SLIDER);
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				dword flags = 0;
				flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_ACTIVE, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, GTK_STATE_FLAG_NORMAL);

				gtk_style_context_set_state(style, static_cast<GtkStateFlags>(flags));

				Image img = CairoImage(16, 16, [&](cairo_t *cr) {
					gtk_render_slider(style, cr, 0, 0, 16, 16, radio ? GTK_ORIENTATION_VERTICAL	 : GTK_ORIENTATION_HORIZONTAL);
				});
				w.DrawImage(x, 550, img);
				
				x += img.GetWidth() + 5;
			}
		}
	}
}

GUI_APP_MAIN
{
	MyApp().Run();
}
