#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUsers.h"
#include "clsinputvalidation.h"
class clsFindUserScreen : protected clsScreen
{
private:

	static void _PrintUserCard(clsBankUsers user)
	{
		cout << "\n________________________________________________\n";
		cout << "\t\t  User Card " << endl;
		cout << "________________________________________________\n";
		cout << "First Name        : " << user.FirstName << endl;
		cout << "Last Name         : " << user.LastName << endl;
		cout << "Email             : " << user.Email << endl;
		cout << "Phone             : " << user.Phone << endl;
		cout << "User Name         : " << user.UserName << endl;
		cout << "Password          : " << user.Password << endl;
		cout << "Permission        : " << user.Permission << endl;
		cout << "________________________________________________\n";
	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t    Find User Screen");
		cout << "\nEnter User Name: ";
		string username = clsinputvalidation::ReadString();
		while (!clsBankUsers::IsUserExist(username))
		{
			cout << "\nThis user does not exist on the system , Enter another one : ";
			username = clsinputvalidation::ReadString();
		}
		clsBankUsers ModifiedUser = clsBankUsers::Find(username);
		_PrintUserCard(ModifiedUser);
	}

};
