#include "Hot4d.h"

Path Wing::Get()
{
	Path r;
	
	airfoil.Render(r, 200, Pointf(20, 20));
	
	return r;
}

Wing::Wing()
{
	CtrlLayout(*this);
}


