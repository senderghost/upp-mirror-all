#include "XMLToolBarFloating.h"
#include "XMLToolBarCtrl.h"
#include "WithXMLMenu.h"

NAMESPACE_UPP

// handler for window drag events
void XMLToolBarFloating::WindowDragged(DragWindow::DragEvent e, Point p)
{
	XMLMenuInterface *iFace = toolBar->GetInterface();
	if(iFace && e == DragWindow::DRAG_DRAG)
		iFace->FloatingDraggedEvent(*toolBar, p);
}

XMLToolBarFloating::XMLToolBarFloating(XMLToolBarCtrl &tb, Point p)
{
	// stores toolbar
	toolBar = &tb;
	
	// sets size and position of container
	ToolWindow();
	Size sz = toolBar->GetSquaredSize();
	int x = p.x - sz.cx / 2;
	int y = p.y + 5;
	SetRect(x, y, sz.cx, sz.cy);
	AddChild(&toolBar->SizePos());
	Layout();
	OpenMain();
	TopMost(true, true);
}

XMLToolBarFloating::~XMLToolBarFloating()
{
	RemoveChild(toolBar);
	Close();
}

END_UPP_NAMESPACE
