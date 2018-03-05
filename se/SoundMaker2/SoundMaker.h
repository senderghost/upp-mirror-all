#ifndef _SoundMaker2_SoundMaker_h_
#define _SoundMaker2_SoundMaker_h_

#include <CtrlLib/CtrlLib.h>
#include <Synth2/Synth.h>

#define LAYOUTFILE <SoundMaker2/SoundMaker.lay>
#include <CtrlCore/lay.h>

using namespace Upp;

struct OperatorCtrl : WithOperatorLayout<ParentCtrl> {
	void Set(FMOP op);
	FMOP Get() const;
	
	OperatorCtrl();
};

struct SoundMakerDlg : WithSoundMakerLayout<TopWindow> {
	typedef SoundMakerDlg CLASSNAME;
	SoundMakerDlg();

	StaticRect timber;
	
	Vector<Tuple<EditDouble *, SliderCtrl *, double>> param;
	
	Button tone[72];
	
	TimeCallback       tm;
//	Vector<SoundPoint> sp;
	int                tm0 = 0;
	double             f = 440;
	
	OperatorCtrl       op[2];


	void Sync();
	void AddParam(const char *id, EditDouble& p, double max);
	void Param();
	
	Value  Get() const;
	void   Set(const Value& v);

	String GetJSON() const;
	void   SetJSON(const String& h);
};

#endif
