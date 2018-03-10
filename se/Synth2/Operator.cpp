#include "Synth.h"

Sound::Sound()
{
	op[0].duration = 1;
	op[0].volume = 100;
}

String Aformat(double x)
{
	return (int)x == x ? AsString(x) : Format("%.2f", x);
}

String FMOP::Save() const
{
	String r;

	auto Put = [&](char c, double val, double def) {
		if(val != def)
			r << c << Aformat(val);
	};

	Put('L', duration, 99);
	Put('V', volume, 0);
	Put('f', f, 1);
	Put('r', fdrift, 0);
	Put('A', attack, 100);
	Put('D', decay, 100);
	Put('S', sustain, 100);
	Put('R', release, 100);
	
	return r + decode(waveform, WAVEFORM_SQUARE, "Q",
	                            WAVEFORM_TRIANGLE, "T",
	                            WAVEFORM_SAWTOOTH, "W",
	                            WAVEFORM_BROWN, "B",
	                            WAVEFORM_WHITE, "N", "");
}

const char * FMOP::Load(const char *s)
{
	auto Get = [&](double& r) {
		try {
			CParser p(s + 1);
			if(p.IsDouble())
				r = p.ReadDouble();
			s = p.GetPtr();
		}
		catch(CParser::Error) {}
	};
	
	while(*s) {
		if(*s == ':') {
			s++;
			break;
		}
		switch(*s) {
		case 'L': Get(duration); break;
		case 'V': Get(volume); break;
		case 'f': Get(f); break;
		case 'r': Get(fdrift); break;
		case 'A': Get(attack); break;
		case 'D': Get(decay); break;
		case 'S': Get(sustain); break;
		case 'R': Get(release); break;
		case 'Q': waveform = WAVEFORM_SQUARE;
		case 'T': waveform = WAVEFORM_TRIANGLE;
		case 'W': waveform = WAVEFORM_SAWTOOTH;
		case 'B': waveform = WAVEFORM_BROWN;
		case 'N': waveform = WAVEFORM_WHITE;
		default: s++;
		}
	}
	return s;
}

String Sound::Save() const
{
	String r;
	r << Aformat(f) << ':';
	for(int i = 0; i < OPCOUNT; i++) {
		if(i)
			r << ':';
		r << op[i].Save();
	}
	return r;
}

void Sound::Load(const char *s)
{
	try {
		CParser p(s);
		if(p.IsDouble())
			f = p.ReadDouble();
		p.Char(':');
		s = p.GetPtr();
		for(int i = 0; i < OPCOUNT; i++)
			s = op[i].Load(s);
	}
	catch(CParser::Error) {}
}
