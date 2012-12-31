#include <CtrlCore/CtrlCore.h>

#ifdef GUI_GTK

NAMESPACE_UPP

#define LLOG(x)  DLOG(x)

// --------------------------------------------------------------------------------------------

Ptr<Ctrl> sDnDSource;

Ctrl * Ctrl::GetDragAndDropSource()
{
	return sDnDSource;
}

void Ctrl::GtkDragBegin(GtkWidget *widget, GdkDragContext *context, gpointer user_data)
{
	LLOG("GtkDragBegin");
}

void Ctrl::GtkDragDelete(GtkWidget *widget, GdkDragContext *context, gpointer user_data)
{
	LLOG("GtkDragDelete");
}

void Ctrl::GtkDragGetData(GtkWidget *widget, GdkDragContext   *context, GtkSelectionData *data,
                       guint info, guint time, gpointer user_data)
{
	LLOG("GtkDragGetData");
}

void Ctrl::GtkDragEnd(GtkWidget *widget, GdkDragContext *context, gpointer user_data)
{
	LLOG("GtkDragEnd");
}
                                                       
gboolean Ctrl::GtkDragFailed(GtkWidget *widget, GdkDragContext *context, GtkDragResult   result,
                             gpointer user_data)
{
	LLOG("GtkDragFailed");
	return FALSE;
}

Image MakeDragImage(const Image& arrow, Image sample);

Image MakeDragImage(const Image& arrow, const Image& arrow98, Image sample)
{
#ifdef PLATFORM_WIN32
	if(IsWin2K())
		return MakeDragImage(arrow, sample);
	else
#endif
		return arrow98;
}

int Ctrl::DoDragAndDrop(const char *fmts, const Image& sample, dword actions,
                        const VectorMap<String, ClipData>& data)
{
	return DND_NONE;
}

// --------------------------------------------------------------------------------------------

Index<String>   Ctrl::dnd_targets;
String          Ctrl::dnd_text_target;
String          Ctrl::dnd_image_target;
GtkWidget      *Ctrl::dnd_widget;
GdkDragContext *Ctrl::dnd_context;
guint           Ctrl::dnd_time;
String          Ctrl::dnd_data;
String          Ctrl::dnd_data_fmt;
bool            Ctrl::dnd_data_wait;

Ctrl *Ctrl::DragWnd(gpointer user_data)
{
	if(dnd_data_wait) // Do nothing if waiting for data
		return NULL;
	ProcessEvents0(NULL, false); // process any events that are already fetched
	return GetTopCtrlFromId(user_data);
}

void ToIndex(GtkTargetList *target_list, Index<String>& ndx)
{
	gint n;
	GtkTargetEntry *t = gtk_target_table_new_from_list(target_list, &n);
	for(int i = 0; i < n; i++)
		ndx.Add(t[i].target);
	gtk_target_table_free(t, n);
	gtk_target_list_unref(target_list);
	DDUMPC(ndx);
}

void Ctrl::DndTargets(GdkDragContext *context)
{
	static Index<String> text_targets;
	static Index<String> image_targets;
	ONCELOCK {
		GtkTargetList *target_list = gtk_target_list_new (NULL, 0);
		gtk_target_list_add_text_targets (target_list, 0);
		ToIndex(target_list, text_targets);
		GtkTargetList *target_list2 = gtk_target_list_new (NULL, 0);
		gtk_target_list_add_image_targets (target_list2, 0, TRUE);
		ToIndex(target_list2, image_targets);
	}
	dnd_targets.Clear();
	dnd_text_target.Clear();
	for(GList *list = gdk_drag_context_list_targets(context); list; list = g_list_next (list)) {
		String g = gdk_atom_name((GdkAtom)list->data);
		DDUMP(g);
		if(text_targets.Find(g) >= 0) {
			dnd_targets.Add("text");
			if(dnd_text_target.IsEmpty())
				dnd_text_target = g;
		}
		else
		if(image_targets.Find(g) >= 0) {
			dnd_targets.Add("image");
			if(dnd_image_target.IsEmpty())
				dnd_image_target = g;
		}
		else
			dnd_targets.Add(g);
	}
}

void Ctrl::GtkDragDataReceived(GtkWidget *widget, GdkDragContext *context,
                               gint x, gint y, GtkSelectionData *data,
                               guint info, guint time, gpointer user_data)
{
	LLOG("GtkDragDataReceived");
	dnd_data_wait = false;
	if(dnd_data_fmt == "text") {
		guchar *s = gtk_selection_data_get_text(data);
		if(s) {
			dnd_data = (const char *)s;
			g_free(s);
		}
	}
	else
	if(dnd_data_fmt == "image") {
		Image img = ImageFromPixbufUnref(gtk_selection_data_get_pixbuf(data));
		dnd_data = StoreAsString(img); // Not very optimal...
	}
	else
		dnd_data = String(gtk_selection_data_get_data(data), gtk_selection_data_get_length(data));
}

