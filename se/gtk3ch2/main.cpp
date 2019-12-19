#include <CtrlLib/CtrlLib.h>

using namespace Upp;

gboolean
draw_gtk(GtkWidget *widget,
         cairo_t   *cr);

struct MyApp : TopWindow {
	int n = 0;

	virtual void Paint(Draw& w);
	virtual void LeftDown(Point, dword) {
		n++;
		Refresh();
	}
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
/*	ONCELOCK {
		window = gtk_window_new(GTK_WINDOW_POPUP);
		gtk_widget_realize(window);
		layout = gtk_fixed_new();
		gtk_container_add(GTK_CONTAINER(window), layout);
		gtk_widget_realize(layout);
	}
    gtk_container_add(GTK_CONTAINER(layout), w);
	gtk_widget_realize(w);
*/	style = gtk_widget_get_style_context(w);
}

Color GetRenderBackgroundColor()
{
    gtk_style_context_add_class(style, GTK_STYLE_CLASS_BACKGROUND);
    
    ImageDraw iw(16, 16);
    gtk_render_background(style, iw, 0, 0, 16, 16);

	return AvgColor(iw);
}

Color GetBackgroundColor(GtkStyleContext *style)
{
    ImageDraw iw(16, 16);
    gtk_render_background(style, iw, 0, 0, 16, 16);
	return AvgColor(iw);
}

Color GetPaperColor(GtkStyleContext *style, int state)
{
	GdkRGBA color;
	gtk_style_context_get_background_color(style, static_cast<GtkStateFlags>(state), &color);
	return Color(int(255 * color.red), int(255 * color.green), int(255 * color.blue));
}

Color GetPaperColor(int state)
{
	GdkRGBA color;
	gtk_style_context_get_background_color(style, static_cast<GtkStateFlags>(state), &color);
	return Color(int(255 * color.red), int(255 * color.green), int(255 * color.blue));
}

Color GetInkColor(GtkStyleContext *style, int state)
{
	GdkRGBA color;
	gtk_style_context_get_color(style, static_cast<GtkStateFlags>(state), &color);
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
		cairo_surface_set_device_scale(cairo_get_target(cr), DPI(1), DPI(1));
		draw(cr);
		m[i] = iw;
	}
	return RecreateAlpha(m[0], m[1]);
}

static void
append_element (GtkWidgetPath *path,
                const char    *selector)
{
  static const struct {
    const char    *name;
    GtkStateFlags  state_flag;
  } pseudo_classes[] = {
    { "active",        GTK_STATE_FLAG_ACTIVE },
    { "hover",         GTK_STATE_FLAG_PRELIGHT },
    { "selected",      GTK_STATE_FLAG_SELECTED },
    { "disabled",      GTK_STATE_FLAG_INSENSITIVE },
    { "indeterminate", GTK_STATE_FLAG_INCONSISTENT },
    { "focus",         GTK_STATE_FLAG_FOCUSED },
    { "backdrop",      GTK_STATE_FLAG_BACKDROP },
    { "dir(ltr)",      GTK_STATE_FLAG_DIR_LTR },
    { "dir(rtl)",      GTK_STATE_FLAG_DIR_RTL },
    { "link",          GTK_STATE_FLAG_LINK },
    { "visited",       GTK_STATE_FLAG_VISITED },
    { "checked",       GTK_STATE_FLAG_CHECKED },
    { "drop(active)",  GTK_STATE_FLAG_DROP_ACTIVE }
  };
  const char *next;
  char *name;
  char type;
  guint i;

  next = strpbrk (selector, "#.:");
  if (next == NULL)
    next = selector + strlen (selector);

  name = g_strndup (selector, next - selector);
  if (g_ascii_isupper (selector[0]))
    {
      GType gtype;
      gtype = g_type_from_name (name);
      if (gtype == G_TYPE_INVALID)
        {
          g_critical ("Unknown type name `%s'", name);
          g_free (name);
          return;
        }
      gtk_widget_path_append_type (path, gtype);
    }
  else
    {
      /* Omit type, we're using name */
      gtk_widget_path_append_type (path, G_TYPE_NONE);
      gtk_widget_path_iter_set_object_name (path, -1, name);
    }
  g_free (name);

  while (*next != '\0')
    {
      type = *next;
      selector = next + 1;
      next = strpbrk (selector, "#.:");
      if (next == NULL)
        next = selector + strlen (selector);
      name = g_strndup (selector, next - selector);

      switch (type)
        {
        case '#':
          gtk_widget_path_iter_set_name (path, -1, name);
          break;

        case '.':
          gtk_widget_path_iter_add_class (path, -1, name);
          break;

        case ':':
          for (i = 0; i < G_N_ELEMENTS (pseudo_classes); i++)
            {
              if (g_str_equal (pseudo_classes[i].name, name))
                {
                  gtk_widget_path_iter_set_state (path,
                                                  -1,
                                                  (GtkStateFlags)(
                                                  gtk_widget_path_iter_get_state (path, -1)
                                                  | pseudo_classes[i].state_flag));
                  break;
                }
            }
          if (i == G_N_ELEMENTS (pseudo_classes))
            g_critical ("Unknown pseudo-class :%s", name);
          break;

        default:
          g_assert_not_reached ();
          break;
        }

      g_free (name);
    }
}

