#include <plugin/Eigen/Eigen.h>
using namespace Eigen;

#include "ScatterDraw.h"

NAMESPACE_UPP


#define Membercall(fun)	(this->*fun)

double DataSource::Min(Getdatafun getdata, int64& id) {
	double minVal = -DOUBLE_NULL;
	for (int64 i = 0; i < GetCount(); ++i) {
		double d = Membercall(getdata)(i);
		if (!IsNull(d) && minVal > d) {
			minVal = d;
			id = i;
		}
	}
	if (minVal == -DOUBLE_NULL)
		return Null;
	return minVal;		
}
 
double DataSource::Max(Getdatafun getdata, int64& id) {
	double maxVal = DOUBLE_NULL;
	for (int64 i = 0; i < GetCount(); ++i) {
		double d = Membercall(getdata)(i);
		if (!IsNull(d) && maxVal < d) {
			maxVal = d;
			id = i;
		}
	}
	if (maxVal == DOUBLE_NULL)
		return Null;
	return maxVal;
}

double DataSource::Avg(Getdatafun getdata) {
	double ret = 0;
	int count = 0;
	for (int64 i = 0; i < GetCount(); ++i) {
		double d = Membercall(getdata)(i);
		if (!IsNull(d)) {
			ret += d;
			count++;
		}
	}
	if (count == 0) 
		return Null;
	return ret/count;
}

double DataSource::Variance(Getdatafun getdata, double avg) {
	if (IsNull(avg))
		avg = Avg(getdata);
	if (IsNull(avg))
		return Null;
	double ret = 0;
	int count = 0;
	for (int64 i = 0; i < GetCount(); ++i) {
		double d = Membercall(getdata)(i);
		if (!IsNull(d)) {
			d -= avg;
			ret += d*d;
			count++;
		}
	}
	if (count <= 0)
		return Null;
	return ret/(count - 1);
}

Vector<int64> DataSource::Envelope(Getdatafun getdataY, Getdatafun getdataX, double width, bool (*fun)(double a, double b)) {
	Vector<int64> ret;
	double width_2 = width/2.;
		
	for (int i = 0; i < GetCount(); ++i) {
		double y = Membercall(getdataY)(i);
		double x = Membercall(getdataX)(i);
		if (IsNull(x) || IsNull(y))
			continue;
		int numComparisons = 0;
		for (int j = i-1; j >= 0; --j) {
			double ynext = Membercall(getdataY)(j);
			double xnext = Membercall(getdataX)(j);
			if (IsNull(xnext) || IsNull(ynext))
				continue;
			if ((x - xnext) > width_2)
				break;
			if (!fun(y, ynext)) {
				numComparisons = Null;
				break;
			}
			numComparisons++;
		}
		if (IsNull(numComparisons))
			continue;
		for (int j = i+1; j < GetCount(); ++j) {
			double ynext = Membercall(getdataY)(j);
			double xnext = Membercall(getdataX)(j);
			if (IsNull(xnext) || IsNull(ynext))
				continue;
			if ((xnext - x) > width_2)
				break;
			if (!fun(y, ynext)) {
				numComparisons = Null;
				break;
			}
			numComparisons++;
		}
		if (IsNull(numComparisons))
			continue;
		if (numComparisons > 2)
			ret << i;
	}
	return ret;
}

bool GreaterThan(double a, double b) {return a > b;}
bool LowerThan(double a, double b) {return a < b;}

Vector<int64> DataSource::UpperEnvelope(Getdatafun getdataY, Getdatafun getdataX, double width) {return Envelope(getdataY, getdataX, width, GreaterThan);}
Vector<int64> DataSource::LowerEnvelope(Getdatafun getdataY, Getdatafun getdataX, double width) {return Envelope(getdataY, getdataX, width, LowerThan);}

Vector<Pointf> DataSource::MovingAverage(Getdatafun getdataY, Getdatafun getdataX, double width) {
	Vector<Pointf> ret;
	double width_2 = width/2.;
	
	for (int i = 0; i < GetCount(); ++i) {
		double y = Membercall(getdataY)(i);
		double x = Membercall(getdataX)(i);
		if (IsNull(x) || IsNull(y))
			continue;
		int numAvg = 1;
		double sum = y;
		int j;
		for (j = i-1; j >= 0; --j) {
			double ynext = Membercall(getdataY)(j);
			double xnext = Membercall(getdataX)(j);
			if (IsNull(xnext) || IsNull(ynext))
				continue;
			if ((x - xnext) > width_2)
				break;
			sum += ynext;
			numAvg++;
		}
		if (j < 0)
			continue;
		for (j = i+1; j < GetCount(); ++j) {
			double ynext = Membercall(getdataY)(j);
			double xnext = Membercall(getdataX)(j);
			if (IsNull(xnext) || IsNull(ynext))
				continue;
			if ((xnext - x) > width_2)
				break;
			sum += ynext;
			numAvg++;
		}
		if (j == GetCount())
			continue;
		ret << Pointf(x, sum/numAvg);
	}
	return ret;	
}

double DataSource::StdDev(Getdatafun getdata, double avg) {
	double var = Variance(getdata, avg);
	return IsNull(var) ? Null : sqrt(var);
}

