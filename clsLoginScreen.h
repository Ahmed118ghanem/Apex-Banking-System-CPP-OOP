#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankUsers.h"
#include "clsGlobal.h"
#include "clsinputvalidation.h"
#include "clsScreen.h"
#include "clsMainMenuScreen.h"
class clsLoginScreen : protected clsScreen
{

private:

	

	static bool _Log()
	{
		bool LoginFailed = false;
		short Trials=0;
		do
		{
			system("cls");
			_DrawScreenHeader("\t\tLogin Screen");
			if (LoginFailed)
			{
				Trials++;
				cout << "Invalid Username/Password!\n";
				cout << "You have " << 3 - Trials << " Trials to login.\n";
				if (Trials == 3)
				{
					cout << "\n\nYou are locked after " << Trials << " failed trials.\n";
					return false;
				}
			}
			cout << "\nEnter User Name : ";
			string username = clsinputvalidation::ReadString();
			cout << "Enter Password  : ";
			string password = clsinputvalidation::ReadString();
			CurrentUser = clsBankUsers::Find(username, password);
			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);
		CurrentUser.AddLoginRegisterToFile();
		clsMainMenuScreen::ShowMainMenuScreen();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		return _Log();
	}

};

