#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsShowTransactionMenu : protected clsScreen
{
private:

	enum enTransactionOptions{eDeposit = 1 , eWithdraw=2 , eTotalBalances = 3  , eTransfer = 4, eTransferLog , eMainMenu = 6};

	static short _ReadTransactionMenuOptions()
	{
		short choose;
		cout << setw(38) << "" << left << "Choose what do you want to do? [1 to 6]? ";
		choose = clsinputvalidation::ReadNumberBetween(1, 6, "\t\t\t\t      Wrong Value , Enter Number between [1 to 6]? ");
		return choose;
	}

	static void _GoBackToTransactionMenu()
	{
		cout << "\nPress any key to go back to Transaction Menu...";
		system("pause>0");
		_ShowTransactionMenu();
	}

	static void _Deposit()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _Withdraw()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _TotalBalances()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _TransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}
	
	static void _TransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _PerformTransactionMenu(enTransactionOptions TransactionOptions)
	{
		switch (TransactionOptions)
		{
		case enTransactionOptions::eDeposit:
			system("cls");
			_Deposit();
			_GoBackToTransactionMenu();
			break;
		case enTransactionOptions::eWithdraw:
			system("cls");
			_Withdraw();
			_GoBackToTransactionMenu();
			break;
		case enTransactionOptions::eTotalBalances:
			system("cls");
			_TotalBalances();
			_GoBackToTransactionMenu();
			break;
		case enTransactionOptions::eTransfer:
			system("cls");
			_TransferScreen();
			_GoBackToTransactionMenu();
			break;
		case enTransactionOptions::eTransferLog:
			system("cls");
			_TransferLogScreen();
			_GoBackToTransactionMenu();
			break;
		case enTransactionOptions::eMainMenu:
			//do nothing main menu will handle it.
			break;
		}
	}

public:

	static void _ShowTransactionMenu()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eTransaction))
		{
			return; //it will exit the function and it will not continue.
		}
		system("cls");
		_DrawScreenHeader("\t   Transaction Screen");
		cout << setw(38) << "" << left << "=============================================\n";
		cout << setw(38) << "" << left << "\t\t    Transaction Menu\n";
		cout << setw(38) << "" << left << "=============================================\n";
		cout << setw(38) << "" << left << "\t  [1] Deposit.\n";
		cout << setw(38) << "" << left << "\t  [2] Withdraw.\n";
		cout << setw(38) << "" << left << "\t  [3] Total Balances.\n";
		cout << setw(38) << "" << left << "\t  [4] Transfer.\n";
		cout << setw(38) << "" << left << "\t  [5] Transfer Log.\n";
		cout << setw(38) << "" << left << "\t  [6] Main Menu.\n";
		cout << setw(38) << "" << left << "=============================================\n";
		_PerformTransactionMenu((enTransactionOptions)_ReadTransactionMenuOptions());
	}

};

