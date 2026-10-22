#pragma once
#include <iostream>
#include <iomanip>
#include "clsCurrency.h"
#include "clsinputvalidation.h"
#include "clsBankUsers.h"
#include "clsScreen.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExchangeMainMenu : protected clsScreen
{
private:

	enum enCurrencyMainMenuOption{ListCurrencies=1 , FindCurrencies = 2 , UpdateRate = 3 , CurrencyCalculator = 4,
	                              MainMenu = 5};

	static short _ReadCurrenciesMainMenuOption()
	{
		short Choose;
		cout << setw(39) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		Choose = clsinputvalidation::ReadNumberBetween(1, 5, "\t\t\t\t       Wrong Value,Enter Number Between [1 to 5]? ");
		return Choose;
	}

	static void _GoBackToCurrencyExchangeScreen()
	{
		cout << "\nPress any key to go back to Currencies Menu...";
		system("pause>0");
		ShowCurrencyExchangeMainScreen();
	}

	static void _ShowCurrenciesList()
	{
		clsListCurrenciesScreen::CurrencyInformationListScreen();
	}

	static void _ShowFindCurrency()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrencyMainMenuOption(enCurrencyMainMenuOption CurrencyMainMenuOption)
	{
		switch (CurrencyMainMenuOption)
		{
		case enCurrencyMainMenuOption::ListCurrencies:
			system("cls");
			_ShowCurrenciesList();
			_GoBackToCurrencyExchangeScreen();
			break;
		case enCurrencyMainMenuOption::FindCurrencies:
			system("cls");
			_ShowFindCurrency();
			_GoBackToCurrencyExchangeScreen();
			break;
		case enCurrencyMainMenuOption::UpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeScreen();
			break;
		case enCurrencyMainMenuOption::CurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeScreen();
			break;
		case enCurrencyMainMenuOption::MainMenu:
			//do nothing main menu will be handle it;
			break;
		}
	}

public:

	static void ShowCurrencyExchangeMainScreen()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eCurrencyExchange))
		{
			return; //it will exit the function and it will not continue.
		}
		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");
		cout << setw(39) << left << "" << "============================================\n";
		cout << setw(50) << left << "" << "Currency Exchange Menu\n";
		cout << setw(39) << left << "" << "============================================\n";
		cout << setw(42) << left << "" << "[1] List Currencies.\n";
		cout << setw(42) << left << "" << "[2] Find Currency.\n";
		cout << setw(42) << left << "" << "[3] Update Rate.\n";
		cout << setw(42) << left << "" << "[4] Currency Calculator.\n";
		cout << setw(42) << left << "" << "[5] Main Menu.\n";
		cout << setw(39) << left << "" << "============================================\n";
		_PerformCurrencyMainMenuOption((enCurrencyMainMenuOption)_ReadCurrenciesMainMenuOption());
	}

};

