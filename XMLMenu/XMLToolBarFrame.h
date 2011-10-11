#ifndef _XMLToolBarFrame_h_
#define _XMLToolBarFrame_h_

#include "XMLToolBarCtrl.h"

NAMESPACE_UPP

// XMLToolBarFrame : a frame containing multiple XMLToolBars
// arranged in rows (for BAR_TOP and BAR_BOTTOM) or columns
// (for BAR_LEFT and BAR_RIGHT)
class XMLToolBarFrame : public CtrlFrame, public Pte<XMLToolBarFrame>
{
	friend class XMLToolBarCtrl;
	private:
		Ptr<Ctrl> parent;
	
		// position mapper :
		//        row            hpos idx
		// maps each toolbar with its absolute position
		VectorMap<int, VectorMap<int, int> >posMapper;
		
		// total frame size
		int frameSize;
		
		// frame rectangle for container
		Rect frameRect;
		
		// points for painting frame limits
		Point frameP11, frameP12;
		Point frameP21, frameP22;
		
		// toolbars container
		ParentCtrl toolBarContainer;
		
		// alignment of toolbarline
		XMLToolBarCtrl::XMLToolBarState toolBarState;
	
		// the toolbars on this frame
		Array<Ptr<XMLToolBarCtrl> >toolBars;
		
		// the positions inside a frame, as Size struct
		// where cx is position inside a row and cy is the row
		// positions get dynamically changed by XMLToolBarFrama layouting
		// positions are given in ODD numbers, so we can dynamically insert
		// between them before repositioning
		Array<Size> relativePositions;
		
		// dragging stuffs
		bool dragging;
		
		// current drag point
		Point dragPoint;
		
		// position of dragged toolbar before dragging
		Ctrl::LogPos toolBarPos;
		
		// current dragging toolbar
		Ptr<XMLToolBarCtrl> dragToolBar;
		
		// predocking stuffs
		bool preDocking;
		Rect preDockRect;
		
	protected:
	
		// recalculates relative toolbar's positions
		// needed after adding or removing a toolbar
		void Reposition(void);
		
		// frame layout functions
		virtual void FrameLayout(Rect &r);
		virtual void FrameAddSize(Size &s);
	
		// frame painting
		virtual void FramePaint(Draw& w, const Rect& r);
		
		// frame insertion/removing handlers
		virtual void FrameAdd(Ctrl &_parent);
		virtual void FrameRemove(void);
		
		// find index of a docked XMLToolBar; -1 if not found
		int FindIndex(XMLToolBarCtrl &tb);
		
		// gets dock target giving point in frame
		bool GetDockTarget(XMLToolBarCtrl &tb, Point p, int &dockLine, bool &insert, int &col);

		// docks a toolbar into this frame
		// eventually undocks it from other frames, unfloats it or open it
		XMLToolBarFrame &Dock(XMLToolBarCtrl &tb, int row, int col);
		XMLToolBarFrame &Dock(XMLToolBarCtrl &tb, Point p);

		// closes (undocking it) an XMLToolBar from this frame
		XMLToolBarFrame &Undock(XMLToolBarCtrl &tb);
		
	public:
	
		XMLToolBarFrame(XMLToolBarCtrl::XMLToolBarState align);
		~XMLToolBarFrame();
		
		// lays toolbars inside frame
		virtual void Layout(void);
		
		// gets toolbar align
		XMLToolBarCtrl::XMLToolBarState GetToolBarState() { return toolBarState; }
		
		// gets toolbar at given mouse point; point is in parent rect coordinates
		// returns NULL if not grabbed a toolbar
		XMLToolBarCtrl *GetToolBarAt(Point p);
		
		// gets isDragging flag
		bool GetDragging(void) { return dragging; }

		// check whether a point is inside the frame
		bool Contains(Point p);
		
		// pre-docking handling
		XMLToolBarFrame &PreDock(XMLToolBarCtrl &tb, Point p);
		XMLToolBarFrame &UnPreDock(XMLToolBarCtrl &tb);

};

END_UPP_NAMESPACE

#endif
