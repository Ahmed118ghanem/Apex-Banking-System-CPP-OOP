#pragma once
#include <iostream>
#include "clsScreen.h" 
#include "clsCurrency.h"
#include "clsinputvalidation.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
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

	static void _UpdateCurrency(clsCurrency currency)
	{
		cout << "\nUpdate Currency Rate: \n";
		cout << "______________________________________\n\n";
		cout << "Enter New Rate: ";
		double NewRate = clsinputvalidation::ReadDBLNumber("Wrong Value , Enter the New Rate Number : ");
		currency.Update(NewRate);
		cout << "\n\nCurrency Rate Updated Successfully :-)"<<endl;
		_PrintCurrencyCard(currency);
	}

public:

	static void ShowUpdateRateScreen()
	{
		_DrawScreenHeader("\t    Update Currency Screen");
		cout << "\n\nPlease Enter Currency Code: ";
		string Code = clsinputvalidation::ReadString();
		while (!clsCurrency::IsCurrencyExist(Code))
		{
			cout << "Incorrect Currency Code , Enter another one: ";
			Code = clsinputvalidation::ReadString();
		}
		clsCurrency Currecny = clsCurrency::FindByCode(Code);
		_PrintCurrencyCard(Currecny);
		string Answer;
		cout << "\nAre you sure you want to update the rate of this currency? Y/N ? ";
		Answer = clsinputvalidation::ReadString();
		if (Answer == "y" || Answer == "Y")
		{
			_UpdateCurrency(Currecny);
		}
		else
		{
			cout << "\nThe Operation was cancelled" << endl;
		}
	}

};

