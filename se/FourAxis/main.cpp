#include "Hot4d.h"

#define IMAGECLASS HotImg
#define IMAGEFILE <FourAxis/HotImg.iml>
#include <Draw/iml_source.h>

void FourAxisDlg::AddShape(Shape *l, Shape *r)
{
	shape.Add(l->GetId(), MakeTuple(l, r));
	type.Add(type.GetCount(), l->GetName());
	left.Add(*l);
	if(r)
		right.Add(*r);
}


FourAxisDlg::FourAxisDlg()
{
	CtrlLayout(*this, "4 axis CNC G-code generator");

	AddShape(rod, rod + 1);
	AddShape(text);
	AddShape(angle);
	AddShape(wing, wing + 1);
	AddShape(motor);
	AddShape(textpath);
	
	WhenClose = [=] { Exit(); };

	panel_width <<= 500;
	tower_distance <<= 700;
	left_gap <<= 80;
//	save_as << [=] { Save(); };
	
	speed <<= 140;
	
	for(auto i : { 1, 2, 3, 5, 10, 20, 30, 50, 100, 200, 500, 1000 })
		scale.Add(i, AsString(i) + " pixels / mm");
	scale <<= 5;

	type << [=] { Type(); };
	type <<= 0;
	
	tapered << [=] { Type(); };
	
	view.fa = this;
	view.Add(home.BottomPos(0, Zy(14)).LeftPos(0, Zy(14)));
	home.NoWantFocus();
	home.SetImage(HotImg::Home());
	home << [=] { Home(); };

	show_shape <<= true;
	show_arrows <<= true;
	show_wire <<= true;
	show_kerf <<= false;
	show_points <<= false;
	show_left <<= true;
	show_right <<= true;
	show_cnc <<= true;

	for(Ctrl *q = GetFirstChild(); q; q = q->GetNext())
		*q << [=] { Sync(); };

	for(int i = 0; i < shape.GetCount(); i++) {
		for(Ctrl *q = shape[i].a->GetFirstChild(); q; q = q->GetNext())
			*q << [=] { Sync(); };
		if(shape[i].b)
			for(Ctrl *q = shape[i].b->GetFirstChild(); q; q = q->GetNext())
				*q << [=] { Sync(); };
	}

	kerf.NullText("0");
	
	Type();
	
	Sizeable().Zoomable();
}

Shape& FourAxisDlg::CurrentShape(bool right)
{
	int q = ~type;
	if(q < 0 || q >= shape.GetCount()) return rod[0];
	auto t = shape[~type];
	return t.a->IsTapered() && tapered && right ? *t.b : *t.a;
}

void FourAxisDlg::Type()
{
	for(int i = 0; i < shape.GetCount(); i++) {
		auto t = shape[i];
		bool b = ~type == i;
		t.a->Show(b);
		if(t.a->IsTapered())
			t.b->Show(b && tapered);
	}
	tapered.Show(CurrentShape().IsTapered());
	
	bool b = tapered;
	
	tower_distance_lbl.Show(b);
	panel_width_lbl.Show(b);
	left_gap_lbl.Show(b);
	left_gap.Show(b);
	panel_width.Show(b);
	tower_distance.Show(b);
	
	show_left.Show(b);
	show_right.Show(b);

	Sync();
}

bool FourAxisDlg::Key(dword key, int count)
{
	if(key == K_HOME) {
		Home();
		return true;
	}
	return TopWindow::Key(key, count);
}

void FourAxisDlg::Exit()
{
#ifndef _DEBUG0
	bool ok;
	if(filepath.GetCount() == 0)
		ok = SaveAs();
	else
		ok = Save();
	if(!ok && !PromptYesNo("File is not saved. Do you really want to quit?"))
		return;
#endif
	Close();
}

void FourAxisDlg::Serialize(Stream& s)
{
	SerializeGlobalConfigs(s);
	s % lrufile;
	SerializePlacement(s);
	s % show_shape % show_wire % show_kerf;
}

void FourAxisDlg::Layout()
{
	Sync();
}

void Shape::SyncView()
{
	Ctrl *q = this;
	while(q) {
		auto *h = dynamic_cast<FourAxisDlg *>(q);
		if(h) {
			h->Sync();
			break;
		}
		q = q->GetParent();
	}
}

GUI_APP_MAIN
{
#ifdef _DEBUG0
	void TestMix();
	TestMix();
	return;
#endif
	
#ifdef _DEBUG0
	TestKerf();
	return;
#endif

//	SetVppLogName("c:/xxx/fa/" + AsString(GetCurrentProcessId()) + ".log");
	
	DUMP("A");

	FourAxisDlg dlg;

	DUMP("B");

	LoadFromFile(dlg);

	DUMP("C");

	const Vector<String>& cmdline = CommandLine();
	int argc = cmdline.GetCount();

	dlg.OpenMain();

	if(argc == 1 && ToLower(GetFileExt(cmdline[0])) == ".nc") {
		if(!dlg.OpenS(cmdline[0]))
			return;
	}

	DUMP("D");

	Ctrl::EventLoop();
	
	StoreToFile(dlg);
}
