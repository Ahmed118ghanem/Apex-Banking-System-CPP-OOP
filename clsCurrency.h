#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsstring.h"


class clsCurrency
{
private:

	enum enMode{EmptyMode = 1 , UpdateMode};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	double _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string line, string separator)
	{
		vector <string> vLine = clsstring::Split(line, separator);
		return clsCurrency(enMode::UpdateMode, vLine[0], vLine[1], vLine[2], stod(vLine[3]));
	}

	static vector <clsCurrency> _LoadDataFromCurrencyFile()
	{
		vector <clsCurrency> vCurrency;
		fstream myfile;
		myfile.open("CurrencyFile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line, "#//#");
				vCurrency.push_back(currency);
			}
			myfile.close();
		}
		return vCurrency;
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode,"","","",0);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency C , string Separator)
	{
		string line;
		line += C.Country + Separator;
		line += C.CurrencyCode + Separator;
		line += C.CurrencyName + Separator;
		line += to_string(C.Rate);
		return line;
	}

	static void _SaveDataToCurrencyFileAfterUpdate(vector <clsCurrency> &vCurrency)
	{
		fstream myfile;
		myfile.open("CurrencyFile.txt", ios::out);
		if (myfile.is_open())
		{
			for (clsCurrency C : vCurrency)
			{
				string line = _ConvertCurrencyObjectToLine(C, "#//#");
				myfile << line << endl;
			}

			myfile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrency = _LoadDataFromCurrencyFile();
		for (clsCurrency& C : vCurrency)
		{
			if (C.CurrencyCode == this->CurrencyCode)
			{
				C = *this;
				break;
			}
		}
		_SaveDataToCurrencyFileAfterUpdate(vCurrency);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, double Rate)
	{
		_Mode = Mode ;
		_Country = Country ;
		_CurrencyCode = CurrencyCode ;
		_CurrencyName = CurrencyName ;
		_Rate = Rate ;
	}

	string GetCountry()
	{
		return _Country;
	}

	__declspec(property(get = GetCountry)) string Country;

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	__declspec(property(get = GetCurrencyCode)) string CurrencyCode;

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	__declspec(property(get = GetCurrencyName)) string CurrencyName;

	double GetRate()
	{
		return _Rate;
	}

	__declspec(property(get = GetRate)) double Rate;

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsstring::UpperAllString(Country);
		fstream myfile;
		myfile.open("CurrencyFile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line, "#//#");
				if (clsstring::UpperAllString(currency.Country) == Country)
				{
					myfile.close();
					return currency;
				}
			}
			myfile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string Code)
	{
		Code = clsstring::UpperAllString(Code);
		fstream myfile;
		myfile.open("CurrencyFile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line, "#//#");
				if (clsstring::UpperAllString(currency.CurrencyCode) == Code)
				{
					myfile.close();
					return currency;
				}
			}
			myfile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static bool IsCurrencyExist(string Code)
	{
		clsCurrency C1 = FindByCode(Code);
		return (!C1.IsEmpty());
	}

	void Update(double NewRate)
	{
		this->_Rate = NewRate;
		_Update();
	}

	static vector <clsCurrency> GetCurrencyList()
	{
		return _LoadDataFromCurrencyFile();
	}

	double ConvertToUsd(double AmountToExchange)
	{
		return  AmountToExchange / this->_Rate ;
	}

	double ConvertRateToOtherCurrency(double AmountToExchange, clsCurrency ToCurrency)
	{
		if (ToCurrency.CurrencyCode == "USD")
		{
			return ConvertToUsd(AmountToExchange);
		}
		return ConvertToUsd(AmountToExchange) * ToCurrency.Rate;
	}

};

