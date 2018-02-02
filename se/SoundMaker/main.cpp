#include <CtrlLib/CtrlLib.h>
#include <Synth/Synth.h>

#define LAYOUTFILE <SoundMaker/SoundMaker.lay>
#include <CtrlCore/lay.h>

using namespace Upp;

struct SoundMakerDlg : WithSoundMakerLayout<TopWindow> {
	typedef SoundMakerDlg CLASSNAME;
	SoundMakerDlg();
	
	ADSR adsr, adsr1, adsr2, adsrf, adsrn;
	
	Button tone[72];
};

void SetupSlider(EditDouble& e, SliderCtrl& slider, double min, double max)
{
	slider.MinMax(0, 1000);
	slider << [=, &e, &slider] {
		double x = (double)~slider / 1000;
		DDUMP(x);
		x = x*x*x;
		DDUMP(x);
		DDUMP(max - min);
		e <<= min + (max - min) * x;
	};
}

void SetupADSR(ADSR& adsr, SliderCtrl& a, SliderCtrl& d, SliderCtrl& s, SliderCtrl& r)
{
	a.MinMax(0, 1000) << [&] { adsr.attack = (double)~a / 1000.0; };
	a <<= 0;
	d.MinMax(0, 1000) << [&] { adsr.decay = (double)~d / 1000.0; };
	d <<= 0;
	s.MinMax(0, 100) << [&] { adsr.sustain = 1 - (double)~s / 100.0; };
	s <<= 0;
	r.MinMax(0, 3000) << [&] { adsr.release = (double)~r / 1000.0; };
	r <<= 0;
}

SoundMakerDlg::SoundMakerDlg()
{
	CtrlLayout(*this, "");
	
	cm1 <<= 1.23;
	beta1 <<= 0;

	cm2 <<= 1;
	beta2 <<= 0;

	cmf <<= 1;
	betaf <<= 0;
	
	betan <<= 0;
	
	SetupADSR(adsr, a, d, s, r);
	SetupADSR(adsr1, a1, d1, s1, r1);
	SetupADSR(adsr2, a2, d2, s2, r2);
	SetupADSR(adsrf, af, df, sf, rf);
	
	SetupSlider(cm1, cm1_slider, 0.001, 1000);
	SetupSlider(beta1, beta1_slider, 0, 20);

	SetupSlider(cm2, cm2_slider, 0.001, 1000);
	SetupSlider(beta2, beta2_slider, 0, 20);

	SetupSlider(cmf, cmf_slider, 0.001, 1000);
	SetupSlider(betaf, betaf_slider, 0, 20);

	SetupSlider(betan, betan_slider, 0, 20);
	
	sound <<= "{1} a0.01d0.1s0.5r1";
	
	for(int i = 0; i < 72; i++)
		tone[i] << [=] {
			try {
				String s = ~~sound;
				FMPatch t;
				t.m1 = ~cm1;
				t.beta1 = ~beta1;
				t.m2 = ~cm2;
				t.beta2 = ~beta2;
				t.mf = ~cmf;
				t.betaf = ~betaf;
				t.betan = ~betan;
				t.adsr = adsr;
				t.adsr1 = adsr1;
				t.adsr2 = adsr2;
				t.adsrf = adsrf;
				Play(0.5, 65.406 * exp2(i / 12.0), 0.5, t);
			}
			catch(...) {}
		};
	
	test << [=] {
		try {
			String s = ~~sound;
			CParser p(s);
			while(!p.IsEof()) {
				Instrument t;
				t.Read(p);
				Play(0.3, 500, 0.5, t);
				if(!p.Char(';'))
					break;
			}
		}
		catch(...) {}
	};
}

// {1 1 1 1 0.5} [1]@1^10a0.05d0.3s0.3r3;{1 1 1 1 0.5}@1.05 [1]@2^12 a0.05d0.3s0.3r3

GUI_APP_MAIN
{
	InitSoundSynth();
	
	SoundMakerDlg().Run();
	
	CloseSoundSynth();
}
