/*
 * GraphElement.h
 *
 *  Created on: 6 avr. 2012
 *      Author: didier
 */

#ifndef GRAPHELEMENT_H_
#define GRAPHELEMENT_H_


namespace GraphDraw_ns
{
	typedef enum {
		LEFT_OF_GRAPH  = 0x001,
		RIGHT_OF_GRAPH = 0x002,
		TOP_OF_GRAPH   = 0x010,
		BOTTOM_OF_GRAPH= 0x020,
		OVER_GRAPH     = 0x100
	} ElementPosition;

	enum {
		VERTICAL_MASK  = 0x00F,
		HORIZONTAL_MASK = 0x0F0,
		OVER_MASK       = 0xF00
	};

	typedef enum {
			REFRESH_FAST = 0,
			REFRESH_TOTAL
	} RefreshStrategy;


	class GraphElementParent {
		public:
			typedef GraphElementParent CLASSNAME;
			virtual void ScrollX( TypeScreenCoord xOffset) = 0;
			virtual void ScrollY( TypeScreenCoord yOffset) = 0;
			virtual void ZoomX(TypeScreenCoord left, TypeScreenCoord right) = 0;
			virtual void ZoomY(TypeScreenCoord top, TypeScreenCoord bottom) = 0;
			virtual void RefreshFromChild( RefreshStrategy doFastPaint ) = 0;
			virtual Value GetSeries() = 0;	
			virtual Value GetParentCtrl() = 0;	

			GraphElementParent() {}
			virtual ~GraphElementParent() {}
	};


	// ============================
	//    GraphElementFrame   CLASS
	// ============================
	class GraphElementFrame {
		public:
			Rect            _frame;    // Frame on which element is painted (absolute position in complete draw area)
			Rect            _overFrame;// Frame size used as SCALE=1 reference frame
			int             _width;    // width of GraphElement (in screen size)
			ElementPosition _pos;      // position in plot area
			int             _allowedPosMask;
			bool            _hide;     // true: is not drawn
			int             _stackingPriority; // 
			String          _name;

		public:
			GraphElementParent* _parent;
			Callback3<GraphElementFrame*, Point , dword > WhenLeftDown     ;
			Callback3<GraphElementFrame*, Point , dword > WhenLeftUp       ;
			Callback3<GraphElementFrame*, Point , dword > WhenLeftDouble   ;
			Callback3<GraphElementFrame*, Point , dword > WhenLeftDrag     ;
			Callback3<GraphElementFrame*, Point , dword > WhenRightDown    ;
			Callback3<GraphElementFrame*, Point , dword > WhenRightUp      ;
			Callback3<GraphElementFrame*, Point , dword > WhenRightDouble  ;
			Callback3<GraphElementFrame*, Point , dword > WhenRightDrag    ;
			Callback3<GraphElementFrame*, Point , dword > WhenMiddleDown   ;
			Callback3<GraphElementFrame*, Point , dword > WhenMiddleUp     ;

			GraphElementFrame()
			: _frame( 0, 0, 5, 5 )
			, _overFrame(_frame)
			, _width(5)
			, _pos(LEFT_OF_GRAPH)
			, _allowedPosMask(LEFT_OF_GRAPH | RIGHT_OF_GRAPH| BOTTOM_OF_GRAPH | TOP_OF_GRAPH | OVER_GRAPH )
			, _hide(false)
			, _stackingPriority(100)
			, _name("NAME NOT SET")
			, _parent(0)
			{}
			
			GraphElementFrame(GraphElementFrame* p)
			: _frame( 0, 0, 5, 5 )
			, _overFrame(p->_overFrame)
			, _width(p->_width)
			, _pos(LEFT_OF_GRAPH)
			, _allowedPosMask(p->_allowedPosMask)
			, _hide(p->_hide)
			, _stackingPriority(p->_stackingPriority)
			, _name("NAME NOT SET")
			, _parent(p->_parent)
			, WhenLeftDown    (p->WhenLeftDown)
			, WhenLeftDouble  (p->WhenLeftDouble  )
			, WhenLeftDrag    (p->WhenLeftDrag    )
			, WhenRightDown   (p->WhenRightDown   )
			, WhenRightDouble (p->WhenRightDouble )
			, WhenRightDrag   (p->WhenRightDrag   )
			, WhenMiddleDown  (p->WhenMiddleDown  )
			{}

