#include <CtrlLib/CtrlLib.h>

using namespace Upp;

gboolean
draw_gtk(GtkWidget *widget,
         cairo_t   *cr);

struct MyApp : TopWindow {
	virtual void Paint(Draw& w);
};

Color AvgColor(const Image& m, int margin)
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
		cairo_surface_set_device_scale(cairo_get_target(cr), DPI(1), DPI(1));
		draw(cr);
		m[i] = iw;
	}
	return RecreateAlpha(m[0], m[1]);
}

static void
append_element2 (GtkWidgetPath *path,
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

static GtkStyleContext *
get_style (GtkStyleContext *parent,
           const char      *selector)
{
  GtkWidgetPath *path;

  if (parent)
    path = gtk_widget_path_copy (gtk_style_context_get_path (parent));
  else
    path = gtk_widget_path_new ();

  append_element2 (path, selector);

  return create_context_for_path (path, parent);
}

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

void MyApp::Paint(Draw& w)
{
	w.DrawRect(GetSize(), LtYellow());
#if 1
	auto sw  = dynamic_cast<SystemDraw *>(&w);
	if(sw && gtk()) {
		draw_gtk((GtkWidget *)gtk(), *sw);
		return;
	}
	
#else
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
		int x = 50;
		for(int st = -1; st < 2; st++) {
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				GtkStyleContext *button_context;
				GtkStyleContext *check_context;
				gint contents_x, contents_y, contents_width, contents_height;
				
				/* This information is taken from the GtkCheckButton docs, see "CSS nodes" */
				button_context = get_style (NULL, "checkbutton");
				check_context = get_style (button_context, "check");
				
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

				w.DrawImage(x, 800, img);
				
				x += DPI(32);
			}
		}
	}

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

				w.DrawImage(x, 800, img);
				
				x += DPI(16);
			}
		}
	}

	{
		int x = 50;
		for(int st = -1; st < 2; st++) {
			for(int m : { CTRL_NORMAL, CTRL_HOT, CTRL_PRESSED, CTRL_DISABLED }) {
				GtkStyleContext *button_context;
				GtkStyleContext *check_context;
				gint contents_x, contents_y, contents_width, contents_height;
				
				/* This information is taken from the GtkCheckButton docs, see "CSS nodes" */
				button_context = get_style (NULL, "button");
				
				dword flags = 0;
				flags = st < 0 ? GTK_STATE_FLAG_INCONSISTENT : st > 0 ? GTK_STATE_FLAG_CHECKED : 0;
				flags |= decode(m, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT, CTRL_PRESSED, GTK_STATE_FLAG_SELECTED, CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE, 0);

				gtk_style_context_set_state(button_context, static_cast<GtkStateFlags>(flags));
				
				Image img = CairoImage(50, 20, [&](cairo_t *cr) {
					gtk_render_background(button_context, cr, 0, 0, 50, 20);
					gtk_render_frame(button_context, cr,  0, 0, 50, 20);
				});
				
				g_object_unref (button_context);

				w.DrawImage(x, 850, img);
				
				x += DPI(55);
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
			DDUMP(gtk_widget_path_to_string(gtk_style_context_get_path(style)));
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
			New(gtk_scrollbar_new(radio ? GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL, NULL));
			DDUMP(gtk_widget_path_to_string(gtk_style_context_get_path(style)));
			gtk_style_context_add_class(style, GTK_STYLE_CLASS_SLIDER);
			DDUMP(gtk_widget_path_to_string(gtk_style_context_get_path(style)));
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

	
#endif
}

GUI_APP_MAIN
{
	MyApp().Run();
}
