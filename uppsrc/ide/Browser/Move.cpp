#include "Browser.h"

class MoveTopicDlg : public WithMoveTopicLayout<TopWindow> {
	typedef MoveTopicDlg CLASSNAME;

public:
	MoveTopicDlg();
};

MoveTopicDlg::MoveTopicDlg()
{
	CtrlLayoutOKCancel(*this, "");
	
}

void TopicEditor::MoveTopic()
{
	if(!topic.IsCursor())
		return;
	TopicDlg<WithMoveTopicLayout<TopWindow> > d("Move topic");
	String p = GetCurrentTopicPath();
	String tn;
	int    lng;
	ParseTopicFileName(p, tn, lng);
	d.topic <<= tn;
	d.lang <<= lng;
	if(d.Run() != IDOK)
		return;
	String np = AppendFileName(grouppath, d.GetName());
	if(FindFile(np)) {
		Exclamation("Target file aready exists!");
		return;
	}
	Flush();
	FileMove(p, np);
	InvalidateTopicInfoPath(p);
	InvalidateTopicInfoPath(np);
	Open(grouppath);
	Load(np);
	SaveInc();
	topic.FindSetCursor(GetFileTitle(np));
	editor.SetFocus();
	serial++;
}
