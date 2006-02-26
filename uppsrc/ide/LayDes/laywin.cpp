#include "LayDes.h"

#define LTIMING(x) //TIMING(x)

#define KEYNAMESPACE LayoutKeys
#define KEYGROUPNAME "Layout"
#define KEYFILE      <ide/LayDes/laydes.key>
#include             <CtrlLib/key_source.h>

using namespace LayoutKeys;

void LayDes::EditBar(Bar& bar)
{
	bool islayout = currentlayout >= 0;
	bool iscursor = islayout && cursor.GetCount();
	bar.Add(iscursor, "Cut", CtrlImg::cut(), THISBACK(Cut))
	   .Key(K_SHIFT_DELETE)
	   .Key(K_CTRL_X);
	bar.Add(iscursor, "Copy", CtrlImg::copy(), THISBACK(Copy))
	   .Key(K_CTRL_INSERT)
	   .Key(K_CTRL_C);
	bar.Add(islayout, "Paste", CtrlImg::paste(), THISBACK(Paste))
	   .Key(K_SHIFT_INSERT)
	   .Key(K_CTRL_V);
	bar.Add(iscursor, "Delete", CtrlImg::remove(), THISBACK(Delete))
	   .Key(K_DELETE);
	bar.Add(iscursor, AK_DUPLICATESEL, LayImg::Duplicate(), THISBACK(Duplicate));
	bar.Add(iscursor, AK_MATRIXDUPLICATE, THISBACK(Matrix));
	bar.Add(islayout, "Select all", THISBACK(SelectAll))
	   .Key(K_CTRL_A);
	bar.Add(islayout, AK_VISGEN, LayImg::Members(), THISBACK(VisGen));
	bar.Separator();
	bar.Add(islayout && CurrentLayout().IsUndo(), "Undo", CtrlImg::undo(), THISBACK(Undo))
	   .Key(K_ALT_BACKSPACE)
	   .Key(K_CTRL_Z);
	bar.Add(islayout && CurrentLayout().IsRedo(), "Redo", CtrlImg::redo(), THISBACK(Redo))
	   .Key(K_SHIFT|K_ALT_BACKSPACE)
	   .Key(K_SHIFT_CTRL_Z);
	bar.MenuSeparator();
	bar.Add(iscursor, AK_HIDESELECTION, THISBACK1(ShowSelection, false))
		.Key(K_CTRL_SUBTRACT);
	bar.Add(iscursor, AK_SHOWSELECTION, THISBACK1(ShowSelection, true))
		.Key(K_CTRL_ADD);
}

void LayDes::MoveBar(Bar& bar)
{
	bool iscursor = currentlayout >= 0 && cursor.GetCount();
	bar.Add(iscursor, AK_MOVEUP, LayImg::MoveUp(), THISBACK(MoveUp));
	bar.Add(iscursor, AK_MOVEDOWN, LayImg::MoveDown(), THISBACK(MoveDown));
}

void LayDes::AlignBar(Bar& bar)
{
	bool islayout = currentlayout >= 0;
	bool iscursor = islayout && cursor.GetCount();
	bool group = islayout && cursor.GetCount() > 1;
	bar.Add(iscursor, AK_HCENTERLAY, LayImg::HorzCenter(), THISBACK1(Align, A_HORZCENTER));
	bar.Add(iscursor, AK_VCENTERLAY, LayImg::VertCenter(), THISBACK1(Align, A_VERTCENTER));
	bar.Separator();
	bar.Add(group, AK_LEFT, LayImg::AlignLeft(), THISBACK1(Align, A_LEFT));
	bar.Add(group, AK_HCENTER, LayImg::AlignHCenter(), THISBACK1(Align, A_HCENTER));
	bar.Add(group, AK_RIGHT, LayImg::AlignRight(), THISBACK1(Align, A_RIGHT));
	bar.Separator();
	bar.Add(group, AK_TOP, LayImg::AlignTop(), THISBACK1(Align, A_TOP));
	bar.Add(group, AK_VCENTER, LayImg::AlignVCenter(), THISBACK1(Align, A_VCENTER));
	bar.Add(group, AK_BOTTOM, LayImg::AlignBottom(), THISBACK1(Align, A_BOTTOM));
	bar.Add(cursor.GetCount(), AK_LABELS, LayImg::AlignLbl(), THISBACK1(Align, A_LABEL));
}

