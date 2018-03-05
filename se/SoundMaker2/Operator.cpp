#include "SoundMaker.h"

OperatorCtrl::OperatorCtrl()
{
	CtrlLayout(*this);
}

void OperatorCtrl::Set(FMOP op)
{
	duration <<= op.duration;
	volume <<= op.volume;
	f <<= op.f;
	fdrift <<= op.fdrift;
	attack <<= op.attack;
	decay <<= op.decay;
	sustain <<= op.sustain;
	release <<= op.release;
}

FMOP OperatorCtrl::Get() const
{
	FMOP op;
	op.duration = ~duration;
	op.volume = ~volume;
	op.f = ~f;
	op.fdrift = ~fdrift;
	op.attack = ~attack;
	op.decay = ~decay;
	op.sustain = ~sustain;
	op.release = ~release;
	return op;
}
