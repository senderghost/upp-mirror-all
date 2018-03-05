#include "SoundMaker.h"

SoundMakerDlg::SoundMakerDlg()
{
	CtrlLayout(*this, "");

	{
		FMOP op;
		op.duration = 10000;
		op.attack = 1.01;
		op.decay = 0.999;
		op.release = 0.9999;
		op.sustain = 0.5;
		op.volume = 1;
		op.f = 0.1;
		
		this->op[0].Set(op);
	}
	
	{
		FMOP op;
		op.volume = 200;
		op.duration = 10000;
		op.attack = 1.01;
		op.decay = 0;
		op.release = 0.9995;
		op.sustain = 1;
		op.volume = 1;
		op.f = 0.3;

		this->op[1].Set(op);
	}

	/*		s.op[0] = op;
			
			s.op[1].f = 0.3;
			s.op[1].volume = 200;
			s.op[1].attack = 1.01;
			s.op[1].decay = 0;
			s.op[1].sustain = 1;
			s.op[1].release = 0.9995;
			s.op[1].duration = 10000;*/

		
	for(int i = 0; i < 72; i++)
		tone[i] << [=] {
			Sound s;
			s.op[0] = this->op[0].Get();
			s.op[1] = this->op[1].Get();
			SetChannel(0, s, true);
		};
/*		
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
*/	
	test << [=] {
		Sound s;
/*		s.f = 110;
		s.duration = 0.5;
		s.op[0].decay = 0.5;
		s.op[0].release = 0.5;
		s.op[0].sustain = 0;
		s.op[1].f = 0.5;
		s.op[1].volume = 5;
		s.op[1].decay = 0.4;
		s.op[1].sustain = 0;
		s.op[1].release = 2;*/
		SetChannel(0, s, true);
/*		sp.Clear();
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
		Render(1, sp, 0, f);*/
	};
	
//	list.WhenSel << [=] { Sync(); };
	
//	Sync();

	tm.Set(-1, [=] {
//		Render(1, sp, msecs(tm0), f);
	});
}
/*
void SoundMakerDlg::AddParam(const char *id, EditDouble& p, double maxval)
{
	list.AddCtrl(id, p);
	SliderCtrl& slider = *(SliderCtrl *)p.GetNext();
	slider.MinMax(10000, 0);
	slider << [=, &p, &slider] { p <<= maxval * (int)~slider / 10000; };
	p << [=, &p, &slider] { Sync(); };
	param.Add(MakeTuple(&p, &slider, maxval));
}
String SoundMakerDlg::GetJSON() const
{
	return AsJSON(Get());
}

void SoundMakerDlg::SetJSON(const String& s)
{
	Set(ParseJSON(s));
}
*/

GUI_APP_MAIN
{
	InitSoundSynth();

			Sound s;
			FMOP op;
			op.duration = 0;
			op.attack = 1.01;
			op.decay = 0.999;
			op.release = 0.9999;
			op.sustain = 0.5;
			op.volume = 1;
			op.f = 0.1;
			s.op[0] = op;
			
			s.op[1].f = 0.3;
			s.op[1].volume = 200;
			s.op[1].attack = 1.0001;
			s.op[1].decay = 0;
			s.op[1].sustain = 1;
			s.op[1].release = 0.9995;
			s.op[1].duration = 1000000;

			SetChannel(0, s, true);

	SoundMakerDlg dlg;

//	dlg.SetJSON(LoadFile(GetHomeDirFile("sound.json")));
	dlg.Run();
//	SaveFile(GetHomeDirFile("sound.json"), dlg.GetJSON());
	
	CloseSoundSynth();
}