void LayDes::SizeBar(Bar& bar)
{
	bool islayout = currentlayout >= 0;
	bool iscursor = islayout && cursor.GetCount();
	bool group = islayout && cursor.GetCount() > 1;
	bar.Add(group, AK_SAMEWIDTH, LayImg::SameWidth(), THISBACK1(Align, A_SAMEWIDTH));
	bar.Add(group, AK_SAMEHEIGHT, LayImg::SameHeight(), THISBACK1(Align, A_SAMEHEIGHT));
	bar.Add(group, AK_SAMESIZE, LayImg::SameSize(), THISBACK1(Align, A_SAMESIZE));
	bar.Separator();
	bar.Add(iscursor, AK_MINIMALWIDTH, LayImg::MinWidth(), THISBACK1(Align, A_MINWIDTH));
	bar.Add(iscursor, AK_MINIMALHEIGHT, LayImg::MinHeight(), THISBACK1(Align, A_MINHEIGHT));
}

void LayDes::SpringBar(Bar& bar)
{
	bool islayout = currentlayout >= 0;
	bool iscursor = islayout && cursor.GetCount();
	int va = -1;
	int ha = -1;
	if(currentlayout >= 0 && cursor.GetCount()) {
		LayoutData& l = CurrentLayout();
		Ctrl::LogPos p = l.item[cursor.Top()].pos;
		ha = p.x.GetAlign();
		va = p.y.GetAlign();
		for(int i = 0; i < cursor.GetCount() - 1; i++) {
			p = l.item[cursor[i]].pos;
			if(p.x.GetAlign() != ha)
				ha = -1;
			if(p.y.GetAlign() != va)
				va = -1;
		}
	}
	bar.Add(iscursor, AK_SPRINGLEFT, LayImg::SpringLeft(),
	       THISBACK1(SetSprings, MAKELONG(Ctrl::LEFT, -1)))
		.Check(ha == Ctrl::LEFT);
	bar.Add(iscursor, AK_SPRINGRIGHT, LayImg::SpringRight(),
	       THISBACK1(SetSprings, MAKELONG(Ctrl::RIGHT, -1)))
		.Check(ha == Ctrl::RIGHT);
	bar.Add(iscursor, AK_SPRINGHSIZE, LayImg::SpringHSize(),
	       THISBACK1(SetSprings, MAKELONG(Ctrl::SIZE, -1)))
		.Check(ha == Ctrl::SIZE);
	bar.Add(iscursor, AK_SPRINGHCENTER, LayImg::SpringHCenter(),
	       THISBACK1(SetSprings, MAKELONG(Ctrl::CENTER, -1)))
		.Check(ha == Ctrl::CENTER);
	bar.Separator();
	bar.Add(iscursor, AK_SPRINGTOP, LayImg::SpringTop(),
	       THISBACK1(SetSprings, MAKELONG(-1, Ctrl::TOP)))
		.Check(va == Ctrl::TOP);
	bar.Add(iscursor, AK_SPRINGBOTTOM, LayImg::SpringBottom(),
	       THISBACK1(SetSprings, MAKELONG(-1, Ctrl::BOTTOM)))
		.Check(va == Ctrl::BOTTOM);
	bar.Add(iscursor, AK_SPRINGVSIZE, LayImg::SpringVSize(),
	       THISBACK1(SetSprings, MAKELONG(-1, Ctrl::SIZE)))
		.Check(va == Ctrl::SIZE);
	bar.Add(iscursor, AK_SPRINGVCENTER, LayImg::SpringVCenter(),
	       THISBACK1(SetSprings, MAKELONG(-1, Ctrl::CENTER)))
		.Check(va == Ctrl::CENTER);
	bar.Separator();
	bar.Add(iscursor, AK_AUTOSPRINGS, LayImg::SpringAuto(),
	       THISBACK1(SetSprings, MAKELONG(AUTOSPRING, 0)));
	bar.Add(iscursor, AK_TOPLEFTSPRINGS, LayImg::SpringTopLeft(),
	       THISBACK1(SetSprings, MAKELONG(Ctrl::LEFT, Ctrl::TOP)));
}

