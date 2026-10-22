#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsGlobal.h"
#include "clsBankUsers.h"
#include "clsDate.h"

using namespace std;
class clsScreen
{
protected:

	static void _DrawScreenHeader(string Titel, string SubTitel = "")
	{
		cout << "\n\t\t\t\t\t__________________________________________\n\n";
		cout << "\t\t\t\t\t" << Titel;
		if (SubTitel != "")
		{
			cout << "\n\t\t\t\t\t" << SubTitel;
		}
		cout << "\n\t\t\t\t\t__________________________________________\n\n";
		cout << "\t\t\t\t\tUser : " << CurrentUser.UserName << endl;
		cout << "\t\t\t\t\tDate : " << clsdate::DateToString(clsdate()) << "\n" << endl;

	}

	static bool _CheckAccessRight(clsBankUsers::enPermission permission)
	{
		if (!CurrentUser.CheckUsersPermission(permission))
		{
			system("cls");
			cout << setw(36) << left << "" << "_________________________________________________\n" << endl;
			cout << setw(53) << left << "" << "Access Denied," << endl;
			cout << setw(42) << left << "" << "You don't have permission to do this," << endl;
			cout << setw(47) << left << "" << "Please contact your Admin." << endl;
			cout << setw(36) << left << "" << "_________________________________________________" << endl;
			return false;
		}
		return true;
	}

};

