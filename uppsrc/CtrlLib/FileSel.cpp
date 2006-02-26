#include <CtrlLib/CtrlLib.h>

#ifdef PLATFORM_XFT
#define FNTSIZE 12
#else
#define FNTSIZE 11
#endif

bool Load(FileList& list, const String& dir, const char *patterns, bool dirs,
          Callback3<bool, const String&, Image&> WhenIcon, FileSystemInfo& filesystem)
{
	if(dir.IsEmpty()) {
		Array<FileSystemInfo::FileInfo> root = filesystem.Find(Null);
		for(int i = 0; i < root.GetCount(); i++)
			list.Add(root[i].filename, GetDriveImage(root[i].root_style),
				Arial(FNTSIZE).Bold(), SBlack, true, -1, Null, SCyan,
				root[i].root_desc, Arial(FNTSIZE));
	}
	else {
		Array<FileSystemInfo::FileInfo> ffi =
			filesystem.Find(AppendFileName(dir, filesystem.IsWin32() ? "*.*" : "*"));
		if(ffi.IsEmpty())
			return false;
		for(int t = 0; t < ffi.GetCount(); t++) {
			const FileSystemInfo::FileInfo& fi = ffi[t];
			Image img = fi.is_directory ? CtrlImg::Dir() : CtrlImg::File();
			WhenIcon(fi.is_directory, fi.filename, img);
			bool nd = dirs && !fi.is_directory;
			if(fi.filename != "." && fi.filename != ".." != 0 &&
			   (fi.is_directory || PatternMatchMulti(patterns, fi.filename)))
				list.Add(fi.filename, img,
						 fi.is_directory ? Arial(FNTSIZE).Bold() : Arial(FNTSIZE),
						 nd ? SGray : SBlack, fi.is_directory, fi.is_directory ? -1 : (int)fi.length,
						 Null, nd ? SGray : fi.is_directory ? SBlack : SLtBlue);
		}
	}
	return true;
}

class FileListSortName : public FileList::Order {
public:
	virtual bool operator()(const FileList::File& a, const FileList::File& b) const {
		if(a.isdir != b.isdir)
			return a.isdir;
		if(a.name == "..")
			return b.name != "..";
		if(b.name == "..")
			return false;
		return stricmp(a.name, b.name) < 0;
	}
};

void SortByName(FileList& list)
{
	list.Sort(FileListSortName());
}

class FileListSortExt : public FileList::Order {
public:
	virtual bool operator()(const FileList::File& a, const FileList::File& b) const {
		if(a.isdir != b.isdir)
			return a.isdir;
		if(a.name == "..")
			return b.name != "..";
		if(b.name == "..")
			return false;
		const char *ae = strrchr(a.name, '.');
		const char *be = strrchr(b.name, '.');
		int q;
		if(ae == NULL || be == NULL) {
			if(ae) return false;
			if(be) return true;
			q = 0;
		}
		else
			q = stricmp(ae, be);
		return (q ? q : stricmp(a.name, b.name)) < 0;
	}
};

void SortByExt(FileList& list)
{
	list.Sort(FileListSortExt());
}

String FileSel::GetDir() {
	String s = ~dir;
	if(s.IsEmpty()) return basedir;
	if(basedir.IsEmpty()) return s;
	return AppendFileName(basedir, s);
}

void FileSel::SetDir(const String& _dir) {
	dir <<= _dir;
	Load();
}

String FileSel::FilePath(const String& fn) {
	return AppendFileName(GetDir(), fn);
}

Image GetDriveImage(char drive_style)
{
	switch(drive_style)
	{
	case FileSystemInfo::ROOT_NO_ROOT_DIR: return Null;
	case FileSystemInfo::ROOT_COMPUTER:  return CtrlImg::Computer();
	case FileSystemInfo::ROOT_REMOVABLE: return CtrlImg::Diskette();
	case FileSystemInfo::ROOT_CDROM:     return CtrlImg::CdRom();
	default:                             return CtrlImg::Hd();
	}
}

