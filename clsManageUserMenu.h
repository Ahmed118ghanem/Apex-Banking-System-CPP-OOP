#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsinputvalidation.h"
#include "clsScreen.h"
#include "clsListUserScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUserMenu : protected clsScreen
{
private:
	enum enManageUserMenuOption{eListUser = 1 , eAddNewUser = 2 , eDeleteUser = 3 , eUpdateUser=4,
	                            eFindUser = 5 , eMainMenu = 6};

	static short _ReadManageUserMenuOption()
	{
		short choose;
		cout << setw(36) << "" << left << "Choose what do you want to do? [1 to 6]? ";
		choose = clsinputvalidation::ReadNumberBetween(1, 6, "\t\t\t\t    Wrong Value , Enter Number between [1 to 6]? ");
		return choose;
	}

	static void _GoBackToManageUserMenu()
	{
		cout << "\n\nPress any key to go back to Transaction Menu...";
		system("pause>0");
		ShowManageUserMenuScreen();
	}

	static void _ShowListUserScreen()
	{
		clsListUserScreen::_ShowListUserScreen();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::_ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenuOption(enManageUserMenuOption ManageUsersOption)
	{
		switch (ManageUsersOption)
		{
		case enManageUserMenuOption::eListUser:
			system("cls");
			_ShowListUserScreen();
			_GoBackToManageUserMenu();
			break;
		case enManageUserMenuOption::eAddNewUser:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUserMenu();
			break;
		case enManageUserMenuOption::eDeleteUser:
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUserMenu();
			break;
		case enManageUserMenuOption::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUserMenu();
			break;
		case enManageUserMenuOption::eFindUser:
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUserMenu();
			break;
		case enManageUserMenuOption::eMainMenu:
			//do nothing mainmenu will handle it.
			break;
		}
	}

public:

	static void ShowManageUserMenuScreen()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eManageUser))
		{
			return; //it will exit the function and it will not continue.
		}
		system("cls");
		_DrawScreenHeader("\t  Manage Users Screen");
		cout << setw(36) << "" << left << "=================================================\n";
		cout << setw(36) << "" << left << "\t\t   Manage Users Menu\n";
		cout << setw(36) << "" << left << "=================================================\n";
		cout << setw(38) << "" << left << " [1] List Users.\n";
		cout << setw(38) << "" << left << " [2] Add New User.\n";
		cout << setw(38) << "" << left << " [3] Delete User.\n";
		cout << setw(38) << "" << left << " [4] Update User.\n";
		cout << setw(38) << "" << left << " [5] Find User.\n";
		cout << setw(38) << "" << left << " [6] Main Menu.\n";
		cout << setw(36) << "" << left << "=================================================\n";
		_PerformManageUsersMenuOption((enManageUserMenuOption)_ReadManageUserMenuOption());
	}

};