			void AdjustToPlotRect(const Rect& plotRect)
			{
				if ( !IsOverGraph() ) {
					int xCenter = (plotRect.left + plotRect.right)/2;
					if ( (_frame.left < xCenter) && (xCenter < _frame.right) ) {
						_frame.left = plotRect.left;
						_frame.right = plotRect.right;
					}
					else {
						_frame.top = plotRect.top;
						_frame.bottom = plotRect.bottom;
					}
					Update();
				}
			}

			virtual ~GraphElementFrame() {}

			inline void SetName(const char* name) { _name = name; };
			virtual bool Contains(Point p) const { return _frame.Contains(p); }
			inline const Rect& GetFrame() const { return _frame; }
			inline void SetFrame(Rect v) { _frame = v; Update(); }
			inline const Rect& GetOverFrame() const { return _overFrame; }
			inline void SetOverFrame(Rect v) { _overFrame = v; }
			inline int GetElementWidth() { return _width; }
			inline ElementPosition GetElementPos() { return _pos; }
			//virtual void SetElementPos( ElementPosition v ) { _pos = v; }
			inline void SetAllowedPosMask( int v ) { _allowedPosMask = v; }
			inline void DisablePos( int v ) { _allowedPosMask &= ~v; }
			inline void SetStackingPriority( int v ) { _stackingPriority = v; }
			inline int GetStackingPriority( int v )  { return _stackingPriority; }

			inline bool IsVertical() const { return ((_pos & GraphDraw_ns::VERTICAL_MASK)!=0); }
			inline bool IsHorizontal() const { return ((_pos & GraphDraw_ns::HORIZONTAL_MASK)!=0); }
			inline bool IsOverGraph() const { return ((_pos & GraphDraw_ns::OVER_MASK)!=0); }
			inline bool IsHidden() const { return _hide; }
			inline void Hide( bool v=true ) { _hide = v; }
			
			bool operator<(const GraphElementFrame& b) const { return (_stackingPriority < b._stackingPriority); };
			bool operator>(const GraphElementFrame& b) const { return (_stackingPriority > b._stackingPriority); };

         // Paint element somewhere inside the graph area (legend, ...)
			// Offset and clipping are set with the '_frame' settings
			virtual void PaintOverGraph(Draw& dw, int scale) { };

			// Paint the element in his own area
			// There is no clipping ==> drawing can overlap plot or other elements
			virtual void PaintElement(Draw& dw, int scale) = 0;

			// Paint additionnal element stuff on PLOT AREA : grids, square zones,  anything you wan't
			// Painting zone is clipped so nothing can be drawn outside
			virtual void PaintOnPlot(Draw& dw, int otherWidth, int scale) {}
			virtual void Update() {}; // called when coordinates need update

			virtual GraphElementFrame* Clone() = 0;