void FileSel::Load() {
	list.EndEdit();
	list.Clear();
	String d = GetDir();
	if(!::Load(list, d, (String)~type, mode == SELECTDIR, WhenIcon, *filesystem)) {
		Exclamation(t_("[A3* Unable to read the directory !]&&") + DeQtf((String)~dir) + "&&" +
		            GetErrorMessage(GetLastError()));
		if(!basedir.IsEmpty() && String(~dir).IsEmpty()) {
			Break(IDCANCEL);
			return;
		}
		dir <<= olddir;
		olddir = Null;
		Load();
	}
	if(d.IsEmpty()) {
		if(filesystem->IsWin32()) {
			mkdir.Disable();
			plus.Disable();
			minus.Disable();
			toggle.Disable();
			list.Renaming(false);
		}
		dir <<= d;
		dirup.Disable();
	}
	else {
		dirup.Enable();
		mkdir.Enable();
		plus.Enable();
		minus.Enable();
		toggle.Enable();
		list.Renaming(true);
	}
	if(filesystem->IsPosix())
		if(d == "/" || !IsEmpty(basedir) && String(~dir).IsEmpty())
			dirup.Disable();
	if(filesystem->IsWin32())
		if(!IsEmpty(basedir) && String(~dir).IsEmpty())
			dirup.Disable();
	if(sortext && mode != SELECTDIR)
		SortByExt(list);
	else
		SortByName(list);
	olddir = ~dir;
}

String TrimDot(String f) {
	int i = f.Find('.');
	if(i == f.GetLength() - 1)
		f.Trim(i);
	return f;
}


void FileSel::AddName(Vector<String>& fn, String& f) {
	if(!f.IsEmpty()) {
		if(f.Find('.') < 0 && !defext.IsEmpty())
			f << '.' << defext;
		else
			f = TrimDot(f);
		fn.Add(f);
	}
	f.Clear();
}

void FileSel::Finish() {
	if(filesystem->IsWin32())
		if(GetDir().IsEmpty()) {
			file.Clear();
			return;
		}
	fn.Clear();
	if(mode == SELECTDIR) {
		String p = GetDir();
		if(list.GetCursor() >= 0) {
			const FileList::File& m = list[list.GetCursor()];
			if(m.isdir)
				p = AppendFileName(p, m.name);
		}
		fn.Add(p);
		Break(IDOK);
		return;
	}
	String f = file.GetText().ToString();
	if(f.IsEmpty()) return;
	String o;
	for(const char *s = f; *s; s++) {
		if(*s == ' ')
			AddName(fn, o);
		else
		if(*s == '\"') {
			AddName(fn, o);
			s++;
			for(;;) {
				if(*s == '\0')
					AddName(fn, o);
				else
				if(*s == '\"') {
					AddName(fn, o);
					break;
				}
				o.Cat(*s++);
			}
		}
		else
			o.Cat(*s);
	}
	AddName(fn, o);
	if(!IsMulti() && fn.GetCount())
		fn.SetCount(1);
	String d = GetDir();
	String nonexist;
	int ne = 0;
	for(int i = 0; i < fn.GetCount(); i++) {
		String p = fn[i];
		if(!IsFullPath(p))
			p = NormalizePath(AppendFileName(d, fn[i]));
		Array<FileSystemInfo::FileInfo> ff = filesystem->Find(p, 1);
		p = DeQtf(p);
		if(!ff.IsEmpty() && ff[0].is_directory) {
			Exclamation(p + t_(" is directory."));
			return;
		}
		if(asking)
			if(mode == SAVEAS) {
				if(!ff.IsEmpty() && !PromptOKCancel(p + t_(" already exists.&Do you want to continue ?")))
					return;
			}
			else
			if(ff.IsEmpty()) {
				if(ne) nonexist << '&';
				nonexist << p;
				ne++;
			}
	}
	if(ne) {
		nonexist << (ne == 1 ? t_(" does not exist.") : t_("&do not exist."));
		if(!PromptOKCancel(nonexist + t_("&Do you want to continue ?")))
			return;
	}
	Break(IDOK);
}

bool FileSel::OpenItem() {
	if(list.IsCursor()) {
		const FileList::File& m = list.Get(list.GetCursor());
		if(m.isdir) {
			SetDir(AppendFileName(~dir, m.name));
			return true;
		}
	}
	if(mode != SELECTDIR)
		Finish();
	return false;
}

