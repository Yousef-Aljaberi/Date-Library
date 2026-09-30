#pragma warning(disable : 4996)
#pragma once

#include<string>
#include<iostream>
#include "clsString.h"
#include<vector>
#include<ctime>


using namespace std;
class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;
public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	clsDate(string Date)
	{
		vector<string> vDate = clsString::SplitString(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year)
	{

		_Day = Day;
		_Month = Month;
		_Year = Year;

	}
	clsDate(short DateOrderInYear, short Year)
	{
		clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
		_Day = Date1.Day;
		_Month = Date1.Month;
		_Year = Date1.Year;
	}
	void SetDay(int Day)
	{
		_Day = Day;
	}
	int GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) int Day;


	void SetMonth(int Month)
	{
		_Month = Month;
	}

	int GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) int Month;

	void SetYear(int Year)
	{
		_Year = Year;
	}
	int GetYear()
	{
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) int Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	//-----------------------------------------------------

	static bool IsLeapYear(int Year)
	{
		return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool IsLeapYear()
	{
		return IsLeapYear(this->_Year);
	}
	//-----------------------------------------------------
	static int NumberOfDaysInYear(int Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	int	NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(this->_Year);
	}
	static int NumberOfHoursInYear(int Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}
	int NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(this->_Year);
	}
	static int NumberOfMinutsInYear(int Year)
	{
		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMinutsInYear()
	{
		return  NumberOfMinutsInYear(this->_Year);
	}
	static int NumberOfSecendsInYear(int Year)
	{
		return NumberOfMinutsInYear(Year) * 60;
	}
	int NumberOfSecendsInYear()
	{
		return NumberOfSecendsInYear(this->_Year);
	}
	//-----------------------------------------------------

	static short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month>12)
			return 0;

		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}
	static short NumberOfHoursInMonth(short Year, short Month)
	{
		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_Year, _Month);
	}
	static int NumberOfMinutsInMonth(short Year, short Month)
	{
		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	int NumberOfMinutsInMonth()
	{
		return NumberOfMinutsInMonth(_Year, _Month);
	}
	static int NumberOfSecendsInMonth(int Year, short Month)
	{
		return NumberOfMinutsInMonth(Year, Month) * 60;
	}
	int NumberOfSecendsInMonth()
	{
		return NumberOfSecendsInMonth(_Year, _Month);
	}

	//-----------------------------------------------------
	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		int a = (14 - Month) / 12;
		int y = Year - a;
		int m = Month + (12 * a) - 2;
		//Gregorian:
		//0:Sunday, 1:Monday ....
		return 	(Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	}
	static short DayOfWeekOrder(clsDate Date)
	{
		int a = (14 - Date.Month) / 12;
		int y = Date.Year - a;
		int m = Date.Month + (12 * a) - 2;
		//Gregorian:
		//0:Sunday, 1:Monday ....
		return 	(Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

	}
	static  string DayShortName(short DayOrderOfWeek)
	{
		string arrDaysName[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDaysName[DayOrderOfWeek];
	}
	static  string DayShortName(short Year, short Month, short Day)
	{
		return  DayShortName(DayOfWeekOrder(Year, Month, Day));
	}
	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder(_Year, _Month, _Day));
	}

	//-----------------------------------------------------

	static  string MonthShortName(short Month)
	{
		if (Month > 12 || Month < 1)
			return "";
		string arrShortMonthName[12] = { "Jan","Feb","Mar","Ipr","May","Jun","jul","Aug","Sep","Oct","Nov","Dec" };
		return arrShortMonthName[Month - 1];
	}
	string MonthShortName()
	{
		return MonthShortName(this->_Month);
	}

	//-----------------------------------------------------

	static void PrintMonthCalendar(int Year, short Month)
	{
		short NumberOfDayInMonth = NumberOfDaysInMonth(Year, Month);

		//index of the day 0 to 6
		short IndexOfDay = DayOfWeekOrder(Year, Month, 1);


		//print currn month name
		printf("---------------------------%s---------------------------\n\n", MonthShortName(Month).c_str());

		//print the columns
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		//print appropriate space
		for (i = 0; i < IndexOfDay; i++)
			printf("     ");


		for (int j = 1; j <= NumberOfDayInMonth; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}

		}
		cout << "\n-------------------------------------------------------\n";
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(this->_Year, this->_Month);
	}

	//-----------------------------------------------------

	static void PrintYearCalender(short Year)
	{
		cout << "\n-------------------------------------------------------\n";
		cout << "\t\t\t Calender - " << Year;
		cout << "\n-------------------------------------------------------\n";

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(Year, i);
		}
	}
	void PrintYearCalender()
	{
		PrintYearCalender(this->_Year);
	}

	//-----------------------------------------------------

	static short DaysFromTheBeginingOfTheYear(short Year, short Month, short Day)
	{
		short NumberOfDays = 0;
		for (int i = 1; i <= Month - 1; i++)
		{
			NumberOfDays += NumberOfDaysInMonth(Year, i);
		}
		NumberOfDays += Day;

		return NumberOfDays;
	}
	short DaysFromTheBeginingOfTheYear()
	{
		return DaysFromTheBeginingOfTheYear(this->_Year, this->_Month, this->_Day);
	}

	//-----------------------------------------------------

	static clsDate AddDaysToDate(clsDate& Date, int DaysToAdd)
	{
		short RemainingDays = DaysToAdd + DaysFromTheBeginingOfTheYear(Date.Year, Date.Month, Date.Day);
		short MonthDays = 0;
		Date.Month = 1;
		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Year, Date.Month);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
				if (Date.Month > 12)
				{
					Date.Year++;
					Date.Month = 1;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	void AddDaysToDate(int DaysToAdd)
	{
		AddDaysToDate(*this, DaysToAdd);
	}

	//-----------------------------------------------------

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? (Date1.Day < Date2.Day) : false)) : false);

	}
	bool IsDateBeforeDate2(clsDate Date)
	{
		return IsDate1BeforeDate2(*this, Date);
	}

	//-----------------------------------------------------

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return ((Date1.Year == Date2.Year) ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day) : false) : false);
	}
	bool IsDateEqualDate2(clsDate Date)
	{
		return IsDate1EqualDate2(*this, Date);
	}

	//-----------------------------------------------------

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	//-----------------------------------------------------

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		return (_Month == 12);
	}

	//-----------------------------------------------------

	static	bool IsValidDate(clsDate Date)
	{

		if (Date.Day < 1 || Date.Day>31)
			return false;

		if (Date.Month < 1 || Date.Month>12)
			return false;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}
			else
			{
				if (Date.Day > 28)
					return false;
			}
		}

		short DaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth)
			return false;

		return true;

	}


	//-----------------------------------------------------

	static clsDate AddOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}
	void AddOneDay()
	{
		AddOneDay(*this);
	}

	//-----------------------------------------------------

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		//this will take care of negative diff
		int Days = 0;
		short SawpFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SawpFlagValue = -1;

		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = AddOneDay(Date1);
		}

		return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}



	//-----------------------------------------------------

	static void  SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate tempDate = Date1;
		Date1 = Date2;
		Date2 = tempDate;
	}
	//-----------------------------------------------------

	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Year = now->tm_year + 1900;
		Date.Month = now->tm_mon + 1;
		Date.Day = now->tm_mday;

		return Date;
	}

	//-----------------------------------------------------

	static short CalculateYourAgeInDays(clsDate DateOfBirth)
	{
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}

	//-----------------------------------------------------

	static clsDate IncreaseDateByXDays(clsDate& Date, int NumberOfDayes)
	{

		for (int i = 1; i <= NumberOfDayes; i++)
		{
			AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(int NumberOfDayes)
	{
		IncreaseDateByXDays(*this, NumberOfDayes);
	}

	//-----------------------------------------------------

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	//-----------------------------------------------------

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}
		short NumberOfDayInCurrntMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (NumberOfDayInCurrntMonth > Date.Day)
		{
			Date.Day = NumberOfDayInCurrntMonth;
		}
		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	//-----------------------------------------------------

	static clsDate IncreaseDateByXMonths(clsDate& Date, int NumberOfMonths)
	{
		for (int i = 1; i <= NumberOfMonths; i++)
		{
			IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonths(int NumberOfMonths)
	{
		IncreaseDateByXMonths(*this, NumberOfMonths);
	}

	//-----------------------------------------------------

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	//-----------------------------------------------------

	static clsDate IncreaseDateByXYears(clsDate& Date, int NumberOfYears)
	{
		Date.Year += NumberOfYears;
		return Date;
	}
	void IncreaseDateByXYears(int NumberOfYears)
	{
		IncreaseDateByXYears(*this, NumberOfYears);
	}

	//_________________________________________________________________________________

	static clsDate IncreaseDateByOneDecade(clsDate& Date) {
		Date.Year += 10;
		return Date;

	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	//_________________________________________________________________________________

	static clsDate IncreaseDateByXDecade(clsDate& Date, int NumberOfDecades)
	{
		Date.Year += NumberOfDecades * 10;
		return Date;
	}
	void IncreaseDateByXDecade(int NumberOfDecades)
	{
		IncreaseDateByXDecade(*this, NumberOfDecades);
	}

	//_________________________________________________________________________________

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	//_________________________________________________________________________________

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.Day == 1)
		{
			if ((Date.Month == 1))
			{
				Date.Year--;
				Date.Month = 12;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
			}
		}
		else
		{
			Date.Day--;
		}
		return Date;
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByXDay(clsDate& Date, int Days)
	{
		for (int i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDay(int Days)
	{
		DecreaseDateByXDay(*this, Days);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByXWeek(clsDate& Date, int Weeks)
	{
		for (int i = 1; i <= Weeks; i++)
		{
			DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeek(int Weeks)
	{
		DecreaseDateByXWeek(*this, Weeks);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;

		}
		else
		{
			Date.Month--;
		}
		//ÅÐÇ ßÇä ÚÏÏ ÇáÃíÇã Ýí ÇáÔåÑ ÈÚÏ ÇáÓÇÈÞ ÃßÈÑ ãä ÚÏÏ ÇáÃíÇã Ýí ÇáÔåÑ ÇáÍÇáí
		short NumberOfDaysInCurrnMonth = NumberOfDaysInMonth(Date.Year, Date.Month);
		if (Date.Day > NumberOfDaysInCurrnMonth)
		{
			Date.Day = NumberOfDaysInCurrnMonth;
		}

		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByXMonth(clsDate& Date, int Months)
	{
		for (int i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonth(int Months)
	{
		DecreaseDateByXMonth(*this, Months);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;

		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByXYear(clsDate& Date, int Years)
	{
		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYear(int Years)
	{
		DecreaseDateByXYear(*this, Years);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByXDecade(clsDate& Date, int Decades)
	{
		Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecade(int Decades)
	{
		DecreaseDateByXDecade(*this, Decades);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	//_________________________________________________________________________________

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	//_________________________________________________________________________________

	static bool IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date) == 6;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	//_________________________________________________________________________________

	static bool IsWeekEnd(clsDate Date)
	{
		short DayIndex = DayOfWeekOrder(Date);
		return DayIndex == 5 || DayIndex == 6;
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	//_________________________________________________________________________________

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	//_________________________________________________________________________________

	static  short DaysUntilEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}
	short  DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}

	//_________________________________________________________________________________

	static short DaysUntilEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;
		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}
	short DaysUntilEndOfMonth()
	{
		return DaysUntilEndOfMonth(*this);
	}

	//_________________________________________________________________________________

	static int DaysUntilEndOfYear(clsDate Date)
	{
		clsDate EndOfYearsDate;
		EndOfYearsDate.Day = 31;
		EndOfYearsDate.Month = 12;
		EndOfYearsDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearsDate, true);

	}
	int DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}
	//_________________________________________________________________________________

	static short CalculateVactionDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
			{
				DaysCount++;
			}
			DateFrom = AddOneDay(DateFrom);

		}
		return DaysCount;
	}
	short CalculateVactionDays(clsDate DateTo)
	{
		return CalculateVactionDays(*this, DateTo);
	}
	//_________________________________________________________________________________

	static clsDate CalculateVactionDaysReturnDate(clsDate DateFrom, short VactionDays)
	{
		short WeekEndCounter = 0;
		for (int i = 1; i <= VactionDays; i++)
		{
			if (IsWeekEnd(DateFrom))
			{
				WeekEndCounter++;
			}
			DateFrom = AddOneDay(DateFrom);

		}
		for (int i = 1; i <= WeekEndCounter; i++)
		{
			DateFrom = AddOneDay(DateFrom);
		}

		return DateFrom;
	}
	clsDate CalculateVactionDaysReturnDate(short VactionDays)
	{
		return CalculateVactionDaysReturnDate(*this, VactionDays);
	}

	//_________________________________________________________________________________

	static  bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}
	enum enDateCompare { Befor = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDate(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Befor;
		else if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	short CompareDate(clsDate Date2)
	{
		return CompareDate(*this, Date2);
	}

	//_________________________________________________________________________________

	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return  DateToString(*this);
	}

	//_________________________________________________________________________________

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{

		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}

		return Date;
	}
};

