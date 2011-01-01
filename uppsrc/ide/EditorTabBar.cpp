#include "ide.h"

EditorTabBar::EditorTabBar()
{
	Stacking();
	AutoScrollHide(false);
	FileIcons(false);
	SetBorder(1);
}

String EditorTabBar::GetFile(int n) const
{
	return tabs[n].key;
}

bool EditorTabBar::FindSetFile(const String& fn)
{
	int n = FindKey(fn);
	if(n >= 0)
	{
		SetCursor(n);
		return true;
	}
	return false;
}

void EditorTabBar::SetAddFile(const String& fn)
{
	if(IsNull(fn))
		return;
	if(FindSetFile(fn))
		return;
	AddFile(WString(fn), true);
}

void EditorTabBar::RenameFile(const String& fn, const String& nn)
{
	FileTabs::RenameFile(WString(fn), WString(nn));
}