void FileSel::Open() {
	if(mode == SELECTDIR) {
		Finish();
		return;
	}
	if(list.HasFocus()) {
		if(OpenItem()) list.SetCursor(0);
	}
	else
	if(list.IsSelection())
		for(int i = 0; i < list.GetCount(); i++) {
			const FileList::File& m = list[i];
			if(!m.isdir) Finish();
		}
	else
	if(file.HasFocus()) {
		String fn = file.GetText().ToString();
		if(fn == "." || fn == "..") {
			DirUp();
			return;
		}
		if(HasWildcards(fn)) {
			file.Clear();
			int q = type.FindKey(fn);
			if(q >= 0)
				type.SetIndex(q);
			else {
				type.Add(fn, t_("Custom file type (") + fn + ')');
				type.SetIndex(type.GetCount() - 1);
			}
			Load();
			return;
		}
		if(fn.Find(' ') < 0 && fn.Find('\"') < 0) {
			if(filesystem->IsWin32())
			{
				if(fn.GetLength() >= 2 && fn[1] == ':' && fn.GetLength() <= 3) {
					fn.Set(0, ToUpper(fn[0]));
					if(fn.GetLength() == 2)
						fn.Cat('\\');
//					if(GetDriveType(fn) == DRIVE_NO_ROOT_DIR) {
//						Exclamation(s_(FileSel7));
//						return;
//					}
					SetDir(fn);
					return;
				}
			}
			if(!IsFullPath(fn))
				fn = AppendFileName(~dir, fn);
			if(filesystem->IsWin32() && (!fn.IsEmpty() && (*fn.Last() == '\\' || *fn.Last() == '/'))
			|| filesystem->IsPosix() && (fn != "/" && (*fn.Last() == '\\' || *fn.Last() == '/')))
			{
				fn.Trim(fn.GetLength() - 1);
				SetDir(TrimDot(fn));
				return;
			}
			Array<FileSystemInfo::FileInfo> ff = filesystem->Find(fn, 1);
			if(!ff.IsEmpty()) {
				if(ff[0].is_directory) {
					SetDir(TrimDot(fn));
					return;
				}
				else {
					SetDir(TrimDot(GetFileFolder(fn)));
					file.SetText(GetFileName(fn).ToWString());
				}
			}
		}
		if(mode != SELECTDIR) Finish();
	}
}

String DirectoryUp(String& dir, bool basedir)
{
	String s = dir;
	String name;
#ifdef PLATFORM_WIN32
	if(s.GetLength() < 3 || s.GetLength() == 3 && s[1] == ':') {
		dir.Clear();
		name = s;
	}
	else
#endif
#ifdef PLATFORM_POSIX
	if(s != "/")
#endif
	{
#ifdef PLATFORM_WIN32
		int i = max(s.ReverseFind('/'), s.ReverseFind('\\'));
#endif
#ifdef PLATFORM_POSIX
		int i = s.ReverseFind('/');
#endif
		if(basedir)
			if(i < 0)
				dir.Clear();
			else {
				dir = s.Mid(0, i);
				name = s.Mid(i + 1);
			}
		else {
#ifdef PLATFORM_WIN32
			if(s.GetLength() && s[1] == ':')
				if(i > 3) {
					dir = s.Mid(0, i);
					name = s.Mid(i + 1);
				}
				else {
					dir = s.Mid(0, 3);
					name = s.Mid(3);
				}
			if(s.GetLength() && s[0] == DIR_SEP && s[1] == DIR_SEP)
				if(i > 2) {
					dir = s.Mid(0, i);
					name = s.Mid(i + 1);
				}
				else {
					dir.Clear();
					name = s;
				}
#endif
#ifdef PLATFORM_X11
			if(i == 0 && s.GetLength() > 1) {
				dir = "/";
				name = s.Mid(1);
			}
			else
			if(s.GetLength() && s[0] == '/' && s[1] != '/') {
				dir = s.Mid(0, i);
				name = s.Mid(i + 1);
			}
#endif
		}
	}
	return name;
}

void FileSel::DirUp() {
	String s = ~dir;
	String name = DirectoryUp(s, !basedir.IsEmpty());
	SetDir(s);
	if(list.HasFocus())
		list.FindSetCursor(name);
}

void FileSel::MkDir() {
	if(String(~dir).IsEmpty() && basedir.IsEmpty()) return;
	String name, error;
	if(EditText(name, t_("New directory"), t_("Name")) && !name.IsEmpty())
		if(filesystem->CreateFolder(FilePath(name), error))
		{
			Load();
			list.FindSetCursor(name);
		}
		else
			Exclamation(t_("[A3* Creating directory failed !&&]") + error);
}

void FileSel::PlusMinus(const char *title, bool sel) {
	String pattern;
	if(EditText(pattern, title, t_("Mask")) && !pattern.IsEmpty())
		for(int i = 0; i < list.GetCount(); i++)
			if(!list.Get(i).isdir)
				if(::PatternMatchMulti(pattern, list.Get(i).name))
					list.SelectOne(i, sel);
}

