#include <CtrlLib/CtrlLib.h>
#include <Synth/Synth.h>

#define LAYOUTFILE <SoundMaker/SoundMaker.lay>
#include <CtrlCore/lay.h>

using namespace Upp;

struct SoundMakerDlg : WithSoundMakerLayout<TopWindow> {
	typedef SoundMakerDlg CLASSNAME;
	SoundMakerDlg();
	
	Button tone[72];
};

SoundMakerDlg::SoundMakerDlg()
{
	CtrlLayout(*this, "");
	
	sound <<= "{1} a0.01d0.1s0.5r1";
	
	for(int i = 0; i < 72; i++)
		tone[i] << [=] {
			try {
				String s = ~~sound;
				CParser p(s);
				while(!p.IsEof()) {
					Instrument t;
					t.Read(p);
					Play(0.5, 65.406 * exp2(i / 12.0), 0.5, t);
					if(!p.Char(';'))
						break;
				}
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