void LayDes::ToggleGrid()
{
	usegrid = !usegrid;
	SetBar();
}

void LayDes::ToggleMinSize()
{
	ignoreminsize = !ignoreminsize;
	SetBar();
}

void LayDes::Settings()
{
	setting.Execute();
	Refresh();
	SyncItems();
}

void LayDes::OptionBar(Bar& bar)
{
	bar.Add("Use grid", LayImg::Grid(), THISBACK(ToggleGrid))
	   .Check(usegrid);
	bar.Add("Ignore min size", LayImg::MinSize(), THISBACK(ToggleMinSize))
	   .Check(ignoreminsize);
	bar.Add("Settings..", THISBACK(Settings));
}

void LayDes::MainToolBar(Bar& bar)
{
	EditBar(bar);
	bar.Separator();
	MoveBar(bar);
	bar.Separator();
	OptionBar(bar);
	bar.Separator();
	bar.Add(status, INT_MAX);
	bar.Break();
	AlignBar(bar);
	bar.Separator();
	SizeBar(bar);
	bar.Separator();
	SpringBar(bar);
}

void LayDes::ItemBar(Bar& bar)
{
	bar.Add("Position", THISBACK(MoveBar));
	bar.Add("Alignment", THISBACK(AlignBar));
	bar.Add("Size", THISBACK(SizeBar));
	bar.Add("Springs", THISBACK(SpringBar));
}

void LayDes::MainMenuBar(Bar& bar)
{
	bar.Add("Edit", THISBACK(EditBar));
	bar.Add("Item", THISBACK(ItemBar));
	bar.Add("Options", THISBACK(OptionBar));
}

void LayDes::EditMenu(Bar& bar)
{
	EditBar(bar);
	bar.Separator();
	bar.Add("Item", THISBACK(ItemBar));
	bar.Separator();
	OptionBar(bar);
}

void LayDes::SetBar()
{
	LTIMING("SetBar");
	toolbar.Set(THISBACK(MainToolBar));
}

class CVFrame : public CtrlFrame {
	virtual void FrameLayout(Rect& r) { r.bottom -= 4; r.left += 2; r.right -= 2; }
	virtual void FramePaint(Draw& w, const Rect& r) { w.DrawRect(r, SLtGray); }
	virtual void FrameAddSize(Size& sz) { sz.cy += 4; sz.cx += 4; }
};

void LayDes::Serialize(Stream& s)
{
	int version = 1;
	s / version;
	s % setting.gridx % setting.gridy;
	s % setting.paintgrid % setting.showicons;
	s % ignoreminsize % usegrid;
	frame->SerializePlacement(s);
	s % lsplit % isplit % rsplit;
	item.SerializeHeader(s);
	SetBar();
}

void LayDes::Set(LayDesigner *f)
{
	frame = f;
	frame->Icon(LayImg::RwIconSmall());
	frame->SetRect(GetDefaultWindowRect());
	frame->Maximize();
	frame->Sizeable().Zoomable();
	frame->Add(lsplit);
	frame->AddFrame(TopSeparatorFrame());
	toolbar.AddFrame(LeftSeparatorFrame());
	frame->Title("Layout designer");
	frame->ActiveFocus(*this);
}