bool Ctrl::IsDragAvailable(const char *fmt)
{
	LLOG("IsDragAvailable " << fmt << " " << (Ctrl::dnd_targets.Find(fmt) >= 0));
	return dnd_targets.Find(fmt) >= 0;
}

String Ctrl::DragGet(const char *fmt)
{
	LLOG("DragGet " << fmt << " " << (Ctrl::dnd_targets.Find(fmt) >= 0));
	if(Ctrl::dnd_targets.Find(fmt) < 0)
		return Null;
	dnd_data.Clear();
	dnd_data_wait = true;
	dnd_data_fmt = fmt;
	int t0 = msecs();
	DDUMP(dnd_widget);
	DDUMP(dnd_context);
	gtk_drag_get_data(dnd_widget, dnd_context,
	                  GAtom(strcmp(fmt, "image") == 0 ? ~dnd_image_target
	                        : strcmp(fmt, "text") == 0 ? ~dnd_text_target : fmt),
	                  dnd_time);
	while(msecs() - t0 < 1000 && dnd_data_wait)
		FetchEvents(true);
	LLOG("DragGet data length " << dnd_data.GetLength());
	DDUMPHEX(dnd_data);
	return dnd_data;
}

PasteClip Ctrl::GtkDnd(GtkWidget *widget, GdkDragContext *context, gint x, gint y,
                       guint time, gpointer user_data, bool paste)
{
	DndTargets(context);
	g_object_ref(context); // make sure these always survive the action...
	g_object_ref(widget);
	dnd_context = context;
	dnd_widget = widget;
	dnd_time = time;
	PasteClip clip;
	clip.type = 1;
	clip.paste = paste;
	clip.accepted = false;
	clip.allowed = DND_MOVE|DND_COPY;
	clip.action = gdk_drag_context_get_suggested_action(context) == GDK_ACTION_COPY ? DND_COPY
                                                                                    : DND_MOVE;
	Ctrl *w = DragWnd(user_data);
	if(w) {
		gint mx, my;
		GdkModifierType mod;
		gdk_window_get_pointer(gdk_get_default_root_window(), &mx, &my, &mod);
		CurrentState = mod;
		CurrentMousePos = Point(x, y) + w->GetScreenRect().TopLeft();	
		w->DnD(CurrentMousePos, clip);
	}
	return clip;
}

gboolean Ctrl::GtkDragMotion(GtkWidget *widget, GdkDragContext *context, gint x, gint y,
                             guint time, gpointer user_data)
{
	LLOG("GtkDragMotion");

	PasteClip clip = GtkDnd(widget, context, x, y, time, user_data, false);
	gdk_drag_status(context, clip.IsAccepted() ? clip.GetAction() == DND_MOVE ? GDK_ACTION_MOVE
	                                                                          : GDK_ACTION_COPY
	                                           : GdkDragAction(0), time);
	g_object_unref(widget);
	g_object_unref(context);
	return TRUE;
}

void Ctrl::GtkDragLeave(GtkWidget *widget, GdkDragContext *context, guint time, gpointer user_data)
{
	LLOG("GtkDragLeave");
	DnDLeave();
}

gboolean Ctrl::GtkDragDrop(GtkWidget *widget, GdkDragContext *context, gint x, gint y,
                           guint time, gpointer user_data)
{
	LLOG("GtkDragDrop");

	PasteClip clip = GtkDnd(widget, context, x, y, time, user_data, true);
	gtk_drag_finish(context, clip.IsAccepted(), clip.IsAccepted() && clip.GetAction() == DND_MOVE, time);
	g_object_unref(widget);
	g_object_unref(context);
	DnDLeave();
	return TRUE;
}

void Ctrl::DndInit()
{
	GtkWidget *w = top->window;
	gpointer id = (gpointer)(uintptr_t)top->id;
	g_signal_connect(w, "drag-begin", G_CALLBACK(GtkDragBegin), id);
	g_signal_connect(w, "drag-data-delete", G_CALLBACK(GtkDragDelete), id);
	g_signal_connect(w, "drag-data-get", G_CALLBACK(GtkDragGetData), id);
	g_signal_connect(w, "drag-data-received", G_CALLBACK(GtkDragDataReceived), id);
	g_signal_connect(w, "drag-drop", G_CALLBACK(GtkDragDrop), id);
	g_signal_connect(w, "drag-end", G_CALLBACK(GtkDragEnd), id);
	g_signal_connect(w, "drag-failed", G_CALLBACK(GtkDragFailed), id);
	g_signal_connect(w, "drag-leave", G_CALLBACK(GtkDragLeave), id);
	g_signal_connect(w, "drag-motion", G_CALLBACK(GtkDragMotion), id);
	gtk_drag_dest_set(w, GtkDestDefaults(0), NULL, 0, GdkDragAction(GDK_ACTION_COPY|GDK_ACTION_MOVE));
}

void Ctrl::DndExit()
{
	if(top)
		gtk_drag_dest_unset(top->window);
}

END_UPP_NAMESPACE

#endif
