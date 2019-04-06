#include "ScatterDraw.h"

int ScatterDraw::NumSeriesLegend() const {
	int num = 0;
	for (int i = 0; i < series.GetCount(); ++i) {
		if (series[i].showLegend)
			num++;
	}
	return num;
}

void ScatterDraw::DrawLegend(Draw& w) const {
	if (series.IsEmpty())
		return;
	int nlab = NumSeriesLegend();		
	if (nlab == 0)
		return;
	
	Upp::Font scaledFont = legendFont;
	double textScale = min(plotScaleX, plotScaleY);
	int rowHeight = int(textScale*scaledFont.GetHeight());
	int rowAscent = int(textScale*scaledFont.GetAscent());
	scaledFont.Height(rowHeight);
	int xWidth = scaledFont.GetWidth('X');
	int lineLen = 4*xWidth;
	
	Vector<String> legends;
	int legendWidth = 0;
	for (int i = 0; i < series.GetCount(); ++i) {
		if (series[i].showLegend) {
			String legend = series[i].legend;
			if (legend.Find('[') < 0 && !series[i].unitsY.IsEmpty())
				legend += " [" + series[i].unitsY + "]";
			legends.Add(legend);
			legendWidth = max<int>(legendWidth, GetTextSize(legend, scaledFont).cx);
		}
	}
	legendWidth += lineLen + 4*xWidth;
	
	int rowIncSign;
	int plotW, plotH;
	int nlr;					
	int topClip;
	int plotLeft, plotTop, rectWidth, rectHeight;	
	int loclegendRowSpacing;
	if (legendAnchor == TOP) {
		plotLeft = plotTop = 0;
		plotW = size.cx - int((hPlotLeft + hPlotRight)*plotScaleX);
		plotH = int(plotScaleY*(vPlotTop - 1) + titleHeight);		
		rowIncSign = -1;
		rectWidth = plotW;
		rectHeight = plotH;
		topClip = 0;
		nlr = fround(rectWidth/legendWidth);	
		loclegendRowSpacing = 0;
	} else {
		plotW = size.cx - int(hPlotLeft*plotScaleX);
		plotH = size.cy - int((vPlotTop + vPlotBottom)*plotScaleY - titleHeight);
		rowIncSign = 1;
		if (IsNull(legendPos))
			return;
		
		plotLeft = int(plotScaleX*hPlotLeft);
		plotTop = int(plotScaleY*vPlotTop + titleHeight);
		rectWidth = legendWidth*legendNumCols;
		rectHeight = 0;
		topClip = int(plotScaleY*vPlotTop + titleHeight);
		nlr = legendNumCols;	
		loclegendRowSpacing = int(legendRowSpacing*textScale);
	}
	if (nlr <= 0) 
		return;
	
	int nrows = fceil(double(nlab)/nlr);	

	if (legendAnchor != TOP) 
		rectHeight = int(rowHeight*(nrows + 0.2)) + loclegendRowSpacing*nrows;
	
	double left = plotLeft + legendPos.x*textScale;
	double right = plotW + (hPlotLeft - hPlotRight)*plotScaleX - legendPos.x*textScale - rectWidth;
	double top = plotTop + legendPos.y*textScale;
	double bottom = plotH - legendPos.y*textScale - rectHeight;
	Rectf rect;
	switch(legendAnchor) {
	case TOP:			rect.Set(plotScaleX*hPlotLeft, 0, rectWidth, rectHeight);		break;
	case LEFT_TOP: 		rect.Set(left, top, left + rectWidth, top + rectHeight);		break;
	case RIGHT_TOP:		rect.Set(right, top, right + rectWidth, top + rectHeight);		break;
	case LEFT_BOTTOM: 	rect.Set(left, bottom, left + rectWidth, bottom + rectHeight);	break; 
	case RIGHT_BOTTOM:	rect.Set(right, bottom, right + rectWidth, bottom + rectHeight);break; 
	default:			rect.Set(0, 0, 0, 0);
	}
	
	w.Clip(int(plotScaleX*hPlotLeft), topClip, plotW, plotH);
	
	if (legendAnchor != TOP) {
		if (!IsNull(legendFillColor))
			FillRectangle(w, rect, legendFillColor);
		if (!IsNull(legendBorderColor)) 
			DrawRectangle(w, rect, textScale, 1, legendBorderColor);
	}
	Upp::Font italic = scaledFont;
	italic.Italic();
	scaledFont.Bold();
	for(int row = 0, start = 0, i = 0, ireal = 0; row <= nrows; row++) {
		for(; ireal < min(start + nlr, nlab); i++) {
			if (series[i].showLegend) {
				double lx = rect.left + (ireal - start)*legendWidth + xWidth;
				double ly = (rowIncSign >= 0 ? rect.top : rect.bottom) +
						 rowIncSign*int(rowHeight*(row + 0.6) + loclegendRowSpacing*(row + 0.5));
				Vector <Pointf> line;
				double dashLen = GetDashLength(series[i].dash)*textScale;
				double realLineLen = lineLen/dashLen > 1 ? dashLen*int(lineLen/dashLen) : lineLen;
				line << Pointf(lx, ly) << Pointf(lx + realLineLen, ly);
				if (series[i].opacity > 0 && series[i].seriesPlot)
					DrawPolylineOpa(w, line, textScale, 1, series[i].thickness, series[i].color, series[i].dash);
				Pointf mark_p(lx + xWidth, ly);
				if (series[i].markWidth >= 1 && series[i].markPlot)
					series[i].markPlot->Paint(w, plotScaleAvg, mark_p, series[i].markWidth, series[i].markColor, 
						series[i].markBorderWidth, series[i].markBorderColor);   
				Upp::Font &font = series[i].primaryY ? scaledFont : italic;
				DrawText(w, lx + lineLen + xWidth, ly - int((2*rowAscent)/3), 0, legends[ireal], font, series[i].color);                   
				ireal++;
			} 
		}
		start = ireal;
	}
	w.End();
}	