static GtkStyleContext *
create_context_for_path (GtkWidgetPath   *path,
                         GtkStyleContext *parent)
{
  GtkStyleContext *context;

  context = gtk_style_context_new ();
  gtk_style_context_set_path (context, path);
  gtk_style_context_set_parent (context, parent);
  /* Unfortunately, we have to explicitly set the state again here
   * for it to take effect
   */
  gtk_style_context_set_state (context, gtk_widget_path_iter_get_state (path, -1));
  gtk_widget_path_unref (path);

  return context;
}

static void
draw_style_common (GtkStyleContext *context,
                   cairo_t         *cr,
                   gint             x,
                   gint             y,
                   gint             width,
                   gint             height)
{
  GtkBorder margin, border, padding;
  int min_width, min_height;

  gtk_style_context_get_margin (context, gtk_style_context_get_state (context), &margin);
  gtk_style_context_get_border (context, gtk_style_context_get_state (context), &border);
  gtk_style_context_get_padding (context, gtk_style_context_get_state (context), &padding);

  gtk_style_context_get (context, gtk_style_context_get_state (context),
                         "min-width", &min_width,
                         "min-height", &min_height,
                         NULL);
  x += margin.left;
  y += margin.top;
  width -= margin.left + margin.right;
  height -= margin.top + margin.bottom;

  width = MAX (width, min_width);
  height = MAX (height, min_height);

  gtk_render_background (context, cr, x, y, width, height);
  gtk_render_frame (context, cr, x, y, width, height);
}

static GtkStyleContext *
get_style (GtkStyleContext *parent,
           const char      *selector)
{
  GtkWidgetPath *path;

  if (parent)
    path = gtk_widget_path_copy (gtk_style_context_get_path (parent));
  else
    path = gtk_widget_path_new ();

  append_element (path, selector);

  return create_context_for_path (path, parent);
}

static void
query_size (GtkStyleContext *context,
            gint            *width,
            gint            *height)
{
  GtkBorder margin, border, padding;
  int min_width, min_height;

  gtk_style_context_get_margin (context, gtk_style_context_get_state (context), &margin);
  gtk_style_context_get_border (context, gtk_style_context_get_state (context), &border);
  gtk_style_context_get_padding (context, gtk_style_context_get_state (context), &padding);

  gtk_style_context_get (context, gtk_style_context_get_state (context),
                         "min-width", &min_width,
                         "min-height", &min_height,
                         NULL);

  min_width += margin.left + margin.right + border.left + border.right + padding.left + padding.right;
  min_height += margin.top + margin.bottom + border.top + border.bottom + padding.top + padding.bottom;

  if (width)
    *width = MAX (*width, min_width);
  if (height)
    *height = MAX (*height, min_height);
}

static void
draw_style_common (GtkStyleContext *context,
                   cairo_t         *cr,
                   gint             x,
                   gint             y,
                   gint             width,
                   gint             height,
                   gint            *contents_x,
                   gint            *contents_y,
                   gint            *contents_width,
                   gint            *contents_height)
{
  GtkBorder margin, border, padding;
  int min_width, min_height;

  gtk_style_context_get_margin (context, gtk_style_context_get_state (context), &margin);
  gtk_style_context_get_border (context, gtk_style_context_get_state (context), &border);
  gtk_style_context_get_padding (context, gtk_style_context_get_state (context), &padding);

  gtk_style_context_get (context, gtk_style_context_get_state (context),
                         "min-width", &min_width,
                         "min-height", &min_height,
                         NULL);
  x += margin.left;
  y += margin.top;
  width -= margin.left + margin.right;
  height -= margin.top + margin.bottom;

  width = MAX (width, min_width);
  height = MAX (height, min_height);

  gtk_render_background (context, cr, x, y, width, height);
  gtk_render_frame (context, cr, x, y, width, height);

  if (contents_x)
    *contents_x = x + border.left + padding.left;
  if (contents_y)
    *contents_y = y + border.top + padding.top;
  if (contents_width)
    *contents_width = width - border.left - border.right - padding.left - padding.right;
  if (contents_height)
    *contents_height = height - border.top - border.bottom - padding.top - padding.bottom;
}

