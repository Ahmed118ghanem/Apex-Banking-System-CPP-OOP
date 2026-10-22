#pragma once
#include <iostream>
#include <vector> 
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"

class clsListCurrenciesScreen : protected clsScreen
{
private:

	static void _FillCurrencyInformationInTheTable(vector <clsCurrency> VCurrency)
	{
		for (clsCurrency C : VCurrency)
		{
			cout << setw(10) << left << "" << "| " << setw(36) << left << C.Country;
			cout << "| " << setw(8) << left << C.CurrencyCode;
			cout << "| " << setw(40) << left << C.CurrencyName;
			cout << "| " << setw(10) << left << C.Rate;
			cout << endl;
		}
	}

public:

	static void CurrencyInformationListScreen()
	{
		vector <clsCurrency> VCurrency = clsCurrency::GetCurrencyList();
		string Titel = "\t   Currency List Screen";
		string SubTitel = "\t     (" + to_string(VCurrency.size()) + ") Currency.";
		_DrawScreenHeader(Titel, SubTitel);
		cout << setw(10) << left << "" << "_____________________________________________________________________________________________________\n\n";
		cout << setw(10) << left << "" << setw(38) << left << "| Country";
		cout << setw(10) << left << "| Code";
		cout << setw(42) << left << "| Name";
		cout << setw(10) << left << "| Rate/(1$)\n";
		cout << setw(10) << left << "" << "_____________________________________________________________________________________________________\n\n";
		_FillCurrencyInformationInTheTable(VCurrency);
		cout << setw(10) << left << "" << "_____________________________________________________________________________________________________\n";
	}

};