			virtual GraphElementFrame* LeftDown   (Point p, dword keyflags) { WhenLeftDown   (this, p, keyflags); return 0;}
			virtual GraphElementFrame* LeftUp     (Point p, dword keyflags) { WhenLeftUp     (this, p, keyflags); return 0;}
			virtual GraphElementFrame* LeftDouble (Point p, dword keyflags) { WhenLeftDouble (this, p, keyflags); return 0;}
			virtual GraphElementFrame* LeftDrag   (Point p, dword keyflags) { WhenLeftDrag   (this, p, keyflags); return 0;}
			virtual GraphElementFrame* RightDown  (Point p, dword keyflags) { WhenRightDown  (this, p, keyflags); return 0;}
			virtual GraphElementFrame* RightUp    (Point p, dword keyflags) { WhenRightUp    (this, p, keyflags); return 0;}
			virtual GraphElementFrame* RightDouble(Point p, dword keyflags) { WhenRightDouble(this, p, keyflags); return 0;}
			virtual GraphElementFrame* RightDrag  (Point p, dword keyflags) { WhenRightDrag  (this, p, keyflags); return 0;}
			virtual GraphElementFrame* MiddleDown (Point p, dword keyflags) { WhenMiddleDown (this, p, keyflags); return 0;}
			virtual GraphElementFrame* MiddleUp (Point p, dword keyflags)   { WhenMiddleUp   (this, p, keyflags); return 0;}
			virtual GraphElementFrame* MouseMove  (Point p, dword keyflags) { return 0;}
			virtual GraphElementFrame* MouseWheel (Point p, int zdelta, dword keyflags) { return 0; };
			virtual Image  CursorImage(Point p, dword keyflags) { return GraphDrawImg::CROSS(); }
	};

	inline bool compareGraphElementFrame(const GraphElementFrame* a, const GraphElementFrame* b) { return *a < *b; }

	template<class DERIVED>
	class CRTPGraphElementFrame : public GraphElementFrame {
		public:
			CRTPGraphElementFrame() {}
			CRTPGraphElementFrame(CRTPGraphElementFrame& p) : GraphElementFrame(p) {}
			virtual ~CRTPGraphElementFrame() {}

			inline  DERIVED&  SetElementWidth(int v) { _width = v; return *static_cast<DERIVED*>(this); }
			virtual DERIVED&  SetElementPos(ElementPosition v) { _pos = v; return *static_cast<DERIVED*>(this); }
	};


	class BlankAreaElement : public CRTPGraphElementFrame< BlankAreaElement >
	{
		typedef BlankAreaElement CLASSNAME;
		public:
			BlankAreaElement() {}
			BlankAreaElement( BlankAreaElement& p) : CRTPGraphElementFrame< BlankAreaElement >(p) {}
			virtual ~BlankAreaElement() {}
			virtual void PaintElement(Draw& dw, int scale) { /* do noting */}
			virtual CLASSNAME* Clone() { return new CLASSNAME(*this); }
	};


	// ============================
	//    LabelElement   CLASS
	// ============================
	class LabelElement : public CRTPGraphElementFrame< LabelElement >
	{
		private:
		Upp::String _label;
		Font        _font;
		Color       _color;
		Color       _bckGndcolor;
		typedef CRTPGraphElementFrame< LabelElement >  _B;

		public:
		LabelElement() : _color( Blue() ), _bckGndcolor(Null) {}
		LabelElement(LabelElement& p) : _B(p), _color( p._color ), _bckGndcolor(p._bckGndcolor) {}
		virtual ~LabelElement() {}

		virtual LabelElement* Clone() { return new LabelElement(*this); };

		template<class T>	inline LabelElement& SetLabel(T& v) { _label = v; return *this; }
		template<class T>	inline LabelElement& SetFont(T& v) { _font = v; return *this; }
		template<class T>	inline LabelElement& SetTextColor(T v) { _color = v; return *this; }
		template<class T>	inline LabelElement& SetBckGndColor(T v) { _bckGndcolor = v; return *this; }

		inline const Upp::String& GetLabel() const { return _label; }

		virtual void PaintElement(Draw& dw, int scale)
		{
			if ( !_bckGndcolor.IsNullInstance() )
				dw.DrawRect( 0, 0, _B::GetFrame().GetWidth(), _B::GetFrame().GetHeight(), _bckGndcolor);

			Font scaledFont( _font );
			scaledFont.Height(scale*scaledFont.GetHeight());
			Size sz = GetTextSize(_label, scaledFont);
			switch(_B::GetElementPos()){
				case LEFT_OF_GRAPH:
					dw.DrawText( _B::GetElementWidth()*scale/2-sz.cy/2, _B::GetFrame().GetHeight()/2+sz.cx/2 , 900, _label, scaledFont, _color);
					break;
				case BOTTOM_OF_GRAPH:
					dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, scaledFont, _color);
					break;
				case TOP_OF_GRAPH:
					dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, scaledFont, _color);
					break;
				case RIGHT_OF_GRAPH:
					dw.DrawText( _B::GetElementWidth()*scale/2+sz.cy/2, _B::GetFrame().GetHeight()/2-sz.cx/2 , 2700, _label, scaledFont, _color);
					break;
				case OVER_GRAPH:
					break;
			}
		}
	};
