#pragma once
#pragma warning(disable : 4996) 
#include <iostream>
#include "clsstring.h"
#include <string>
#include <vector>
using namespace std;


class clsdate
{
private:
	short _day = 1;
	short _month = 1;
	short _year = 1900;
	short _Hour = 0;
	short _Minute = 0;
	short _Second = 0;
public:

	clsdate()
	{
		time_t t = time(0);
		tm* local = localtime(&t);
		_day = local->tm_mday;
		_month = local->tm_mon + 1;
		_year = local->tm_year + 1900;
		_Hour = local->tm_hour;
		_Minute = local->tm_min;
		_Second = local->tm_sec;
	}

	clsdate(string date)
	{
		vector <string> vdate = clsstring::Split(date, "/");
		_day = stoi(vdate[0]);
		_month = stoi(vdate[1]);
		_year = stoi(vdate[2]);
	}

	clsdate(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}

	clsdate(short days, short year)
	{
		clsdate date = GetDateOfBeginningOfYear(days, year);
		_day = date.Day;
		_month = date.Month;
		_year = date.Year;
	}

	void SetDay(short day)
	{
		_day = day;
	}

	short GetDay()
	{
		return _day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short month)
	{
		_month = month;
	}

	short GetMonth()
	{
		return _month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_year = Year;
	}

	short GetYear()
	{
		return _year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static clsdate SystemDate()
	{
		clsdate date;

		time_t t = time(0);
		tm* local = localtime(&t);
		date._day = local->tm_mday;
		date._month = local->tm_mon + 1;
		date._year = local->tm_year + 1900;
		return date;
	}

	static bool IsLeapYear(short year)
	{
		return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_year);
	}