void FileSel::Plus() {
	PlusMinus(t_("Add to selection"), true);
}

void FileSel::Minus() {
	PlusMinus(t_("Remove from selection"), false);
}

void FileSel::Toggle() {
	for(int i = 0; i < list.GetCount(); i++)
		if(!list.Get(i).isdir)
			list.SelectOne(i, !list.IsSelected(i));
}

bool FileSel::Key(dword key, int count) {
	switch(key) {
	case '.':
	case K_CTRL_UP:
		list.SetFocus();
		dirup.PseudoPush();
		return true;
	case '+':
		plus.PseudoPush();
		return true;
	case '-':
		minus.PseudoPush();
		return true;
	case '*':
		toggle.PseudoPush();
		return true;
	case K_F6:
		list.StartEdit();
		return true;
	case K_F7:
		mkdir.PseudoPush();
		return true;
	case K_ENTER:
		if(mode == SELECTDIR && OpenItem())
			return true;
		break;
	case K_UP:
	case K_DOWN:
	case K_PAGEUP:
	case K_PAGEDOWN:
		list.SetFocus();
		return list.Key(key, count);
	}
	return TopWindow::Key(key, count);
}

void Catq(String& s, const String& fn) {
	if(!s.IsEmpty())
		s << ' ';
	if(fn.Find(' ') >= 0)
		s << '"' << fn << '"';
	else
		s << fn;
}

void FileSel::Update() {
	String fn;
	if(list.IsSelection()) {
		for(int i = 0; i < list.GetCount(); i++)
			if(list.IsSelected(i))
				Catq(fn, list[i].name);
	}
	else
	if(list.IsCursor()) {
		const FileList::File& m = list[list.GetCursor()];
		if(!m.isdir)
			Catq(fn, m.name);
	}
	if(mode == OPEN)
		file <<= fn;
	filename = String();
	filesize = String();
	filetime = String();
	if(list.IsCursor()) {
		fn = list[list.GetCursor()].name;
		if(fn[1] == ':' && fn.GetLength() <= 3)
			filename = t_("  Drive");
		else {
			Array<FileSystemInfo::FileInfo> ff = filesystem->Find(FilePath(fn), 1);
			if(!ff.IsEmpty()) {
				filename = "  " + fn;
				if(ff[0].is_directory)
					filesize = t_("Directory  ");
				else {
					if(mode == SAVEAS)
						file <<= fn;
					int n = (int)ff[0].length;
					if(n < 10000)
						filesize = Format("%d  ", n);
					else
					if(n < 10000 * 1024)
						filesize = Format("%d K  ", n >> 10);
					else
						filesize = Format("%d M  ", n >> 20);
				}
				Time tm = ff[0].last_write_time;
				filetime = "     " + Format(tm);
			}
		}
	}
	FileUpdate();
}

void FileSel::FileUpdate() {
	if(mode == SELECTDIR) {
		ok.Enable(!IsNull(~dir));
		return;
	}
	bool b = list.IsCursor() || !String(file).IsEmpty();
	ok.Enable(b);
	ok.SetLabel(t_("Open"));
	if(mode == SAVEAS &&
	   (!String(file).IsEmpty() || list.IsCursor() && list[list.GetCursor()].isdir))
		ok.SetLabel(t_("Save"));
}

void FileSel::Rename(const String& on, const String& nn) {
#ifdef PLATFORM_WIN32
	if(MoveFile(FilePath(on), FilePath(nn)))
#endif
#ifdef PLATFORM_X11
	if(rename(FilePath(on), FilePath(nn)) == 0)
#endif
	{
		Load();
		list.FindSetCursor(nn);
	}
	else
		Exclamation(t_("[A3* Renaming of file failed !&&]") + GetErrorMessage(GetLastError()));
}

void FileSel::Choice() {
//	String s = ~dir;
	Load();
}

FileSel& FileSel::Type(const char *name, const char *ext) {
	type.Add(ext, name);
	if(IsNull(type))
		type.SetIndex(0);
	return *this;
}

FileSel& FileSel::AllFilesType() {
	return Type(t_("All files"), "*.*");
}

struct FolderDisplay : public Display {
	virtual void Paint(Draw& w, const Rect& r, const Value& q,
	                   Color ink, Color paper, dword style) const;
};