LayDes::LayDes()
{
	charset = CHARSET_UTF8;

	currentlayout = -1;
	draghandle = -1;

	usegrid = true;
	ignoreminsize = false;

	SetBar();

	status.Width(400);
	status.NoTransparent();

	lsplit.Horz(rsplit, *this).SetPos(2000);
	rsplit.Vert(layoutlist, isplit);
	rsplit.SetPos(1000);
	isplit.Vert(item, property);
	twsplit.Height(EditField::GetStdHeight() + 4);
	twsplit.Horz(type, variable);
	twsplit.SetFrame(Single<CVFrame>());
	property.AddFrame(twsplit);
	property.AddFrame(ThinInsetFrame());
	property.AfterCreate();
	type <<= THISBACK(TypeEdit);
	variable <<= THISBACK(VariableEdit);
	type.Disable();
	variable.Disable();

	item.AddColumn("Type", 20).Margin(0);
	item.AddColumn("Var / lbl", 10).Margin(0);
	item.WhenLeftClick = THISBACK(ItemClick);
	item.NoWantFocus();

	SetFrame(toolbar);
	AddFrame(InsetFrame());
	AddFrame(sb);

	sb.WhenScroll = THISBACK(Scroll);

	layoutlist.NoHeader().NoGrid();
	layoutlist.AddColumn();
	layoutlist.WhenCursor = THISBACK(LayoutCursor);
	layoutlist.WhenBar = THISBACK(LayoutMenu);
	layoutlist.NoWantFocus();

	NoWantFocus();
	item.NoWantFocus();

	BackPaint();

	SyncUsc();

	CtrlLayoutOKCancel(matrix, "Matrix duplicate");
	matrix.nx.MinMax(1, 32);
	matrix.nx <<= 2;
	matrix.dx.MinMax(1, 32);
	matrix.dx <<= 0;
	matrix.ny.MinMax(1, 32);
	matrix.ny <<= 1;
	matrix.dy.MinMax(1, 32);
	matrix.dy <<= 0;

	CtrlLayoutOKCancel(setting, "Settings");
	setting.gridx.MinMax(1, 32);
	setting.gridx <<= 4;
	setting.gridy.MinMax(1, 32);
	setting.gridy <<= 4;
}

void LayDes::CloseDesigner()
{
	Save();
	delete frame;
}

bool LayDesigner::Key(dword key, int repcnt)
{
	if(designer.Key(key, repcnt))
		return true;
	return false;
}

LayDesigner *CreateLayDesigner(const char *filename, byte charset, const char *cfgname)
{
	LayDesigner *q = new LayDesigner();
	LoadFromGlobal(*q, cfgname);
	q->SetConfigName(cfgname);
	if(q->Load(filename, charset))
		return q;
	delete q;
	return NULL;
}

void LayUscClean();
bool LayUscParse(CParser& p) throw(CParser::Error);
void SerializeLayEditPos(Stream& s);

bool IsLayFile(const char *path)
{
	return ToLower(GetFileExt(path)) == ".lay";
}

struct LayDesModule : public IdeModule {
	virtual void CleanUsc() {
		LayUscClean();
	}
	virtual bool ParseUsc(CParser& p) {
		return LayUscParse(p);
	}
	virtual Image FileIcon(const char *path) {
		return IsLayFile(path) ? LayImg::Layout() : Null;
	}
	virtual IdeDesigner *CreateDesigner(const char *path, byte cs) {
		if(IsLayFile(path)) {
			LayDesigner *d = CreateLayDesigner(path, cs, "laydes-ctrl");
			if(d)
				d->SizePos();
			return d;
		}
		return false;
	}
	virtual void Serialize(Stream& s) {
		int version = 0;
		s / version;
		SerializeLayEditPos(s);
	}
};

void RegisterLayDes()
{
	RegisterIdeModule(Single<LayDesModule>());
}

INITBLOCK {
	RegisterGlobalConfig("laydes-ctrl");
}