double DataSource::SinEstim_Amplitude(double avg) {
	return sqrt(2.*VarianceY(avg));
}

bool DataSource::SinEstim_FreqPhase(double &frequency, double &phase, double avg) {
	if (GetCount() < 4)
		return false;
	if (IsNull(avg))
		avg = AvgY();
	int64 firstId;
	for (firstId = 0; firstId < GetCount(); ++firstId) 
		if (!IsNull(x(firstId)) && !IsNull(y(firstId)))
			break;
	bool firstIsToPositive = (y(firstId) - avg) < 0;
	bool isPossitive = !firstIsToPositive;
	double T = 0;
	int numT = 0;
	double lastZero = Null;
	double firstZero;
	firstId++;
	for (int64 id = firstId; id < GetCount(); ++id) {
		if (IsNull(x(id)) || IsNull(y(id)))
			continue;
		if (((y(id) - avg) > 0) != isPossitive) {
			isPossitive = !isPossitive;
			double zero = x(id-1) - (y(id-1) - avg)*(x(id) - x(id-1))/(y(id) - y(id-1));
			if (IsNull(lastZero)) 
				firstZero = zero;
			else {
				T += zero - lastZero;
				numT++;
			}
			lastZero = zero;
		}
	}
	T = 2*T/numT;
	frequency = 2*M_PI/T;			
	phase = -frequency*firstZero;
	if (!firstIsToPositive)
		phase += M_PI;
	return true;
}
	
	
double CArray::znFixed(int n, int64 id) {
	if (n == 0)
		return zData[id];
	NEVER();
	return Null;
}


Vector<Pointf> DataSource::FFT(Getdatafun getdata, double tSample) {
	int numData = int(GetCount());
    VectorXd timebuf(numData);
    int num = 0;
    for (int i = 0; i < numData; ++i) {
        double data = Membercall(getdata)(i);
        if (!IsNull(data)) {
			timebuf[i] = Membercall(getdata)(i);
			num++;
        }
    }
    Vector<Pointf> res;	
    if (num < 3)
        return res;
    timebuf.resize(num);
    
    VectorXcd freqbuf;
    try {
	    Eigen::FFT<double> fft;
	    fft.SetFlag(fft.HalfSpectrum);
	    fft.fwd(freqbuf, timebuf);
    } catch(...) {
        return res;
    }
    for (int i = 1; i < freqbuf.size(); ++i) {
        double T = (tSample*numData)/i;
        res << Pointf(T, 2*std::abs(freqbuf[i])/numData);
    }
    return res;
}


bool Spline::Load(Vector<double>& xdata, Vector<double>& ydata)
{
    if(!IsInputSane(xdata, ydata))
        return false;

    int n = xdata.GetCount() - 1;
    
    Vector<double> h;
    for(int i = 0; i < n; ++i)
        h << (xdata[i+1] - xdata[i]);

    Vector<double> alpha;
    for(int i = 0; i < n; ++i)
        alpha << (3.*(ydata[i+1] - ydata[i])/h[i] - 3*(ydata[i]-ydata[i-1])/h[i-1]);

    Vector<double> l, mu, z;
    l.SetCount(n+1);
    mu.SetCount(n+1);
    z.SetCount(n+1);
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for(int i = 1; i < n; ++i) {
        l[i] = 2.*(xdata[i+1] - xdata[i-1]) - h[i-1]*mu[i-1];
        mu[i] = h[i]/l[i];
        z[i] = (alpha[i] - h[i-1]*z[i-1])/l[i];
    }

    l[n] = 1.;
    z[n] = 0;
    
    Vector<double> c;
    c.SetCount(n+1);
    c[n] = 0;

	Vector<double> b, d;
	b.SetCount(n);
	d.SetCount(n);
    for(int j = n-1; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j+1];
        b[j] = (ydata[j+1] - ydata[j])/h[j] - h[j]*(c[j+1] + 2*c[j])/3.;
        d[j] = (c[j+1] - c[j])/3./h[j];
    }

    coeff.SetCount(n);
    for(int i = 0; i < n; ++i) {
        coeff[i].a = ydata[i];
        coeff[i].b = b[i];
        coeff[i].c = c[i];
        coeff[i].d = d[i];
        coeff[i].x = xdata[i];
    }
    return true;
}

double Spline::GetY(double x)
{
    int j;
    for (j = 0; j < coeff.size(); j++) {
        if(coeff[j].x > x) {
            if(j == 0)
                j++;
            break;
        }
    }
    j--;

    double dx = x - coeff[j].x;
    return coeff[j].a + coeff[j].b*dx + coeff[j].c*dx*dx + coeff[j].d*dx*dx*dx;
}

bool Spline::IsInputSane(Vector<double>& xdata, Vector<double>& ydata)
{
    if(xdata.IsEmpty() || ydata.IsEmpty())
        return false;
    
    if(!IsSorted(xdata))
        return false;

    bool first = true;
    double xold;
    for(double x : xdata) {
        if(first) 
            xold = x;
        else {
	        first = false;
	        if( fabs(x - xold) < 1) 
	            return false;
	        xold = x;
        }
    }
    return true;
}

END_UPP_NAMESPACE