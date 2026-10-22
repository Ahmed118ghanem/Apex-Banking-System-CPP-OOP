#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsScreen.h"
#include "clsstring.h"
#include "clsBankUsers.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _FillUsersLoginRegisterInList(vector <clsBankUsers::stLogRegister> vlog)
	{
		for (clsBankUsers::stLogRegister log : vlog)
		{
			cout << setw(12) << right << "| " << setw(45) << left << log.Date_Time;
			cout << "| " << setw(19) << left << log.Username;
			cout << "| " << setw(18) << left << log.Password;
			cout << "| " << setw(10) << left << log.Permission;
			cout << endl;

		}
	}

public:


	static void ShowLoginRegisterListScreen()
	{
		if(!_CheckAccessRight(clsBankUsers::enPermission::eLogRegister))
		{
			return; //it will exit the function and it will not continue.
		}
		vector <clsBankUsers::stLogRegister> vlog = clsBankUsers::GetLoginRegisterList();
		string Titel = "\tLogin Register List Screen";
		string SubTitel = "\t      (" + to_string(vlog.size()) + ") Record(s).";
		_DrawScreenHeader(Titel, SubTitel);
		cout << left << setw(10) << "" << "_____________________________________________________________________________________________________\n\n";
		cout << left << setw(10) << "" << "| " << setw(30) << "Date/Time";
		cout << left << setw(15) << "" << "| User Name";
		cout << left << setw(10) << "" << "| Password";
		cout << left << setw(10) << "" << "| Permission\n";
		cout << left << setw(10) << "" << "_____________________________________________________________________________________________________\n\n";
		if (vlog.size() == 0)
		{
			cout << left << setw(40) << "" << "There are no users Login on the system!\n";
		}
		else
		{
			_FillUsersLoginRegisterInList(vlog);
		}
		cout << left << setw(10) << "" << "_____________________________________________________________________________________________________\n\n";
	}

};


