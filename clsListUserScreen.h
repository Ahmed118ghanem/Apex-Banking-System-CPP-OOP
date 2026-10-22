#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankUsers.h"

class clsListUserScreen : protected clsScreen
{
private:

	static void _FillUsersInfoInList(vector <clsBankUsers> vusers)
	{
		for (clsBankUsers u : vusers)
		{
			cout << setw(12) << right << "| " << setw(10) << left << u.UserName;
			cout << "| " << setw(18) << left << u.FullName;
			cout << "| " << setw(18) << left << u.Phone;
			cout << "| " << setw(20) << left << u.Email;
			cout << "| " << setw(13) << left << u.Password;
			cout << "| " << setw(13) << left << u.Permission;
			cout << endl;
		}
	}

public:

	static void _ShowListUserScreen()
	{
		vector <clsBankUsers> vusers = clsBankUsers::GetUsersList();
		string Titel = "\t      User List Screen";
		string SubTitel = "\t        (" + to_string(vusers.size()) + ") User(s).";
		_DrawScreenHeader(Titel, SubTitel);
		cout << left << setw(10) << "" << "_____________________________________________________________________________________________________\n\n";
		cout << left << setw(10) << "" << "| " << setw(10) << "User Name";
		cout << left << setw(20) << "| Full Name";
		cout << left << setw(20) << "| Phone";
		cout << left << setw(22) << "| Email";
		cout << left << setw(15) << "| Password";
		cout << left << setw(13) << "| Permission\n";
		cout << left << setw(10) << "" << "_____________________________________________________________________________________________________\n\n";
		if (vusers.size() == 0)
		{
			cout << "There are no users on the system!\n";
		}
		else
		{
			_FillUsersInfoInList(vusers);
		}
		cout << left << setw(10) << "" << "_____________________________________________________________________________________________________\n\n";
	}
};

