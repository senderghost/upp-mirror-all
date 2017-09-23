#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LINES   10
#define COLUMNS 30

char framebuffer[LINES][COLUMNS] = { ' ' };
int  cursor_line, cursor_column;

void Cls()
{
	memset(framebuffer, ' ', sizeof(framebuffer));
}

void GoTo(int line, int column)
{
	cursor_line = line;
	cursor_column = column;
}

void Put(char c)
{
	framebuffer[cursor_line][cursor_column++] = c;
}

void Put(const char *s)
{
	while(*s)
		framebuffer[cursor_line][cursor_column++] = *s++;
}

enum {
	ITEM_ENDMENU, ITEM_MENU, ITEM_INT, ITEM_FLOAT, ITEM_ENUM
};

struct MiniMenuItem {
	byte        kind;
	const char *text;
	void       *data;
	int         min;
	int         max;
	void       *param;
};

struct MiniGui {
	MiniMenuItem *menu;
	int           count;
	int           cursor;
	int           last_dir;
	int           same_dir_count;
	bool          edit;
	int           subcursor;
	
	void Set(MiniMenuItem *m);
	
	void Sync();
	
	void Delta(int d);
	void Select();
};

MiniGui minigui;

const char *GetEnum(const char *l, int ii)
{
	int i = 0;
	for(;;) {
		if(*l == '\0')
			return NULL;
		if(ii == i)
			return l;
		while(*l) l++;
		l++;
		i++;
	}
}

int GetEnumCount(const char *l)
{
	int i = 0;
	for(;;) {
		if(*l == '\0')
			return i;
		while(*l) l++;
		l++;
		i++;
	}
}

void MiniGui::Set(MiniMenuItem *m)
{
	menu = m;
	count = 0;
	while(m[count].kind != ITEM_ENDMENU)
		count++;
	cursor = 0;
	Cls();
	Sync();
}

void MiniGui::Sync()
{
	for(byte i = 0; i < count; i++) {
		GoTo(i, 0);
		Put(i == cursor ? '>' : ' ');
		MiniMenuItem& m = menu[i];
		Put(m.text);
		int h;
		Put(i == cursor && edit ? ":[" : ": ");
		switch(m.kind) {
		case ITEM_INT:
		case ITEM_FLOAT:
			h = *(int *)m.data;
			if(m.kind == ITEM_FLOAT)
				Put(Format("%3d.%c", h / 10, abs(h) % 10 + '0'));
			else
				Put(Format("%4d", h));
			break;
		case ITEM_ENUM:
			Put(GetEnum((const char *)m.param, *(int *)m.data));
			break;
		}
		Put(i == cursor && edit ? "]" : " ");
	}
}

void MiniGui::Delta(int d)
{
	if(edit) {
		if(last_dir != d) {
			last_dir = d;
			same_dir_count = 0;
		}
		else
			same_dir_count++;
		MiniMenuItem& m = menu[cursor];
		switch(m.kind) {
		case ITEM_ENUM: {
			int& h = *(int *)m.data;
			int n = GetEnumCount((const char *)m.param);
			h += d;
			if(h < 0)
				h = n - 1;
			if(h >= n)
				h = 0;
			break;
		}
		case ITEM_INT:
		case ITEM_FLOAT: {
			int& h = *(int *)m.data;
			if(same_dir_count > 5 && h % 10 == 0)
				d *= 10;
			h += d;
			if(h < m.min)
				h = m.min;
			else
			if(m.max > m.min && h > m.max)
				h = m.max;
			break;
		}
		}
	}
	else {
		cursor += -d;
		if(cursor < 0)
			cursor = count - 1;
		else
		if(cursor >= count)
			cursor = 0;
	}
	Sync();
}

void MiniGui::Select()
{
	last_dir = same_dir_count = 0;
	MiniMenuItem& m = menu[cursor];
	if(m.kind == ITEM_MENU)
		Set((MiniMenuItem *)m.data);
	else {
		edit = !edit;
		Sync();
	}
}

struct MyApp : TopWindow {
	virtual void LeftDown(Point p, dword keyflags);
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void Paint(Draw& w);
};

void MyApp::LeftDown(Point p, dword keyflags)
{
	minigui.Select();
	Refresh();
}

void MyApp::MouseWheel(Point p, int zdelta, dword keyflags)
{
	minigui.Delta(sgn(zdelta));
	Refresh();
}

void MyApp::Paint(Draw& w)
{
	w.DrawRect(GetSize(), White());
	for(int linei = 0; linei < LINES; linei++) {
		int cy = Courier(20).GetCy();
		w.DrawText(10, linei * cy + 10, framebuffer[linei], Courier(20), Black(), COLUMNS);
	}
}

int n = 1234, f;
int  b;
int  en;
char h[20];

extern MiniMenuItem test[];

MiniMenuItem test2[] = {
	{ ITEM_MENU, "Main menu", &test },
	{ ITEM_INT, "Integer edit", &n },
	{ ITEM_ENDMENU },
};

MiniMenuItem test[] = {
	{ ITEM_INT, "Integer edit", &n, 200, 700 },
	{ ITEM_FLOAT, "Float edit", &f, 30, 300 },
	{ ITEM_MENU, "Submenu", &test2 },
	{ ITEM_MENU, "Submenu", &test2 },
	{ ITEM_MENU, "Submenu", &test2 },
	{ ITEM_MENU, "Submenu", &test2 },
	{ ITEM_ENUM, "Bool", &b, 0, 0, "On\0Off\0" },
	{ ITEM_ENUM, "Enum", &en, 0, 0, "One\0Two\0Three\0" },
//	{ ITEM_TEXT, "Text", h, 20, 0 },
	{ ITEM_ENDMENU },
};

#define MENU(x)                     MiniMenuItem x[] =
#define INT(text, var, min, max)    { ITEM_INT, text, &var, min, max },
#define FLOAT(text, var, min, max)  { ITEM_FLOAT, text, &var, min, max },
#define SUBMENU(text, menu)         { ITEM_MENU, text, &menu },
#define ENUM(text, var, list)       { ITEM_ENUM, text, &var, 0, 0, list },

MENU(First) {
	INT("Integer", n, 1, 10)
	INT("Float", f, 1, 10)
	ENUM("Enum", en, "ON\0OFF\0NOTHING")
	SUBMENU("Test", test)
};

GUI_APP_MAIN
{
	minigui.Set(First);
	
	MyApp().Run();
}
