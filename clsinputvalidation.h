#pragma once
#include <iostream>
#include "clsdate.h"
using namespace std;

class clsinputvalidation
{
public:

	static bool IsNumberBetween(int number, int from, int to)
	{
		return (number >= from && number <= to);
	}

	static bool IsNumberBetween(double number, double from, double to)
	{
		return (number >= from && number <= to);
	}

	static bool IsDateBetween(clsdate date, clsdate datefrom, clsdate dateto)
	{
		return ((clsdate::IsDateEqualDate(date, datefrom) || clsdate::IsDateAfterDate(date, datefrom))
			&& (clsdate::IsDateEqualDate(date, dateto) || clsdate::IsDateBeforeDate(date, dateto)));
	}

	static int ReadNumber(string invalidMessage)
	{
		int number;
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cout << invalidMessage;
			cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			cin >> number;
		}
		return number;
	}

	static double ReadDBLNumber(string invalidMessage)
	{
		double number;
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cout << invalidMessage;
			cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			cin >> number;
		}
		return number;
	}

	static int ReadIntNumberBetween(int from, int to, string invalidMessage)
	{
		int number = ReadNumber("Invalid Value , Please Enter Again:");
		while (!IsNumberBetween(number, from, to))
		{
			cout << invalidMessage << endl;
			number = ReadNumber("Invalid Value , Please Enter Again:");
		}
		return number;
	}

	static double ReadIntNumberDblBetween(double from, double to, string invalidMessage)
	{
		double number = ReadNumber("Invalid Value , Please Enter Again:");
		while (!IsNumberBetween(number, from, to))
		{
			cout << invalidMessage << endl;
			number = ReadNumber("Invalid Value , Please Enter Again:");
		}
		return number;
	}

	static bool IsValidDate(clsdate date)
	{
		return clsdate::IsValidDate(date);
	}

	static string ReadString()
	{
		string value;
		getline(cin >> ws, value);
		return value;
	}

	static short ReadNumberBetween(short from, short to, string ErrorMessage)
	{
		short number;
		cin >> number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
			cin >> number;
		}
		while (number<from || number>to)
		{
			cout << ErrorMessage;
			cin >> number;
		}
		return number;
	}

};