void FolderDisplay::Paint(Draw& w, const Rect& r, const Value& q,
	                   Color ink, Color paper, dword style) const {
	String s = q;
	w.DrawRect(r, paper);
	Image img = GetDriveImage(*s.Last());

	if(IsNull(img))
		img = CtrlImg::Dir();
	w.DrawImage(r.left, r.top + (r.Height() - img.GetSize().cx) / 2, img);
	w.DrawText(r.left + 20,
	           r.top + (r.Height() - w.GetFontInfo(Arial(FNTSIZE).Bold()).GetHeight()) / 2,
			   ~s, Arial(FNTSIZE).Bold(), ink);
}

struct HomeDisplay : public Display {
	virtual void Paint(Draw& w, const Rect& r, const Value& q,
	                   Color ink, Color paper, dword style) const {
		w.DrawRect(r, paper);
		w.DrawImage(r.left, r.top + (r.Height() - CtrlImg::Home().GetSize().cx) / 2,
			        CtrlImg::Home());
		w.DrawText(r.left + 20,
		           r.top + (r.Height() - w.GetFontInfo(Arial(FNTSIZE).Bold()).GetHeight()) / 2,
				   String(q), Arial(FNTSIZE).Bold(), ink);
	}
};

void FileSel::Set(const String& s)
{
	fn.Clear();
	if(IsFullPath(s)) {
		ActiveDir(GetFileFolder(s));
		fn.Add(GetFileName(s));
	}
	else
		fn.Add(s);
	bidname = true;
}

bool FileSel::Execute(int _mode) {
	mode = _mode;
	if(mode == SELECTDIR) {
		if(!fn.IsEmpty())
			dir <<= NormalizePath(fn[0]);
		type.Hide();
		type_lbl.Hide();
		file.Hide();
		file_lbl.Hide();
		sortext.Hide();
		sort_lbl.Hide();
		ok.SetLabel(t_("&Select"));
		Logc p = filename.GetPos().y;
		int q = ok.GetPos().y.GetA() + ok.GetPos().y.GetB() + 8;
		p.SetA(q);
		filename.SetPosY(p);
		filesize.SetPosY(p);
		filetime.SetPosY(p);
		p = list.GetPos().y;
		p.SetB(q + 20);
		list.SetPosY(p);
		bidname = false;
	}
	else {
		for(Ctrl *q = GetFirstChild(); q; q = q->GetNext())
			q->Show();
		Rect r = GetRect();
		CtrlLayout(*this);
		SetRect(r);
	}
	readonly.Show(rdonly && mode == OPEN);
	list.Multi(multi && mode == OPEN);
	dir.ClearList();
	int i;
	if(basedir.IsEmpty()) {
		for(i = 0; i < lru.GetCount(); i++)
			if(IsFullPath(lru[i]) && filesystem->FolderExists(lru[i]))
				dir.Add(lru[i]);
		Array<FileSystemInfo::FileInfo> root = filesystem->Find(Null);
		for(i = 0; i < root.GetCount(); i++)
		{
			String ugly = root[i].filename;
			ugly.Cat('\0');
			ugly.Cat(root[i].root_style);
			dir.Add(root[i].filename, ugly);
		}
		if(filesystem->IsPosix() && String(~dir).IsEmpty())
			dir <<= "/";
		dir.SetDisplay(Single<FolderDisplay>(), 14);
	}
	else {
		dir.SetDisplay(Single<HomeDisplay>(), 14);
		if(filesystem->IsPosix())
		{
			if(String(~dir)[0] == '/')
				dir <<= "";
		}
	}
	Rect lr = list.GetRect();
	Rect dr = dir.GetRect();
	int px = GetSize().cx - lr.right;
	if(IsMulti()) {
		toggle.RightPos(px, 20).TopPos(dr.top, 20);
		minus.RightPos(px + 20, 20).TopPos(dr.top, 20);
		plus.RightPos(px + 40, 20).TopPos(dr.top, 20);
		px += 64;
		toggle.Show();
		minus.Show();
		plus.Show();
	}
	else {
		toggle.Hide();
		minus.Hide();
		plus.Hide();
	}
	mkdir.RightPos(px, 20).TopPos(dr.top, 20);
	dirup.RightPos(px + 20, 20).TopPos(dr.top, 20);
	dir.HSizePos(dr.left, px + 44);
	if(activetype >= 0 && activetype < type.GetCount())
		type.SetIndex(activetype);
	int dlc = type.GetCount();
	Load();
	ActiveFocus(file);
	if(bidname) {
		String s;
		for(int i = 0; i < fn.GetCount(); i++)
			Catq(s, fn[i]);
		file <<= s;
		ActiveFocus(file);
		bidname = false;
	}
	list.SetSbPos(lastsby);
	FileUpdate();
	int c = TopWindow::Execute();
	lastsby = list.GetSbPos();
	type.Trim(dlc);
	activetype = type.GetIndex();
	if(activetype >= dlc || activetype < 0)
		activetype = 0;
	if(c == IDOK) {
		String d = ~dir;
		if(filesystem->IsWin32())
			if(d.GetLength() == 3 && d[1] == ':') return true;
		if(filesystem->IsPosix())
			if(d == "/") return true;
		if(!IsFullPath(d)) return true;
		LruAdd(lru, d, 8);
		return true;
	}
	return false;
}

