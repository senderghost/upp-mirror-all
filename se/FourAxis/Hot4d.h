#ifndef _FourAxis_Hot4d_h_
#define _FourAxis_Hot4d_h_

#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

#define LAYOUTFILE <FourAxis/dlg.lay>
#include <CtrlCore/lay.h>

VectorMap<String, Ctrl *> GetCtrlMap(Ctrl& parent);
void SetValues(Ctrl& parent, const ValueMap& json);
ValueMap GetValues(Ctrl& parent);

struct Shape : ParentCtrl {
	virtual Vector<Pointf> Get() = 0;
	virtual void     Load(const ValueMap& json) = 0;
	virtual ValueMap Save() = 0;
};

struct Rod : WithRodLayout<Shape> {
	virtual Vector<Pointf> Get();
	virtual void     Load(const ValueMap& json);
	virtual ValueMap Save();

	typedef Rod CLASSNAME;

	Rod();
};

struct Text : WithTextLayout<Shape> {
	typedef Text CLASSNAME;

	virtual Vector<Pointf> Get();
	virtual void     Load(const ValueMap& json);
	virtual ValueMap Save();

	Text();
};


struct FourAxisDlg : WithFourAxisLayout<TopWindow> {
	typedef FourAxisDlg CLASSNAME;
	
	Rod  rod;
	Text text;

	Shape& CurrentShape();
	
	void Type();
	void Sync();
	void Save();

	FourAxisDlg();
};

#endif
