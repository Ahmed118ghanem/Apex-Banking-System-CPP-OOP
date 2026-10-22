#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsShowTransactionMenu.h"
#include "clsManageUserMenu.h"
#include "clsGlobal.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainMenu.h"

class clsMainMenuScreen : protected clsScreen
{
private:

	enum enMainMenuOption{eShowClientList = 1 , eAddClient = 2 , eDeleteClient = 3 , eUpdateClient = 4 ,eFindClient = 5 , 
		     eTransactionScreen = 6 , eManageUsers = 7 , eLoginRegister = 8 , eCurrencyExchange = 9 ,eLogout = 10};

	static short ReadMainMenuOption()
	{
		cout << setw(36) << "" << left << "Choose What do you want to do? [1 to 10]? ";
		short Choose = clsinputvalidation::ReadNumberBetween(1, 10, "\t\t\t\t    Wrong Value , Enter Number between [1 to 10]? ");
		return Choose;
		
	}

	static void _GoBackToMainMenu()
	{
		cout << "\nPress any key to go back to Main Menu...";
		system("pause>0");
		ShowMainMenuScreen();
	}

	static void _ShowClientList()
	{
		clsClientsListScreen::ShowClientListScreen();
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();

	}

	static void _ShowTransactionScreen()
	{
		clsShowTransactionMenu::_ShowTransactionMenu();
	}

	static void _ShowManageUsersScreen()
	{
		clsManageUserMenu::ShowManageUserMenuScreen();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterListScreen();
	}

	static void _ShowCurrencyExchange()
	{
		clsCurrencyExchangeMainMenu::ShowCurrencyExchangeMainScreen();
	}

	static void _PerformMainMenuOption(enMainMenuOption MainMenuOption)
	{
		switch (MainMenuOption)
		{
		case enMainMenuOption::eShowClientList:
			system("cls");
			_ShowClientList();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eAddClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eTransactionScreen:
			system("cls");
			_ShowTransactionScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eManageUsers:
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eCurrencyExchange:
			system("cls");
			_ShowCurrencyExchange();
			_GoBackToMainMenu();
			break;
		case enMainMenuOption::eLogout:
			CurrentUser =  CurrentUser.Find("", "");
			break;
		}
	}

public:

	static void ShowMainMenuScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tMain Screen");
		cout << setw(36)  << "" << left << "=================================================\n";
		cout << setw(36) << "" << left << "\t\t\tMain Menu\n";
		cout << setw(36) << "" << left << "=================================================\n";
		cout << setw(36) << "" << left << "\t[1] Show Client List.\n";
		cout << setw(36) << "" << left << "\t[2] Add New Client.\n";
		cout << setw(36) << "" << left << "\t[3] Delete Client.\n";
		cout << setw(36) << "" << left << "\t[4] Update Client.\n";
		cout << setw(36) << "" << left << "\t[5] Find Client.\n";
		cout << setw(36) << "" << left << "\t[6] Transactions.\n";
		cout << setw(36) << "" << left << "\t[7] Manage Users.\n";
		cout << setw(36) << "" << left << "\t[8] Login Register.\n";
		cout << setw(36) << "" << left << "\t[9] Currency Exchange.\n";
		cout << setw(36) << "" << left << "\t[10] Logout.\n";
		cout << setw(36) << "" << left << "=================================================\n";
		_PerformMainMenuOption((enMainMenuOption)ReadMainMenuOption());
	}

};

