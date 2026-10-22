#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency currency)
	{
		cout << "\nCurrency Card: \n";
		cout << "________________________________________\n\n";
		cout << "Country      : " << currency.Country << endl;
		cout << "Code         : " << currency.CurrencyCode << endl;
		cout << "Name         : " << currency.CurrencyName << endl;
		cout << "Rate(1$) is  : " << currency.Rate << endl;
		cout << "\n________________________________________\n\n";
	}

	static void _ShowSearchResult(clsCurrency currency)
	{
		if (!currency.IsEmpty())
		{
			_PrintCurrencyCard(currency);
		}
		else
		{
			cout << "\nCurrency was not found!\n";
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t    Find Currency Screen");
		short answer = 0;
		cout << "\nFind By: [1] Code OR [2] Country? ";
		answer = clsinputvalidation::ReadNumberBetween(1, 2, "Wrong Value , Find By: [1] Code OR [2] Country? ");
		if (answer == 1)
		{
			string Code;
			cout << "\nPlease enter Currency Code : ";
			Code = clsinputvalidation::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowSearchResult(Currency);
		}
		else
		{
			string Country;
			cout << "\nPlease enter Country Name : ";
			Country = clsinputvalidation::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowSearchResult(Currency);
		}
	}

};

