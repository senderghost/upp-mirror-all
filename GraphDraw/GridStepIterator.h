#ifndef _GraphCtrl_GridStepManager_h_
#define _GraphCtrl_GridStepManager_h_

#include <limits>

namespace GraphDraw_ns
{

	// ============================
	//    GridStepManager   CLASS
	// ============================

	template<class COORDCONVERTER>
	class GridStepIterator {
		private:
			int _nbSteps;     // current step range (according to grid step)
			int _currentStep; // current step number
			COORDCONVERTER& _coordConverter;
			TypeGraphCoord* const _graphStepValues; // points to steps array (pre-calculated by GridStepManager)

		public:
			typedef GridStepIterator<COORDCONVERTER> CLASSNAME;

			GridStepIterator( COORDCONVERTER& conv, int nbSteps, TypeGraphCoord* stepValues, int currentStep)
			: _nbSteps(nbSteps)
			, _currentStep(currentStep)
			, _coordConverter(conv)
			, _graphStepValues(stepValues)
			{}

			GridStepIterator(const CLASSNAME& p)
			: _nbSteps(p._nbSteps)
			, _currentStep(p._currentStep)
			, _coordConverter(p._coordConverter)
			, _graphStepValues(p._graphStepValues)
			{}

			inline bool operator==( const CLASSNAME& v) { return( _currentStep==v._currentStep );  }
			inline bool operator!=( const CLASSNAME& v) { return( _currentStep!=v._currentStep );  }
			inline TypeScreenCoord  operator*() { return getStepValue(); }

			inline CLASSNAME& toEnd()   { _currentStep = _nbSteps; return *this; }
			inline CLASSNAME& toBegin() { _currentStep = 0; return *this; }

			// ++X
			inline CLASSNAME&  operator++()
			{
				++_currentStep;
				return *this;
			}

			// X++
			CLASSNAME  operator++(int)
			{
				CLASSNAME tmp(*this);
				++_currentStep;
				return tmp;
			}

			inline TypeGraphCoord getValue() // methode that calculates the grid step position value
			{
				return _graphStepValues[_currentStep];
			}

			inline TypeScreenCoord getStepValue() // methode that calculates the grid step position value
			{
				return _coordConverter.toScreen( getValue() );
			}
	};


	template<class COORDCONVERTER, int NB_MAX_STEPS=100>
	class GridStepManager {
		public:
			typedef COORDCONVERTER TypeCoordConverter;
			typedef GridStepManager<COORDCONVERTER, NB_MAX_STEPS>  CLASSNAME;
			typedef GridStepIterator<COORDCONVERTER> Iterator;
			typedef Callback2<CLASSNAME&, CoordinateConverter&> TypeGridStepCalcCallBack;

		protected:
			unsigned int _nbMaxSteps;  // steps range is : [0, _nbMaxSteps]
			unsigned int _nbSteps;     // current step range (according to grid step)
			unsigned int _currentStep; // current step number
			TypeCoordConverter& _coordConverter;
			
			TypeGraphCoord _stepValues[NB_MAX_STEPS];


			TypeGridStepCalcCallBack updateCbk;
		public:
			GridStepManager(TypeCoordConverter& coordConv)
			: _nbMaxSteps( 15 )
			, _currentStep( 0 )
			, _coordConverter( coordConv )
			{
				setStdGridSteps();
				Update();
			}

			GridStepManager(int nbSteps, int currStep, TypeCoordConverter& coordConv)
			: _nbMaxSteps( nbSteps )
			, _currentStep( currStep )
			, _coordConverter( coordConv )
			{
				setStdGridSteps();
				Update();
			}
			
			void setGridStepCalcBack(TypeGridStepCalcCallBack cbk) { updateCbk = cbk; }
			void setStdGridSteps()                                 { updateCbk =  THISBACK(stdGridStepCalcCbk); }
			void setTimeGridSteps()                                { updateCbk =  THISBACK(timeGridStepCalcCbk); }
			void setDateGridSteps()                                { updateCbk =  THISBACK(dateGridStepCalcCbk); }

			virtual ~GridStepManager() {}

