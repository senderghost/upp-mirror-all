#include "SoundMaker.h"

// 277.180972598656:L1V100f1r0A100D100S100R100:L99999V0f1r0A100D100S100R100:L99999V0f1r0A100D100S100R100

bool SoundMakerDlg::Key(dword key, int count)
{
	if(key == K_CTRL_V) {
		Sound s;
		s.Load(ReadClipboardText());
		Set(s);
	}
	return false;
}

void SoundMakerDlg::Set(const Sound& s)
{
	for(int i = 0; i < OPCOUNT; i++) {
		this->op[i].Set(s.op[i]);
		reverb <<= s.reverb;
		delay <<= s.delay;
	}
}

SoundMakerDlg::SoundMakerDlg()
{
	CtrlLayout(*this, "");

	Sound s;
	Set(s);

	for(int i = 0; i < 72; i++)
		tone[i] << [=] {
			Sound s;
			for(int i = 0; i < OPCOUNT; i++)
				s.op[i] = op[i].Get();
			s.reverb = ~reverb;
			s.delay = ~delay;
			s.f = 65.406 * exp2(i / 12.0) / s.op[0].f;
			SetChannel(0, s);
		
			WriteClipboardText(s.Save());

			SoundGen sg;
			sg.Start(s);

			Vector<float> data;
			for(int t = 0; t < 2 * 44100; t++)
				data.Add(sg.Get());
			
			scope.Pick(pick(data));
		};

	paste << [=] {
		Sound s;
		s.Load(ReadClipboardText());
		Set(s);
	};
}

GUI_APP_MAIN
{
	InitSoundSynth();

	SoundMakerDlg dlg;

	dlg.Run();
	
	CloseSoundSynth();
}

// 130:L0.25V100f1r0A70D50S90R30:L99V90f1r0A70D50S0R100:L99V92f1r0A100D100S100R100
// 391.99:L0.25V100f1r0A55D50S100R30:L99V70f7r0A100D50S100R100:L99V110f2r0A100D100S100R100
// 277.18:L0.25V100A55D50R30:V70f7D50:V110f2

// explosion 3951.04:L0.25V100r-20A90D35S30R35:V120D20S20B:V2f2

// explosion 146.83:L0.25V100r-20A90D35S30R35:V120D20S20B:V100f2A90D43S0N

// gun fire 146.83:L0.25V100r-14A90D35S30R35:V150D30S20B:V100f2A90D43S0N

// bass 130.81:L0.25V90A90D35S30R35:V160D40S20R20:V100f2A90D43S0R40