void ScatterDraw::DrawRainbowPalette(Draw& w) const {
	double plotLeft = plotScaleX*hPlotLeft;
	double plotTop = plotScaleY*vPlotTop + titleHeight;
	double plotRight = size.cx - hPlotRight*plotScaleX;
	double plotBottom = size.cy - vPlotBottom*plotScaleY;
	
	double rainbowPosx = rainbowPos.x*plotScaleX;
	double rainbowPosy = rainbowPos.y*plotScaleY;
	double rainbowSizecx = rainbowSize.cx*plotScaleX;
	double rainbowSizecy = rainbowSize.cy*plotScaleY;
	
	Rect rect;
	Font fnt = rainbowPaletteFont;
	fnt.Height(int(fnt.GetHeight()*min(plotScaleX, plotScaleY)));
	switch(rainbowAnchor) {
	case LEFT_TOP: 		rect.Set(int(plotLeft  + rainbowPosx), 
								 int(plotTop   + rainbowPosy), 
								 int(plotLeft  + rainbowPosx + rainbowSizecx),
								 int(plotTop   + rainbowPosy + rainbowSizecy));
						break;
	case RIGHT_TOP:		rect.Set(int(plotRight - rainbowPosx - rainbowSizecx), 
								 int(plotTop   + rainbowPosy), 
								 int(plotRight - rainbowPosx),
								 int(plotTop   + rainbowPosy + rainbowSizecy));
						break;
	case LEFT_BOTTOM: 	rect.Set(int(plotLeft  + rainbowPosx), 
								 int(plotBottom- rainbowPosy - rainbowSizecy), 
								 int(plotLeft  + rainbowPosx + rainbowSizecx),
								 int(plotBottom- rainbowPosy));
						break;
	case RIGHT_BOTTOM:	rect.Set(int(plotRight - rainbowPosx - rainbowSizecx), 
								 int(plotBottom- rainbowPosy - rainbowSizecy), 
								 int(plotRight - rainbowPosx),
								 int(plotBottom- rainbowPosy));
						break;
	default:			rect.Set(0, 0, 0, 0);
	}	
	
	if (!surfUnits.IsEmpty()) {
		Size unitsSize = GetTextSize(surfUnits, fnt);	
		switch (surfUnitsPos) {
		case UNITS_TOP:		w.DrawText(int(rect.left + rect.GetWidth()/2. - unitsSize.cx/2.), 
								  	   int(rect.top - unitsSize.cy*1.3), 
								   	   surfUnits, fnt, rainbowPaletteTextColor);
							break;
		case UNITS_BOTTOM:	w.DrawText(int(rect.left + rect.GetWidth()/2. - unitsSize.cx/2.), 
								   	   int(rect.bottom + unitsSize.cy*0.3), 
								   	   surfUnits, fnt, rainbowPaletteTextColor);
							break;
		case UNITS_LEFT:	w.DrawText(int(rect.left - 1.3*unitsSize.cy), 
								   	   int(rect.top + rect.GetHeight()/2. - unitsSize.cx/2.), 900,
								   	   surfUnits, fnt, rainbowPaletteTextColor);
							break;
		case UNITS_RIGHT:	w.DrawText(int(rect.right + 0.3*unitsSize.cy), 
								   	   int(rect.top + rect.GetHeight()/2. - unitsSize.cx/2.), 900,
								   	   surfUnits, fnt, rainbowPaletteTextColor);
							break;
		}
	}
	
	double textX = 0;
	switch (surfLegendPos) {
	case LEGEND_RIGHT:	textX = rect.right + 4*plotScaleX;
						break;
	case LEGEND_LEFT:	textX = rect.left - 4*plotScaleX;
						break;
	}
		
	ImageBuffer out_image(rect.GetWidth(), rect.GetHeight());
	
	double delta = rect.GetHeight();
	for (int iy = 0; iy < delta; ++iy) {
		Color col = GetRainbowColor((delta - iy)/delta, surfRainbow, 
							continuousColor ? 0 : surfNumColor);	
		for (int ix = 0; ix < rect.GetWidth(); ++ix) 
			out_image[iy][ix] = col;
	}
	w.DrawImage(rect.left, rect.top, out_image);	
	DrawRectangle(w, rect, plotScaleAvg, 1, rainbowBorderColor);
	
	double deltaZ = (surfMaxZ - surfMinZ)/double(surfNumColor);
	for (int i = 0; i <= surfNumColor; ++i) {
		double val = surfMinZ + deltaZ*i;
		String txt = VariableFormatZ(val);
		Size textSize = GetTextSize(txt, fnt);
		double deltax = 0;
		if (surfLegendPos == LEGEND_LEFT) 
			deltax = textSize.cx;
		double deltay = textSize.cy/2;
		double ypos = rect.bottom - (i*rect.GetHeight())/double(surfNumColor);
		w.DrawText(int(textX - deltax), int(ypos - deltay), txt, fnt, rainbowPaletteTextColor);
		if (i > 0 && i < surfNumColor)
			DrawLine(w, rect.left, ypos, rect.right, ypos, 1*plotScaleAvg, rainbowBorderColor);
	}
}

