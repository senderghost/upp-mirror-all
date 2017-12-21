#ifndef _ScatterCtrl_Properties_h_
#define _ScatterCtrl_Properties_h_


class MeasuresTab : public WithMeasures<StaticRect> {
public:
	typedef MeasuresTab CLASSNAME;
	
	void Init(ScatterCtrl &scatter);
	void Change();

private:
	ScatterCtrl *pscatter;
};

class TextsTab : public WithTexts<StaticRect> {
public:
	typedef TextsTab CLASSNAME;
	
	void Init(ScatterCtrl &scatter);
	void DoShowText();
	
private:
	ScatterCtrl *pscatter;
	
	void Change();
};

class LegendTab : public WithLegend<StaticRect> {
public:
	typedef LegendTab CLASSNAME;
	
	void Init(ScatterCtrl &scatter);

private:
	ScatterCtrl *pscatter;
	
	void Change();
	void ChangeAnchor(Option *op);
};

class SeriesTab : public WithSeries<StaticRect> {
public:
	typedef SeriesTab CLASSNAME;
	
	SeriesTab() : dashCount(DashStyle::GetCount()) {}
	~SeriesTab() {
		DashStyle::UnregisterFrom(dashCount);
	}
	void Init(ScatterCtrl& scatter);
	
private:
	ScatterCtrl *pscatter;	
	int dashCount;
	
	void Change();
	void ChangeMark();
	void UpdateFields();
};

class DataDlg : public WithData<TopWindow> {
public:
	typedef DataDlg CLASSNAME;
	
	void OnClose();
	
	DataDlg(ScatterCtrl& scatter);
	void OnTab(); 
	void OnArrayBar(Bar &menu);
	void ArrayCopy();
	void ArraySelect();
	void ArraySaveToFile(String fileName);
	
	class DataSourceX : public Convert {
	public:
		Value Format(const Value& q) const;
		ScatterDraw *pscatter;
		int index;
	} dataSourceX;
	
	class DataSourceY : public Convert {
	public:
		Value Format(const Value& q) const;
		ScatterDraw *pscatter;
		int index;
	};
	Array<DataSourceY> dataSourceYArr;
	
private:
	ScatterCtrl *pscatter;	
	
	Array <WithDataSeries <StaticRect> > series;
};

class PropertiesDlg : public WithProperties<TopWindow> {
public:
	typedef PropertiesDlg CLASSNAME;
	
	PropertiesDlg(ScatterCtrl& scatter, int tab = 0);
	void OnTab(); 
	void OnClose();
		
private:
	ScatterCtrl& scatter;
	MeasuresTab measures;
	TextsTab texts;
	LegendTab legend;
	SeriesTab series;
};


class ProcessingTab : public WithProcessingTab<StaticRect> {
public:
	typedef ProcessingTab CLASSNAME;

	ProcessingTab();
	void Init(ScatterCtrl& scatter) {pscatter = &scatter;}
	void UpdateField(const String name, int id);
	void OnFFT();
	void OnOp();
	void OnAutoSensSector();
	void OnShowEquation();
	void UpdateEquations();
	void OnFromTo();
	void OnOperation();
	void OnSet();
	void OnUpdateSensitivity();
	void OnFit();
		
private:
	ScatterCtrl* pscatter;
	int id;
	
	WithProcessingTabFit<StaticRect> tabFit;	
	WithProcessingTabFrequency<StaticRect> tabFreq;
	WithProcessingTabOp<StaticRect> tabOp;
	WithProcessingTabBestFit<StaticRect> tabBestFit;
	
	void ArrayCopy();
	void ArraySelect();
	void OnArrayBar(Bar &menu);
	Array<ExplicitEquation> equationTypes;
	UserEquation *userEquation;
	//GridCtrlSource ds;
	
	bool avgFirst, linearFirst, cuadraticFirst, cubicFirst, sinusFirst, sinusTendFirst, splineFirst;
	double r2Linear, r2Cuadratic, r2Cubic, r2Sinus, r2SinusTend;
	bool tabFreqFirst, tabOpFirst, tabBestFitFirst;
	
	Vector<Pointf> fft;
	AvgEquation average;
	LinearEquation linear;
	PolynomialEquation2 cuadratic;
	PolynomialEquation3 cubic;
	SinEquation sinus, sinusTend;
	SplineEquation spline;
	Vector<Pointf> upperEnvelope, lowerEnvelope;
	Vector<Pointf> movAvg, secAvg;
	DataXRange dataXRange;
	bool exclamationOpened;
	double newWidthMax, newWidthMin, newWidthMovAvg;
};

class ProcessingDlg : public WithProcessing<TopWindow> {
public:
	typedef ProcessingDlg CLASSNAME;

	ProcessingDlg(ScatterCtrl& scatter);
	void OnClose();
	
private:
	ScatterCtrl& scatter;	
	Array<ProcessingTab> tabs;
	
	void UpdateFields();
};

class TextDlg : public WithText<TopWindow> {
public:
	typedef TextDlg CLASSNAME;
	
	TextDlg(ScatterCtrl& scatter);
	void Change();
	void OnClose();
	
private:
	ScatterCtrl& scatter;	
};
	

#endif
