template <class O, class Res, class M classA classP>
Function<Res (A_)> callbackn(O *object, Res (M::*method)(A_ cm_ P_) P_p_)
{
	return [=](A_a_) { (object->*method)(a_ cm_ p_); };
}

template <class O, class Res, class M classA classP>
Function<Res (A_)> callbackn(O *object, Res (M::*method)(A_ cm_ P_) const P_p_)
{
	return [=](A_a_) { (object->*method)(a_ cm_ p_); };
}

template <class O, class Res, class M classA classP>
Function<Res (A_)> ptebackn(O *object, Res (M::*method)(A_ cm_ P_) P_p_)
{
	Ptr<O> ptr = object;
	return [=](A_a_) { if(ptr) (ptr->*method)(a_ cm_ p_); };
}

template <class O, class Res, class M classA classP>
Function<Res (A_)> ptebackn(O *object, Res (M::*method)(A_ cm_ P_) const P_p_)
{
	Ptr<O> ptr = object;
	return [=](A_a_) { if(ptr) (object->*method)(a_ cm_ p_); };
}

#undef callbackn
#undef ptebackn
#undef classP
#undef P_
#undef P_p_
#undef p_