static void
draw_menu (GtkWidget *widget,
           cairo_t   *cr,
           gint       x,
           gint       y,
           gint       width,
           gint      *height)
{
  GtkStyleContext *menu_context;
  GtkStyleContext *menuitem_context;
  GtkStyleContext *hovermenuitem_context;
  gint menuitem1_height, menuitem2_height, menuitem3_height, menuitem4_height, menuitem5_height;
  gint contents_x, contents_y, contents_width, contents_height;
  gint menu_x, menu_y, menu_width, menu_height;
  gint arrow_width, arrow_height, arrow_size;
  gint toggle_x, toggle_y, toggle_width, toggle_height;

  /* This information is taken from the GtkMenu docs, see "CSS nodes" */
  menu_context = get_style (NULL /*gtk_widget_get_style_context(widget)*/, "menu");
  hovermenuitem_context = get_style (menu_context, "menuitem:hover");
  draw_style_common (menu_context, cr, x, y, width, *height);

  /* Hovered with right arrow */
  draw_style_common (hovermenuitem_context, cr, 10, 10, 200, 40);

  g_object_unref (menu_context);
  g_object_unref (hovermenuitem_context);
}


G_GNUC_BEGIN_IGNORE_DEPRECATIONS

void MyApp::Paint(Draw& w)
{
	w.DrawRect(GetSize(), LtYellow());
	
	w.DrawText(0, 0, AsString(n));
	
	SystemDraw *sw = (SystemDraw *)&w;
	cairo_t *cr = *sw;
	GtkWidget *widget = (GtkWidget *)gtk();

#if 0
	int h = 40;
	draw_menu(widget, cr, 800, 50, 200, &h);
	return;
#endif

#if 0
	auto sw  = dynamic_cast<SystemDraw *>(&w);
	if(sw && gtk()) {
		draw_gtk((GtkWidget *)gtk(), *sw);
		return;
	}
	
#else
	int yy = 100;
	{
		int x = 100;
		for(int radio = 0; radio < 2; radio++) {
			New(gtk_check_button_new());
		    gtk_style_context_add_class(style, radio ? GTK_STYLE_CLASS_RADIO : GTK_STYLE_CLASS_CHECK);
			DDUMP(gtk_widget_path_to_string(gtk_style_context_get_path(style)));
			for(int st = -1; st <= 1; st++)
				for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
					dword flags = 0;
					flags = st < 0 ? GTK_STATE_FLAG_INCONSISTENT : st > 0 ? GTK_STATE_FLAG_CHECKED : 0;
					flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

					gtk_style_context_set_state(style, static_cast<GtkStateFlags>(flags));

					Image img = CairoImage(16, 16, [&](cairo_t *cr) {
						gtk_render_check(style, cr, 0, 0, 16, 16);
					});
					w.DrawImage(x, yy, img);
					
					x += DPI(20);
				}
		}
	}
	yy += DPI(20);

	{
		int x = 50;
		for(int st = -1; st < 2; st++) {
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				GtkStyleContext *button_context;
				GtkStyleContext *check_context;
				gint contents_x, contents_y, contents_width, contents_height;
				
				/* This information is taken from the GtkCheckButton docs, see "CSS nodes" */
				button_context = get_style (NULL, "checkbutton");
				check_context = get_style (button_context, "check");
				
				gtk_style_context_set_scale(check_context, DPI(1));

//				check_context = get_style(get_style(get_style(NULL, "window:dir(ltr).background"), "widget:dir(ltr)"), "checkbutton:dir(ltr).check");
		
				dword flags = 0;
				flags = st < 0 ? GTK_STATE_FLAG_INCONSISTENT : st > 0 ? GTK_STATE_FLAG_CHECKED : 0;
				flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

				gtk_style_context_set_state(check_context, static_cast<GtkStateFlags>(flags));
				
				Image img = CairoImage(16, 16, [&](cairo_t *cr) {
					gtk_render_check (check_context, cr, 0, 0, 16, 16);
				});

				w.DrawImage(x, yy, img);
				
				
				g_object_unref (check_context);
				g_object_unref (button_context);

				x += DPI(20);
			}
		}
	}
	yy += DPI(32);

	{
		int x = 50;
		for(int st = -1; st < 2; st++) {
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				GtkStyleContext *button_context;
				GtkStyleContext *check_context;
				gint contents_x, contents_y, contents_width, contents_height;
				
				/* This information is taken from the GtkCheckButton docs, see "CSS nodes" */
				button_context = get_style (NULL, "radiobutton");
				check_context = get_style (button_context, "radio");
				
				dword flags = 0;
				flags = st < 0 ? GTK_STATE_FLAG_INCONSISTENT : st > 0 ? GTK_STATE_FLAG_CHECKED : 0;
				flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

				gtk_style_context_set_state(check_context, static_cast<GtkStateFlags>(flags));
				
				Image img = CairoImage(16, 16, [&](cairo_t *cr) {
//					draw_style_common (button_context, cr, x, y, *width, *height, NULL, NULL, NULL, NULL);
//					draw_style_common (check_context, cr, x, y, *width, *height,
//					                 &contents_x, &contents_y, &contents_width, &contents_height);
					gtk_render_check (check_context, cr, 0, 0, 16, 16);
				});

				
				g_object_unref (check_context);
				g_object_unref (button_context);

				w.DrawImage(x, yy, img);
				
				x += DPI(32);
			}
		}
	}
	yy += DPI(32);

	{
		int x = 50;
		for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
			GtkStyleContext *button_context;
			GtkStyleContext *check_context;
			gint contents_x, contents_y, contents_width, contents_height;
			
			/* This information is taken from the GtkCheckButton docs, see "CSS nodes" */
			button_context = get_style (NULL, "button");

			gtk_style_context_set_scale(button_context, DPI(1));
			
			dword flags = 0;
			flags = decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

			gtk_style_context_set_state(button_context, static_cast<GtkStateFlags>(flags));
			
			Image img = CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(button_context, cr, 0, 0, 50, 20);
				gtk_render_frame(button_context, cr,  0, 0, 50, 20);
			});
			
			g_object_unref (button_context);

			w.DrawImage(x, yy, img);
			
			x += DPI(55);
		}
	}
	yy += DPI(32);

	{
		int x = 50;
		for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
			GtkStyleContext *scrollbar_context;
			GtkStyleContext *contents_context;
			GtkStyleContext *trough_context;
			GtkStyleContext *slider_context;
			gint slider_width;
			
			dword flags = decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);
	
			  /* This information is taken from the GtkScrollbar docs, see "CSS nodes" */
			scrollbar_context = get_style (NULL, "scrollbar.horizontal.bottom");
			contents_context = get_style (scrollbar_context, "contents");
			trough_context = get_style (contents_context, "trough");
			slider_context = get_style (trough_context, "slider");
			
			auto state = static_cast<GtkStateFlags>(flags);
			gtk_style_context_set_state (scrollbar_context, state);
			gtk_style_context_set_state (contents_context, state);
			gtk_style_context_set_state (trough_context, state);
			gtk_style_context_set_state (slider_context, state);
			
			gtk_style_context_get (slider_context, gtk_style_context_get_state (slider_context),
			                       "min-width", &slider_width, NULL);
			DDUMP(slider_width);
	
			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(scrollbar_context, cr, 0, 0, 50, 20);
				gtk_render_frame(scrollbar_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);

			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(contents_context, cr, 0, 0, 50, 20);
				gtk_render_frame(contents_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);

			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(trough_context, cr, 0, 0, 50, 20);
				gtk_render_frame(trough_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);
	
			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(slider_context, cr, 0, 0, 50, 20);
				gtk_render_frame(slider_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);
			
			g_object_unref (slider_context);
			g_object_unref (trough_context);
			g_object_unref (contents_context);
			g_object_unref (scrollbar_context);
		}
	}
	yy += DPI(32);

	{
		int x = 50;
		for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
			GtkStyleContext *frame_context;
			GtkStyleContext *border_context;
			GtkStyleContext *menubar_context;
			GtkStyleContext *hovered_menuitem_context;
			GtkStyleContext *menuitem_context;
			gint contents_x, contents_y, contents_width, contents_height;
			gint item_width;
			
			/* Menubar background is the same color as our base background, so use a frame */
			frame_context = get_style (NULL, "frame");
			border_context = get_style (frame_context, "border");
			
			/* This information is taken from the GtkMenuBar docs, see "CSS nodes" */
			menubar_context = get_style (NULL, "menubar");
			hovered_menuitem_context = get_style (menubar_context, "menuitem");
			menuitem_context = get_style (menubar_context, "menuitem");
			
			gtk_style_context_set_state (hovered_menuitem_context, GTK_STATE_FLAG_PRELIGHT);

			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(frame_context, cr, 0, 0, 50, 20);
				gtk_render_frame(frame_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);

			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(border_context, cr, 0, 0, 50, 20);
				gtk_render_frame(border_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);

			w.DrawImage(x, yy, CairoImage(50, 20, [&](cairo_t *cr) {
				gtk_render_background(menubar_context, cr, 0, 0, 50, 20);
				gtk_render_frame(menubar_context, cr,  0, 0, 50, 20);
			}));
			x += DPI(55);
	
			w.DrawImage(x, yy, CairoImage(30, 20, [&](cairo_t *cr) {
				gtk_render_background(hovered_menuitem_context, cr, 0, 0, 30, 20);
				gtk_render_frame(hovered_menuitem_context, cr, 0, 0, 30, 20);
			}));
			x += DPI(55);

			w.DrawImage(x, yy, CairoImage(30, 20, [&](cairo_t *cr) {
				gtk_render_background(menuitem_context, cr, 0, 0, 30, 20);
				gtk_render_frame(menuitem_context, cr, 0, 0, 30, 20);
			}));
			x += DPI(55);
			
			g_object_unref (menuitem_context);
			g_object_unref (hovered_menuitem_context);
			g_object_unref (menubar_context);
			g_object_unref (border_context);
			g_object_unref (frame_context);
		}
	}
	yy += DPI(32);
	{
		GtkStyleContext *menu_context;
		GtkStyleContext *menuitem_context;
		GtkStyleContext *disablemenuitem_context;
		GtkStyleContext *separatormenuitem_context;
		gint menuitem1_height, menuitem2_height, menuitem3_height, menuitem4_height, menuitem5_height;
		gint contents_x, contents_y, contents_width, contents_height;
		gint menu_x, menu_y, menu_width, menu_height;
		gint arrow_width, arrow_height, arrow_size;
		gint toggle_x, toggle_y, toggle_width, toggle_height;


		/* This information is taken from the GtkMenu docs, see "CSS nodes" */
		menu_context = get_style (gtk_widget_get_style_context((GtkWidget *)gtk()), "menu"); // TODO: TopWindow?
		GtkStyleContext *hovermenuitem_context = get_style (menu_context, "menuitem:hover");
		hovermenuitem_context = get_style (menu_context, "menuitem:hover");
		menuitem_context = get_style (menu_context, "menuitem");
		disablemenuitem_context = get_style (menu_context, "menuitem");

		int x = 50;
		auto Do = [&](GtkStyleContext *st, int state) {
			gtk_style_context_set_state (st, static_cast<GtkStateFlags>(state));
			w.DrawImage(x, yy, CairoImage(150, 20, [&](cairo_t *cr) {
//				draw_style_common(st, cr, 0, 0, 150, 20);
				gtk_render_background(st, cr, 0, 0, 150, 20);
				gtk_render_frame(st, cr,  0, 0, 150, 20);
			}));
			w.DrawText(x, yy, "Test", StdFont(), GetInkColor(st, state));
			x += DPI(155);
		};
		
		Do(menu_context, 0);
		Do(menuitem_context, 0);
		Do(menuitem_context, GTK_STATE_FLAG_PRELIGHT);
		Do(menuitem_context, GTK_STATE_FLAG_INSENSITIVE);

		  g_object_unref (menu_context);
		  g_object_unref (menuitem_context);
		  g_object_unref (hovermenuitem_context);
		  g_object_unref (disablemenuitem_context);
	}
	yy += DPI(32);
	{
		GtkStyleContext *label = get_style(NULL, "entry");
		GtkStyleContext *selection = get_style(label, "selection");
		
		w.DrawText(50, yy, "Normal", StdFont(), GetInkColor(label, 0));
		w.DrawRect(500, yy, 500, 30, GetBackgroundColor(selection));
		w.DrawText(500, yy, "Selected", StdFont(), GetInkColor(selection, 0));
	}
	yy += DPI(32);

	{
		GtkStyleContext *dialog = get_style(NULL, "window.background");
		
		w.DrawRect(50, yy, 100, 30, GetBackgroundColor(dialog));
//		w.DrawRect(150, yy, 500, 30, GetInkColor(get_style(NULL, "label"), 0));
	}
	yy += DPI(32);

#endif
}

static void gtkStyleChangedCallback(GObject*, GParamSpec*)
{
	DLOG("Style changed");
}

GUI_APP_MAIN
{
    GtkSettings* settings = gtk_settings_get_default();
    g_signal_connect(settings, "notify::gtk-theme-name", G_CALLBACK(gtkStyleChangedCallback), 0);
    g_signal_connect(settings, "notify::gtk-color-scheme", G_CALLBACK(gtkStyleChangedCallback), 0);

	MyApp().Run();
}
