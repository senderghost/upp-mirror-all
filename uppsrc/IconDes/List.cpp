#include "IconDes.h"

static String sFormatImageName(const String& name, const Image& img)
{
	Size sz = img.GetSize();
	return String().Cat() << name << " (" << sz.cx << " x " << sz.cy << ')';
}

void IconDes::SyncList()
{
	int a = list.GetCursorSc();
	int ii = list.GetCursor();
	list.Clear();
	for(int i = 0; i < slot.GetCount(); i++) {
		Slot& c = slot[i];
		list.Add(sFormatImageName(c.name, c.image), c.image);
	}
	if(ii >= 0) {
		list.SetCursor(ii);
		list.ScCursor(a);
	}
}

static int sCharFilterCid(int c)
{
	return IsAlNum(c) || c == '_' ? c : 0;
}

void IconDes::PlaceDlg(TopWindow& dlg)
{
	Rect r = list.GetScreenRect();
	Size sz = dlg.GetSize();
	dlg.NoCenter().SetRect(max(0, r.left + (r.Width() - sz.cx) / 2), r.bottom + 32, sz.cx, sz.cy);
}

void IconDes::PrepareImageDlg(WithImageLayout<TopWindow>& dlg)
{
	CtrlLayoutOKCancel(dlg, "New image");
	dlg.cx <<= 16;
	dlg.cy <<= 16;
	if(IsCurrent()) {
		Size sz = GetImageSize();
		dlg.cx <<= sz.cx;
		dlg.cy <<= sz.cy;
	}
	dlg.name.SetFilter(sCharFilterCid);
}

bool CheckName(WithImageLayout<TopWindow>& dlg)
{
	String n = dlg.name;
	CParser p(n);
	if(p.IsId()) return true;
	Exclamation("Invalid name!");
	return false;
}

void IconDes::InsertRemoved(int q)
{
	if(q >= 0 && q < removed.GetCount()) {
		int ii = list.IsCursor() ? list.GetCursor() : 0;
		slot.Insert(ii) = removed[q];
		removed.Remove(q);
		SyncList();
		list.SetCursor(ii);
	}
}

void IconDes::ImageInsert(const String& name, const Image& m)
{
	int ii = list.IsCursor() ? list.GetCursor() : 0;
	if(ii == list.GetCount() - 1)
		ii = list.GetCount();
	Slot& c = slot.Insert(ii);
	c.name = name;
	c.image = m;
	SyncList();
	list.SetCursor(ii);
}

void IconDes::InsertImage()
{
	WithImageLayout<TopWindow> dlg;
	PrepareImageDlg(dlg);
	do {
		if(dlg.Run() != IDOK)
			return;
	}
	while(!CheckName(dlg));
	ImageInsert(~dlg.name, CreateImage(Size(~dlg.cx, ~dlg.cy), Null));
}

void IconDes::Duplicate()
{
	if(!IsCurrent())
		return;
	Slot& c = Current();
	ImageInsert(c.name, c.image);
	EditImage();
}

void IconDes::InsertPaste()
{
	Image m = ReadClipboardImage();
	if(IsNull(m)) {
		Exclamation("Clipboard does not contain an image.");
		return;
	}
	ImageInsert("", m);
	EditImage();
}

void IconDes::ListCursor()
{
	SyncImage();
}

void IconDes::EditImage()
{
	if(!IsCurrent())
		return;
	Slot& c = Current();
	WithImageLayout<TopWindow> dlg;
	PrepareImageDlg(dlg);
	dlg.Breaker(dlg.cx);
	dlg.Breaker(dlg.cy);
	Image img = c.image;
	dlg.cx <<= img.GetWidth();
	dlg.cy <<= img.GetHeight();
	dlg.name <<= c.name;
	for(;;) {
		switch(dlg.Run()) {
		case IDCANCEL:
			c.image = img;
			Reset();
			return;
		case IDOK:
			if(!CheckName(dlg)) break;
			c.name = ~dlg.name;
			list.Set(0, sFormatImageName(c.name, c.image));
			Reset();
			return;
		}
		c.image = CreateImage(Size(minmax((int)~dlg.cx, 1, 8192), minmax((int)~dlg.cy, 1, 8192)), Null);
		::Copy(c.image, Point(0, 0), img, img.GetSize());
		Reset();
	}
}

void IconDes::RemoveImage()
{
	if(!IsCurrent() || !PromptYesNo("Remove current image?"))
		return;
	int ii = list.GetCursor();
	while(removed.GetCount() > 12)
		removed.Remove(0);
	Slot& r = removed.Add();
	r = slot[ii];
	if(r.image.GetWidth() <= 128 && r.image.GetHeight() <= 128)
		r.base_image = Rescale(r.image, Size(16, 16));
	else
		r.base_image = IconDesImg::LargeImage();
	slot.Remove(ii);
	list.KillCursor();
	SyncList();
	if(ii < slot.GetCount())
		list.SetCursor(ii);
	else
		list.GoEnd();
}

void IconDes::MoveSlot(int d)
{
	if(!IsCurrent())
		return;
	int c = list.GetCursor();
	d = c + d;
	if(d >= 0 && d < slot.GetCount()) {
		slot.Swap(c, d);
		SyncList();
		list.SetCursor(d);
	}
}

void IconDes::ListMenu(Bar& bar)
{
	bar.Add("Insert image..", IconDesImg::Insert(), THISBACK(InsertImage))
	   .Key(K_INSERT);
	bar.Add(IsCurrent(), "Image..", IconDesImg::Edit(), THISBACK(EditImage));
	bar.Add(IsCurrent(), "Remove image", IconDesImg::Remove(), THISBACK(RemoveImage));
	bar.Add(IsCurrent(), "Duplicate", IconDesImg::Duplicate(), THISBACK(Duplicate))
	   .Key(K_CTRL_D);
	bar.Add("Insert from clipboard", IconDesImg::InsertPaste(), THISBACK(InsertPaste))
	   .Key(K_ALT_V);
	bar.Separator();
	bar.Add(IsCurrent() && list.GetCursor() > 0, "Move up", IconDesImg::MoveUp(),
	        THISBACK1(MoveSlot, -1))
	   .Key(K_ALT|K_CTRL_UP);
	bar.Add(IsCurrent() && list.GetCursor() < slot.GetCount() - 1, "Move down", IconDesImg::MoveDown(),
	        THISBACK1(MoveSlot, 1))
	   .Key(K_ALT|K_CTRL_DOWN);
	if(removed.GetCount()) {
		bar.Separator();
		for(int i = removed.GetCount() - 1; i >= 0; i--) {
			Slot& r = removed[i];
			bar.Add("Insert " + sFormatImageName(r.name, r.image), r.base_image,
			        THISBACK1(InsertRemoved, i));
		}
	}
}

void IconDes::Clear()
{
	list.Clear();
	slot.Clear();
	Reset();
}

void IconDes::AddImage(const String& name, const Image& image)
{
	Slot& c = slot.Add();
	c.name = name;
	c.image = image;
	list.Add(sFormatImageName(c.name, c.image), c.image);
	list.GoBegin();
}

int IconDes::GetCount() const
{
	return slot.GetCount();
}

Image IconDes::GetImage(int ii) const
{
	const Slot& c = slot[ii];
	Image m = slot[ii].image;
	if(c.supersampling) {
		Size sz = m.GetSize() / 3;
		sz = Size(max(sz.cx, 1), max(sz.cy, 1));
		m = Rescale(m, sz);
	}
	return m;
}

String IconDes::GetName(int ii) const
{
	return slot[ii].name;
}
