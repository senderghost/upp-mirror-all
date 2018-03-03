#include "SoundMaker.h"

SoundMakerDlg::SoundMakerDlg()
{
	CtrlLayout(*this, "");
	
	for(int i = 0; i < 72; i++)
		tone[i] << [=] {
			sp.Clear();
			for(int i = 0; i < list.GetCount(); i++) {
				SoundPoint& p = sp.Add();
				p.duration = list.Get(i, "duration");
				p.fc = 1;
				p.mod_fc = list.Get(i, "fmod");
				p.beta = list.Get(i, "beta");
				p.volume = list.Get(i, "volume");
				p.white_noise = list.Get(i, "white");
				p.brown_noise = list.Get(i, "brown");
			}
			tm0 = msecs();
			f = 65.406 * exp2(i / 12.0);
			Render(1, sp, 0, f);
		};
		
	AddParam("duration", duration, 3000);
	AddParam("fmod", fmod, 2);
	AddParam("beta", beta, 12);
	AddParam("volume", volume, 1);
	AddParam("white", white, 1);
	AddParam("brown", brown, 1);
	
	list.AddColumnAt(0, "Duration");
	
	add << [=] {
		if(list.GetCount() == 0) {
			list.Add();
			list.GoEnd();
			duration <<= 500;
			fmod <<= 1;
			beta <<= 0;
			volume <<= 1;
			white <<= 0;
			brown <<= 0;
			Sync();
			return;
		}
		int ii = list.GetCursor();
		if(ii < 0)
			ii = list.GetCount();
		Vector<Value> v = list.GetLine(ii);
		list.Insert(++ii, v);
		list.SetCursor(ii);
	};
	
	remove << [=] {
		list.DoRemove();
	};
	
	test << [=] {
		sp.Clear();
		for(int i = 0; i < list.GetCount(); i++) {
			SoundPoint& p = sp.Add();
			p.duration = list.Get(i, "duration");
			p.fc = 1;
			p.mod_fc = list.Get(i, "fmod");
			p.beta = list.Get(i, "beta");
			p.volume = list.Get(i, "volume");
			p.white_noise = list.Get(i, "white");
			p.brown_noise = list.Get(i, "brown");
		}
		tm0 = msecs();
		f = 440;
		Render(1, sp, 0, f);
	};
	
	list.WhenSel << [=] { Sync(); };
	
	Sync();

	tm.Set(-1, [=] {
		Render(1, sp, msecs(tm0), f);
	});
}

void SoundMakerDlg::AddParam(const char *id, EditDouble& p, double maxval)
{
	list.AddCtrl(id, p);
	SliderCtrl& slider = *(SliderCtrl *)p.GetNext();
	slider.MinMax(10000, 0);
	slider << [=, &p, &slider] { p <<= maxval * (int)~slider / 10000; };
	p << [=, &p, &slider] { Sync(); };
	param.Add(MakeTuple(&p, &slider, maxval));
}

void SoundMakerDlg::Sync()
{
	bool b = list.IsCursor();
	for(auto& p : param) {
		p.a->Enable(b);
		p.b->Enable(b);
		*p.b <<= int(10000 * (double)~*p.a / p.c);
	}
}

Value SoundMakerDlg::Get() const
{
	ValueArray va;
	for(int i = 0; i < list.GetCount(); i++)
		va.Add(list.GetMap(i));
	return va;
}

void SoundMakerDlg::Set(const Value& v)
{
	list.Clear();
	if(!IsValueArray(v))
		return;
	ValueArray va = v;
	for(int i = 0; i < va.GetCount(); i++)
		if(IsValueMap(va[i]))
			list.AddMap(va[i]);
}

String SoundMakerDlg::GetJSON() const
{
	return AsJSON(Get());
}

void SoundMakerDlg::SetJSON(const String& s)
{
	Set(ParseJSON(s));
}

// {1 1 1 1 0.5} [1]@1^10a0.05d0.3s0.3r3;{1 1 1 1 0.5}@1.05 [1]@2^12 a0.05d0.3s0.3r3

struct Test : TopWindow {
	double mod, beta;
	double t0;
	Sound s;
	
	void Do(Point p, bool first) {
		Size sz = GetSize();
		mod = 2 * (double)p.x / sz.cx;
		beta = 10 * (double)p.y / sz.cy;
		s.volume = 0.4;
		s.fc = 440;
		s.mod_fc = mod * s.fc;
		s.beta = beta * s.fc;
		t0 = msecs();
		SetChannel(0, s, first);
		Refresh();
	}
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		w.DrawRect(sz, White());
		w.DrawText(10, 10, String() << mod << " " << beta);
	}
	
	virtual void LeftDown(Point p, dword keyflags) {
		Do(p, true);
	}
	
	virtual void MouseMove(Point p, dword keyflags) {
		if(keyflags & K_MOUSELEFT)
			Do(p, false);
	}
	
	TimeCallback tm;
	
	Vector<SoundPoint> tst;
	int tm0;
	
	Test() {
		Do(Point(0, 0), false);
		if(0) {
			tm0 = msecs();
			SoundPoint s;
			s.fc = 440;
			s.mod_fc = 0.33333333 * s.fc;
			s.beta = 2 * s.fc;
			s.volume = 0.7;
			s.duration = 4000;
			tst.Add(s);
			s.fc = 420;
			s.beta = 0;
			s.duration = 5000;
			s.volume = 0.5;
			s.brown_noise = 0.3;
			s.white_noise = 0.1;
			tst.Add(s);
		}
		
		tm.Set(-10, [=] {
			if(GetMouseLeft()) t0 = msecs();
			s.volume = max(0.0, 0.4 * (500 - msecs(t0)) / 500);
			SetChannel(0, s);
			Render(1, tst, msecs(tm0));
		});
	}
};

GUI_APP_MAIN
{
	InitSoundSynth();
/*
	Sound s;
	for(int i = 1000; i > 800; i -= 10) {
		s.fc = i;
		s.volume = 0.5;
		SetChannel(0, s);
		Sleep(10);
	}

	s.mod_fc = 0.33333333 * s.fc;
	s.beta = 2 * s.fc;
	SetChannel(0, s);
*/
//	Sound s;
//	s.brown_noise = 0.1;
//	SetChannel(1, s);

	SoundMakerDlg dlg;

	dlg.SetJSON(LoadFile(GetHomeDirFile("sound.json")));
	dlg.Run();
	SaveFile(GetHomeDirFile("sound.json"), dlg.GetJSON());
	
	CloseSoundSynth();
}