//
//	// ============================
//	//    LabelElement   CLASS
//	// ============================
//	class RichLabelElement : public CRTPGraphElementFrame< RichLabelElement >
//	{
//		private:
//		RichText    _label;
//		Color       _bckGndcolor;
//		typedef RichLabelElement                          CLASSANME;
//		typedef CRTPGraphElementFrame< RichLabelElement > _B;
//
//		public:
//		RichLabelElement() : _bckGndcolor(Null) {}
//		RichLabelElement(RichLabelElement& p) : _B(p), _bckGndcolor(p._bckGndcolor) {}
//		virtual ~RichLabelElement() {}
//
//		virtual CLASSANME* Clone() { return new CLASSANME(*this); };
//
//		template<class T>
//		inline void SetLabel(T& v) { _label = ParseQTF(v); }
////		inline const Upp::String& GetLabel() const { return _label.; }
//
//		virtual void PaintElement(Draw& dw, int scale)
//		{
//			if ( !_bckGndcolor.IsNullInstance() )
//				dw.DrawRect( 0, 0, _B::GetFrame().GetWidth(), _B::GetFrame().GetHeight(), _bckGndcolor);
//
//			//Size sz(0,0);
//			switch(_B::GetElementPos()){
//				case LEFT_OF_GRAPH:
//
//					//dw.DrawText( _B::GetElementWidth()*scale/2-sz.cy/2, _B::GetFrame().GetHeight()/2+sz.cx/2 , 900, _label, _font, _color);
//					break;
//				case BOTTOM_OF_GRAPH:
//					//dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, _font, _color);
//					break;
//				case TOP_OF_GRAPH:
//					_label.Paint(dw, 0, 0, 1000);
//					//dw.DrawText( _B::GetFrame().GetWidth()/2-sz.cx/2, _B::GetElementWidth()*scale/2-sz.cy/2 , _label, _font, _color);
//					break;
//				case RIGHT_OF_GRAPH:
//					//dw.DrawText( _B::GetElementWidth()*scale/2+sz.cy/2, _B::GetFrame().GetHeight()/2-sz.cx/2 , 2700, _label, _font, _color);
//					break;
//			}
//		}
//	};



	// ============================
	//    LegendElement   CLASS
	// ============================
	template<class TYPES >
	class LegendElement : public CRTPGraphElementFrame< LegendElement<TYPES> >
	{
		public:
		typedef LegendElement CLASSNAME;
		typedef CRTPGraphElementFrame< LegendElement > _B;
		typedef typename TYPES::TypeVectorSeries TypeVectorSeries;

		String _legend;
		Color  _bckGndcolor;
		RGBA   _bckGndRgba;
		bool   _isRgba;
		Font   _font;
		int    _xSeparation; // separation between two legends
		int    _legendStyleLength;
		int    _legendWeight;
		TypeVectorSeries* v_series;

		public:
		LegendElement()
		: _bckGndcolor(Null)
		, _isRgba(false)
		, _font(StdFont())
		, _xSeparation(20)
		, _legendStyleLength(23)
		, v_series(0)
		{}
		
		LegendElement(LegendElement& p)
		: _B(p)
		, _bckGndcolor(p._bckGndcolor)
		, _bckGndRgba(p._bckGndRgba)
		, _isRgba(p._isRgba)
		, _font(p._font)
		, _xSeparation(p._xSeparation)
		, _legendStyleLength(p._legendStyleLength)
		, v_series(p.v_series)
		{ Update(); }

		virtual ~LegendElement() {}

		virtual CLASSNAME* Clone() { return new CLASSNAME(*this); };

		template<class T>
		inline CLASSNAME& SetLegend(T& v) { _legend = v; return *this; }

		inline CLASSNAME&  SetBackGndColor(Color v) { _bckGndcolor = v; _isRgba=false; return *this; }
		inline CLASSNAME&  SetBackGndColor(RGBA  v) { _bckGndRgba  = v; _isRgba=true;  return *this; }

		virtual void PaintElement(Draw& dw, int scale){
			if ( !_bckGndcolor.IsNullInstance() ) {
				dw.DrawRect( 0, 0, _B::GetFrame().GetWidth(), _B::GetFrame().GetHeight(), _bckGndcolor);
			}
			else if (_isRgba){
				Image img = CreateImage(_B::GetFrame().GetSize(), _bckGndRgba);
				dw.DrawImage( 0,0, img );
			}
			DrawLegend(dw, scale);
		}

		virtual void PaintOverGraph(Draw& dw, int scale){
			if ( !_bckGndcolor.IsNullInstance() )
				dw.DrawRect( 0, 0, _B::GetFrame().GetWidth(), _B::GetFrame().GetHeight(), _bckGndcolor);
			else if (_isRgba){
				Image img = CreateImage(_B::GetFrame().GetSize(), _bckGndRgba);
				dw.DrawImage( 0,0, img );
			}
			DrawLegend(dw, scale);
		}

		virtual void Update() {
			if (v_series==0) {
				v_series = ValueTo<TypeVectorSeries*>(_B::_parent->GetSeries());
			}

			_legendWeight = 0;
			for (int c=0; c<(*v_series).GetCount(); ++c) {
				int textLength = GetTextSize((*v_series)[c].legend, _font).cx;
				if(_legendWeight < textLength) _legendWeight = textLength;
			}
			_legendWeight += _legendStyleLength + _xSeparation;
		}

		void DrawLegend(Draw& w, const int& scale) const
		{
			if (v_series==0) {
				String text = "This is the legend !!";
				w.DrawText( 0,0 , text, _font, Black());
				return;
			}

			int nmr = fround(_B::_frame.GetSize().cx/(_legendWeight*scale));	//max number of labels per row
			if (nmr <= 0) nmr = 1;
			int nLab = (*v_series).GetCount();	//number of labels
			int idx=0;
			int ix=0;
			int iy=0;
			Font scaledFont( _font );
			int txtHeight = scaledFont.Height(scale*_font.GetHeight()).GetHeight();
			while (idx<nLab) {
				while ((idx<nLab) && ((*v_series)[idx].show == false )) { ++idx; }
				
				if (idx<nLab) {
					int x = scale*ix*_legendWeight + txtHeight/2;
					int y = iy*txtHeight + txtHeight/2;
	
					Vector <Point> vp;
					vp << Point(x,y+txtHeight) << Point(x+scale*_legendStyleLength, y);
					if ((*v_series)[idx].opacity > 0 && (*v_series)[idx].seriesPlot)
						DrawPolylineOpa(w, vp, scale, 1, scale*(*v_series)[idx].thickness, (*v_series)[idx].color, (*v_series)[idx].dash);
	
					Point p(x+scale*(_legendStyleLength/2),y+txtHeight/2);
					if ((*v_series)[idx].markWidth >= 1 && (*v_series)[idx].markPlot)
						(*v_series)[idx].markPlot->Paint(w, scale, p, (*v_series)[idx].markWidth, (*v_series)[idx].markColor);
	
					DrawText(w, x+scale*(_legendStyleLength+2), y, 0, (*v_series)[idx].legend, scaledFont,
					         (  ((*v_series)[idx].seriesPlot.IsEmpty()) ? (*v_series)[idx].markColor : (*v_series)[idx].color ) );
					++idx;
				}
				++ix;
				if (ix>=nmr) { ix=0; ++iy; }
			}
		}
	};
}

#endif /* GRAPHELEMENT_H_ */