			void stdGridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv)
			{
				TypeGraphCoord gridStartValue;
				TypeGraphCoord gridStepValue;
				gridStepValue = GetNormalizedStep( coordConv.getSignedGraphRange() );
				gridStartValue = GetGridStartValue( gridStepValue, coordConv.getGraphMin() );
				_nbSteps = (unsigned int)tabs((coordConv.getGraphMax() - gridStartValue) / gridStepValue);
				
				if (_nbSteps > _nbMaxSteps) {
					_nbSteps = _nbMaxSteps;
				}

				// fill step values ==> used by gridStepIterator
				for (unsigned int c=0; c<_nbSteps+1; ++c) {
					_stepValues[c] = gridStartValue + gridStepValue*c;
				}
			}

			void dateGridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv)
			{
				Date dateRange;      dateRange.Set(coordConv.getSignedGraphRange());
				Date graphStartDate; graphStartDate.Set(coordConv.getGraphMin());
				Date graphEndDate;   graphEndDate.Set(coordConv.getGraphMin());
				// ===================
				//        YEARS
				// ===================
				if (dateRange.year >= 7) {
					int yearRange = dateRange.year;
					int normalizedYearStep = GetNormalizedStep( yearRange );
					if (normalizedYearStep==0) normalizedYearStep = 1;

					const double daysPerYear = 365.0;
					Date dateIter(0,1,1);

					if ( Date(dateIter.year,1,1).Get() < graphStartDate.Get()) {
						dateIter.year = GetGridStartValue( normalizedYearStep, graphStartDate.year+1 );
					}
					else {
						dateIter.year = GetGridStartValue( normalizedYearStep, graphStartDate.year );
					}

					_nbSteps = (unsigned int)tabs((graphEndDate.year - dateIter.year) / normalizedYearStep);
					if (_nbSteps > _nbMaxSteps) {
						_nbSteps = _nbMaxSteps;
					}
					else if (_nbSteps==0) _nbSteps = 1;

					LOG("YEAR  range=" << yearRange << "months    normalizedStep = "<< normalizedYearStep << " years     _nbSteps=" << _nbSteps<< "       graphStartDate = "<< dateIter);
					for (unsigned int c=0; c<= _nbSteps; ++c) {
						_stepValues[c] = dateIter.Get();
						LOG("     YEAR  STEP : "<< dateIter);
						dateIter = AddYears(dateIter, normalizedYearStep);
					}
				}
				// ===================
				//        MONTHS
				// ===================
				else if ((dateRange.month >= 7) || (dateRange.year > 0 )) {
					int monthRange = dateRange.year*12 + dateRange.month;
					Vector<double> monthSteps;
					monthSteps << 1 << 2 << 3 << 4 << 6 << 12 << 24 << 48;
					int normalizedMonthStep = GetNormalizedStep( monthRange, monthSteps );
					if (normalizedMonthStep==0) normalizedMonthStep = 1;

					const double daysPerMonths = 365.0/12;
					Date dateIter;
					dateIter.Set( GetGridStartValue( normalizedMonthStep*daysPerMonths, graphStartDate.Get() ));

					if (dateIter.day > 1) {
						dateIter = LastDayOfMonth(dateIter)+1; // goto 1rst day of next month
					}

					_nbSteps = (unsigned int)tabs(((graphEndDate.year - dateIter.year)*12 + graphEndDate.month - dateIter.month ) / normalizedMonthStep);
					if (_nbSteps > _nbMaxSteps) {
						_nbSteps = _nbMaxSteps;
					}
					else if (_nbSteps==0) _nbSteps = 1;
					LOG("MONTH  range=" << monthRange << "months    normalizedStep = "<< normalizedMonthStep << "months     _nbSteps=" << _nbSteps<< "       graphStartDate = "<< dateIter);
					for (unsigned int c=0; c<= _nbSteps; ++c) {
						_stepValues[c] = dateIter.Get();
						LOG("     MONTH  STEP : "<< dateIter);
						dateIter = AddMonths(dateIter, normalizedMonthStep);
					}
				}
				// ======
				//  DAYS
				// ======
				else {
					TypeGraphCoord gridStartValue;
					int64 normalizedStep;
					Vector<double> daySteps;
					daySteps << 1 << 2  << 3 << 4 << 5 << 7 << 14 << 28 << 56;
					normalizedStep = GetNormalizedStep( dateRange.Get(), daySteps );
					if (normalizedStep == 0) normalizedStep = 1;
					gridStartValue = GetGridStartValue( normalizedStep, _coordConverter.getGraphMin() );
					_nbSteps = (unsigned int)tabs((graphEndDate.Get() - gridStartValue) / normalizedStep);

					if (_nbSteps > _nbMaxSteps) {
						_nbSteps = _nbMaxSteps;
					}
					else if (_nbSteps==0) _nbSteps = 1;

					LOG("D/H/M/S  ==>  _nbSteps=" << _nbSteps << "      gridStepValue=" << normalizedStep);
					for (unsigned int c=0; c<_nbSteps+1; ++c)
					{
						_stepValues[c] = gridStartValue + normalizedStep * c;
					}
				}
			}

			void timeGridStepCalcCbk(CLASSNAME& gridStepManager, CoordinateConverter& coordConv)
			{
				enum {
					DAY_sec     = 24*60*60,
					HOUR_sec    = 60*60,
					MINUTES_sec = 60,
				};
				Time timeOrigin;     timeOrigin.Set(0);
				Time graphStartTime; graphStartTime.Set(coordConv.getGraphMin());
				Time graphEndTime;   graphEndTime.Set(coordConv.getGraphMax());
				Time timeRange;      timeRange.Set(coordConv.getSignedGraphRange());

				LOG("\n--timeGridStepCalcCbk--   range=" << timeRange << "       GraphMin = "<< graphStartTime << "     GraphMax = " << graphEndTime);

				// ===================
				//        YEARS
				// ===================
				if (timeRange.year >= 7) {
					Date graphStartDate( graphStartTime.year, graphStartTime.month, graphStartTime.day);
					Date graphEndDate( graphEndTime.year, graphEndTime.month, graphEndTime.day);
					int yearRange = timeRange.year;
					int normalizedYearStep = GetNormalizedStep( yearRange );
					if (normalizedYearStep==0) normalizedYearStep = 1;

					const double daysPerYear = 365.0;
					Date dateIter(0,1,1);

					if ( Date(dateIter.year,1,1).Get() < graphStartDate.Get()) {
						dateIter.year = GetGridStartValue( normalizedYearStep, graphStartDate.year+1 );
					}
					else {
						dateIter.year = GetGridStartValue( normalizedYearStep, graphStartDate.year );
					}

					_nbSteps = (unsigned int)tabs((graphEndDate.year - dateIter.year) / normalizedYearStep);
					if (_nbSteps > _nbMaxSteps) {
						_nbSteps = _nbMaxSteps;
					}
					else if (_nbSteps==0) _nbSteps = 1;

					LOG("YEAR  range=" << yearRange << "months    normalizedStep = "<< normalizedYearStep << " years     _nbSteps=" << _nbSteps<< "       graphStartDate = "<< dateIter);
					for (unsigned int c=0; c<= _nbSteps; ++c) {
						Time tmp = ToTime(dateIter);
						_stepValues[c] = tmp.Get();
						LOG("     YEAR  STEP : "<< dateIter << "       tmp=" << tmp);
						dateIter = ToTime(AddYears(dateIter, normalizedYearStep));
					}
				}
				// ===================
				//        MONTHS
				// ===================
				else if ((timeRange.month >= 7) || (timeRange.year > 0 )) {
					Date graphStartDate( graphStartTime.year, graphStartTime.month, graphStartTime.day);
					Date graphEndDate( graphEndTime.year, graphEndTime.month, graphEndTime.day);
					int monthRange = timeRange.year*12 + timeRange.month;
					Vector<double> monthSteps;
					monthSteps << 1 << 2 << 3 << 4 << 6 << 12 << 24 << 48;
					int normalizedMonthStep = GetNormalizedStep( monthRange, monthSteps );
					if (normalizedMonthStep==0) normalizedMonthStep = 1;

					const double daysPerMonths = 365.0/12;
					Date dateIter;
					dateIter.Set( GetGridStartValue( normalizedMonthStep*daysPerMonths, graphStartDate.Get() ));

					if (dateIter.day > 1) {
						dateIter = LastDayOfMonth(dateIter)+1; // goto 1rst day of next month
					}

					_nbSteps = (unsigned int)tabs(((graphEndDate.year - dateIter.year)*12 + graphEndDate.month - dateIter.month ) / normalizedMonthStep);
					if (_nbSteps > _nbMaxSteps) {
						_nbSteps = _nbMaxSteps;
					}
					else if (_nbSteps==0) _nbSteps = 1;
					LOG("MONTH  range=" << monthRange << "months    normalizedStep = "<< normalizedMonthStep << "months     _nbSteps=" << _nbSteps<< "       graphStartDate = "<< dateIter);
					for (unsigned int c=0; c<= _nbSteps; ++c) {
						Time tmp = ToTime(dateIter);
						_stepValues[c] = tmp.Get();
						LOG("     MONTH  STEP : "<< dateIter << "       tmp=" << tmp);
						dateIter = ToTime(AddMonths(dateIter, normalizedMonthStep));
					}
				}
				// ================================
				//  DAY / HOUR / MINUTES / SECONDS
				// ================================
				else {
					TypeGraphCoord gridStartValue;
					int64 normalizedStep;
					Vector<double> secondsSteps;
					secondsSteps << 1 << 2 << 5 << 10 << 15 << 20 << 30;
					secondsSteps << MINUTES_sec << MINUTES_sec*2 << MINUTES_sec*3 << MINUTES_sec*5 << MINUTES_sec*10 << MINUTES_sec*15 << MINUTES_sec*20 << MINUTES_sec*30;
					secondsSteps << HOUR_sec << HOUR_sec*2 << HOUR_sec*3 << HOUR_sec*4 << HOUR_sec*6 << HOUR_sec*8 << HOUR_sec*12;
					secondsSteps << DAY_sec << DAY_sec*2  << DAY_sec*3 << DAY_sec*4 << DAY_sec*5 << DAY_sec*7 << DAY_sec*14 << DAY_sec*28 << DAY_sec*56;
					normalizedStep = GetNormalizedStep( (timeRange - timeOrigin), secondsSteps );
					if (normalizedStep == 0) normalizedStep = 1;
					gridStartValue = GetGridStartValue( normalizedStep, _coordConverter.getGraphMin() );
					_nbSteps = (unsigned int)tabs((graphEndTime.Get() - gridStartValue) / normalizedStep);

					if (_nbSteps > _nbMaxSteps) {
						_nbSteps = _nbMaxSteps;
					}
					else if (_nbSteps==0) _nbSteps = 1;

					LOG("D/H/M/S  ==>  _nbSteps=" << _nbSteps << "      gridStepValue=" << normalizedStep);
					for (unsigned int c=0; c<_nbSteps+1; ++c)
					{
						_stepValues[c] = gridStartValue + normalizedStep * c;
					}
				}
			}



			virtual void Update()
			{
				updateCbk(*this, _coordConverter);
			}

			void SetNbSteps(int nbSteps)
			{
				_nbMaxSteps = nbSteps;
				Update();
			}

			Iterator End() {
				return GridStepIterator<COORDCONVERTER>( _coordConverter, _nbSteps+1, _stepValues, _nbSteps+1);
			}

			Iterator Begin() {
				return GridStepIterator<COORDCONVERTER>( _coordConverter, _nbSteps+1, _stepValues, 0);
			}

			TypeGraphCoord  GetNormalizedStep(TypeGraphCoord  range)
			{
				int e = 0;
				double s = Upp::normalize(range/(_nbMaxSteps+1), e);
				double sign = 1;
				if (s<0) sign = -1;

				s = sign*s;
				if     ( (s>2) && (s<=5)  ) { s = 5; }
				else if( (s>1) && (s<=2)  ) { s = 2; }
				else if( (s>5) && (s<=10) ) { s = 1; e++; }
				else   { s = 1; }
				return sign * s * Upp::ipow10(e);
			}

			template <class T>
			T  GetNormalizedStep(TypeGraphCoord  range, const Vector<T> stepValues)
			{
				double s = range/(_nbMaxSteps+1);
				T sign = 1;
				if (s<0) sign = -1;

				s = sign*s;
				int c=0;
				while (c < stepValues.GetCount()-1) {
					if ( (s>stepValues[c]) && (s<=stepValues[c+1])  ) {
						s = stepValues[c+1];
						return sign*s;
					}
					++c;
				}
				if (c==stepValues.GetCount()) s = stepValues[0];
				return sign*s;
			}


			TypeGraphCoord  GetGridStartValue(TypeGraphCoord  pstepValue, TypeGraphCoord pgraphMin)
			{
				TypeGraphCoord res;
				long double stepValue = pstepValue;
				long double graphMin = pgraphMin;
				if (graphMin>=0) {
					res = ((int)(graphMin/stepValue + 1 - std::numeric_limits<TypeGraphCoord>::epsilon()) ) * stepValue;
				} else {
					res = (((int)(graphMin/stepValue) ) * stepValue);
				}
				if (res < pgraphMin) res = pgraphMin;
				return res;
			}


		private:
			// explicitly forbidden to use
			CLASSNAME& operator=( const CLASSNAME& v) { return *this; }
			GridStepManager() {}
	};



};
#endif