bool FileSel::ExecuteOpen(const char *title) {
	Title(title ? title : t_("Open"));
	return Execute(OPEN);
}

bool FileSel::ExecuteSaveAs(const char *title) {
	Title(title ? title : t_("Save as"));
	return Execute(SAVEAS);
}

bool FileSel::ExecuteSelectDir(const char *title)
{
	Title(title ? title : t_("Select directory"));
	return Execute(SELECTDIR);
}

void FileSel::Serialize(Stream& s) {
	int version = 5;
	s / version;
	String ad = ~dir;
	s / activetype % ad;
	dir <<= ad;
	if(version < 1) {
		String n = fn.At(0);
		s % n;
		fn.At(0) = n;
	}
	else {
		if(version < 4)
			s % fn;
		else {
			Vector<String> __;
			s % __;
		}
	}
	if(version >= 2) {
		SerializePlacement(s);
		s % list;
	}
	if(version >= 3) {
		s % lastsby;
	}
	if(version >= 4) {
		s % lru;
	}
	if(version >= 5) {
		s % sortext;
	}
}

String FileSel::GetFile(int i) const {
	String p;
	if(i >= 0 && i < fn.GetCount()) {
		p = fn[i];
		if(!IsFullPath(p))
			p = AppendFileName(dir.GetData(), p);
	}
	return p;
}

FileSel::FileSel() {
	filesystem = &StdFileSystemInfo();
	CtrlLayout(*this);
	Acceptor(ok, IDOK); ok.Ok();
	Rejector(cancel, IDCANCEL); cancel.Cancel();
	list.IconWidth(16).Renaming().Columns(3).ClickKill();
	list.WhenLeftDouble = THISBACK(OpenItem2);
	dirup <<= THISBACK(DirUp);
	Add(dirup);
	sortext <<= THISBACK(Load);
	Add(sortext);
	mkdir <<= THISBACK(MkDir);
	Add(mkdir);
	plus <<= THISBACK(Plus);
	Add(plus);
	minus <<= THISBACK(Minus);
	Add(minus);
	toggle <<= THISBACK(Toggle);
	Add(toggle);

	ok <<= THISBACK(Open);
	list <<= THISBACK(Update);
	file <<= THISBACK(FileUpdate);
	list.WhenRename = THISBACK(Rename);
	Sizeable();
	dirup.SetImage(CtrlImg::DirUp()).NoWantFocus();
	dirup.Tip(t_("Dir up") + String(" (Ctrl+Up)"));
	mkdir.SetImage(CtrlImg::MkDir()).NoWantFocus();
	mkdir.Tip(t_("Create directory") + String(" (F7)"));
	plus.SetImage(CtrlImg::Plus()).NoWantFocus();
	plus.Tip(t_("Select files"));
	minus.SetImage(CtrlImg::Minus()).NoWantFocus();
	minus.Tip(t_("Unselect files"));
	toggle.SetImage(CtrlImg::Toggle()).NoWantFocus();
	toggle.Tip(t_("Toggle files"));
	type <<= THISBACK(Load);
	sortext <<= 0;

	filename.SetFont(Arial(FNTSIZE));
	filename.SetFrame(ThinInsetFrame());
	filesize.SetFont(Arial(FNTSIZE)).SetAlign(ALIGN_RIGHT);
	filesize.SetFrame(ThinInsetFrame());
	filetime.SetFont(Arial(FNTSIZE));
	filetime.SetFrame(ThinInsetFrame());

	dir <<= THISBACK(Choice);
	dir.DisplayAll();

	activetype = 0;
	readonly.Hide();

	lastsby = 0;

	asking = true;
	rdonly = false;
	multi = false;
	bidname = false;

	Add(sizegrip);
}

FileSel::~FileSel() {}