	static short GetNumberOfDaysInMonth(short month, short year)
	{
		short arr[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		if (month < 1 || month>12)
			return 0;
		return (month == 2 && IsLeapYear(year)) ? 29 : arr[month - 1];
	}

	short GetNumberOfDaysInMonth()
	{
		return GetNumberOfDaysInMonth(_month, _year);
	}

	static clsdate GetDateOfBeginningOfYear(short Days, short year)
	{
		clsdate date;
		date.Month = 1;
		date.Year = year;
		short remaining = Days;
		while (true)
		{
			short monthdays = GetNumberOfDaysInMonth(date.Month, date.Year);
			if (remaining > monthdays)
			{
				remaining -= monthdays;
				if (date.Month == 12)
				{
					date.Month = 1;
					date.Year++;
				}
				else
				{
					date.Month++;
				}
			}
			else
			{
				date.Day = remaining;
				break;
			}
		}
		return date;
	}

	static short GetDayOrder(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12, y = Year - a, m = Month + (12 * a) - 2;
		short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
		return d;
	}

	short GetDayOrder()
	{
		return GetDayOrder(_day, _month, _year);
	}

	static string GetDayName(short dayorder)
	{
		string arr[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arr[dayorder];
	}

	string GetDayName()
	{
		return GetDayName(GetDayOrder());
	}

	static string GetMonthName(short Month)
	{
		string arr[] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return arr[Month - 1];
	}

	string GetMonthName()
	{
		return GetMonthName(_month);
	}

	static void PrintMonthCalendar(short month, short year)
	{
		short dayorder = GetDayOrder(1, month, year);
		short numberofdaysinmonth = GetNumberOfDaysInMonth(month, year);
		printf("   __________________%s___________________\n", GetMonthName(month).c_str());
		cout << "\n   Sun   Mon   Tue   Wed   Thu   Fri   Sat\n";

		int i = 0;

		for (i; i < dayorder; i++)
			printf("      ");
		for (int x = 1; x <= numberofdaysinmonth; x++)
		{
			printf("%6d", x);
			if (++i == 7)
			{
				printf("\n");
				i = 0;
			}
		}

		printf("\n   ________________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(Month, Year);
	}

	static void PrintYearCalendar(short year)
	{
		printf("\n   ________________________________________\n");
		printf("\n\t\tCalender - %d\n", year);
		printf("   ________________________________________\n\n");
		for (int x = 1; x <= 12; x++)
		{
			clsdate date(1, x, year);
			PrintMonthCalendar(x, year);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(Year);
	}

	static string DateToString(clsdate date)
	{
		return  to_string(date._day) + "/" + to_string(date._month) + "/" + to_string(date._year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	void print()
	{
		cout << DateToString() << endl;
	}

	static bool IsValidDate(clsdate date)
	{

		short monthdays = GetNumberOfDaysInMonth(date.Month, date.Year);

		if (date.Month < 1 || date.Month>12)
			return false;

		if (date.Day<1 || date.Day>monthdays)
			return false;

		return true;
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static short NumberOfDaysInYear(short year)
	{
		return (IsLeapYear(year)) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_year);
	}

	static short NumberOfHoursInYear(short year)
	{
		return NumberOfDaysInYear(year) * 24;
	}

	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(_year);
	}

	static short NumberOfMinutesInYear(short year)
	{
		return NumberOfHoursInYear(year) * 60;
	}

	short NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(_year);
	}

	static int NumberOfSecondsInYear(short year)
	{
		return NumberOfMinutesInYear(year) * 60;
	}

	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(_year);
	}

	static short NumberOfHoursInMonth(short month, short year)
	{
		return GetNumberOfDaysInMonth(month, year) * 24;
	}

	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_month, _year);
	}

	static short NumberOfMinutesInMonth(short month, short year)
	{
		return  NumberOfHoursInMonth(month, year) * 60;
	}

	short NumberOfMinutesInMonth()
	{
		return  NumberOfMinutesInMonth(_month, _year);
	}

	static int NumberOfSecondsInMonth(short month, short year)
	{
		return  NumberOfMinutesInMonth(month, year) * 60;
	}

	int NumberOfSecondsInMonth()
	{
		return  NumberOfSecondsInMonth(_month, _year);
	}

	static short DaysFromBeginningOfTheYear(short days, short month, short year)
	{
		short Totaldays = 0;

		for (int x = 1; x < month; x++)
		{
			Totaldays += GetNumberOfDaysInMonth(x, year);
		}
		return Totaldays + days;
	}

	short DaysFromBeginningOfTheYear()
	{
		return DaysFromBeginningOfTheYear(_day, _month, _year);
	}

	void AddingDays(short days)
	{
		short remainder = days + DaysFromBeginningOfTheYear(_day, _month, _year);
		_month = 1;
		while (true)
		{
			short monthdays = GetNumberOfDaysInMonth(_month, _year);
			if (remainder > monthdays)
			{
				remainder -= monthdays;
				if (_month == 12)
				{
					_month = 1;
					_year++;
				}
				else
				{
					_month++;
				}
			}
			else
			{
				_day = remainder;
				break;
			}

		}

	}

	static bool IsDateBeforeDate(clsdate date1, clsdate date2) // 2022 , 2023
	{
		return (date1.Year < date2.Year) ? true : ((date1.Year == date2.Year) ? (date1.Month < date2.Month ? true : (date1.Month == date2.Month ? date1.Day < date2.Day : false)) : false);
	}

	bool IsDateBeforeDate(clsdate date2)
	{
		return IsDateBeforeDate(*this, date2);
	}

	static bool IsDateEqualDate(clsdate date1, clsdate date2)
	{
		return(date1.Day == date2.Day && date1.Month == date2.Month && date1.Year == date2.Year);
	}

	bool IsDateEqualDate(clsdate date2)
	{
		return IsDateEqualDate(*this, date2);
	}

	static bool IsDateAfterDate(clsdate date1, clsdate date2)
	{
		return !(IsDateEqualDate(date1, date2) || IsDateBeforeDate(date1, date2));
	}

	bool IsDateAfterDate(clsdate date2)
	{
		return IsDateAfterDate(*this, date2);
	}

	static bool IsLastDayInMonth(clsdate date)
	{
		return (date.Day == GetNumberOfDaysInMonth(date.Month, date.Year));
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(clsdate date)
	{
		return (date.Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(*this);
	}

	static clsdate AddOneDay(clsdate date)
	{
		if (IsLastDayInMonth(date))
		{
			date.Day = 1;
			if (IsLastMonthInYear(date))
			{
				date.Month = 1;
				date.Year++;
			}
			else
			{
				date.Month++;
			}
		}
		else
		{
			date.Day++;
		}
		return date;
	}

	clsdate AddOneDay()
	{
		return AddOneDay(*this);
	}

	static void SwapDates(clsdate& date1, clsdate& date2)
	{
		clsdate temp_date;
		temp_date = date1;
		date1 = date2;
		date2 = temp_date;
	}

	static int GetDifferenceInDays(clsdate date1, clsdate date2, bool matchcase = false)
	{
		int Differencedays = 0;
		short swap = 1;
		if (!IsDateBeforeDate(date1, date2) && !IsDateEqualDate(date1, date2))
		{
			SwapDates(date1, date2);
			swap = -1;
		}
		while (IsDateBeforeDate(date1, date2))
		{
			Differencedays++;
			date1 = AddOneDay(date1);
		}
		return (matchcase) ? ++Differencedays * swap : Differencedays * swap;
	}

	int GetDifferenceInDays(clsdate date2, bool matchcase = false)
	{
		return GetDifferenceInDays(*this, date2, matchcase);
	}

	static short CalculateMyAge(clsdate& date)
	{
		return GetDifferenceInDays(date, clsdate::SystemDate(), true);
	}

	static clsdate IncreaseDateByOneWeek(clsdate date)
	{
		for (int x = 1; x <= 7; x++)
		{
			date = AddOneDay(date);
		}
		return date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsdate IncreaseDateByXweek(short number, clsdate& date)
	{
		for (int x = 1; x <= number; x++)
		{
			date = IncreaseDateByOneWeek(date);
		}
		return date;
	}

	clsdate IncreaseDateByXweek(short number)
	{
		return IncreaseDateByXweek(number, *this);
	}

	static clsdate IncreaseDateByOneMonth(clsdate& date)
	{
		if (date.Month == 12)
		{
			date.Month = 1;
			date.Year++;
		}
		else
		{
			date.Month++;
		}
		short monthdays = GetNumberOfDaysInMonth(date.Month, date.Year);
		if (date.Day > monthdays)
		{
			date.Day = monthdays;
		}
		return date;
	}

	clsdate IncreaseDateByOneMonth()
	{
		return IncreaseDateByOneMonth(*this);
	}

	static clsdate IncreaseDateByXMonth(short month, clsdate& date)
	{
		for (int x = 1; x <= month; x++)
		{
			date = IncreaseDateByOneMonth(date);
		}
		return date;
	}

	clsdate IncreaseDateByXMonth(short month)
	{
		return IncreaseDateByXMonth(month, *this);
	}

	static clsdate IncreaseDateByOneYear(clsdate& date)
	{
		date.Year++;
		return date;
	}

	clsdate IncreaseDateByOneYear()
	{
		return IncreaseDateByOneYear(*this);
	}

	static clsdate IncreaseDateByXyear(clsdate& date, short year)
	{
		date.Year += year;
		return date;
	}

	clsdate IncreaseDateByXyear(short year)
	{
		return IncreaseDateByXyear(*this, year);
	}

	static bool IsEndOfWeek(clsdate date)
	{
		short dayorder = GetDayOrder(date.Day, date.Month, date.Year);
		return (dayorder == 5 || dayorder == 6);
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static string GetDateAndTimeLine(clsdate date)
	{
		return  DateToString(date) + " - " + to_string(date._Hour) + ":" + to_string(date._Minute) + ":" + to_string(date._Second);
	}

	string GetDateAndTimeLine()
	{
		return GetDateAndTimeLine(*this);
	}

};


