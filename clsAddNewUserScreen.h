#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUsers.h"
#include "clsinputvalidation.h"
class clsAddNewUserScreen : protected clsScreen
{

private:

	static void _ReadUserInfo(clsBankUsers &user)
	{
		cout << "\nEnter First Name : ";
		user.FirstName = clsinputvalidation::ReadString();
		cout << "Enter Last Name  : ";
		user.LastName = clsinputvalidation::ReadString();
		cout << "Enter Email      : ";
		user.Email = clsinputvalidation::ReadString();
		cout << "Enter Phone      : ";
		user.Phone = clsinputvalidation::ReadString();
		cout << "Enter Password   : ";
		user.Password = clsinputvalidation::ReadString();
		user.Permission = _ReadPermission();
	}

	static short _ReadPermission()
	{
		short permission = 0;
		string answer;
		cout << "\nDo you want to give full access? [Yes OR No]? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			return permission = clsBankUsers::enPermission::eAll;
		}

		cout << "\nDo you want to give access to: \n";

		cout << "\nShow Client List? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eListScreen;
		}

		cout << "\nAdd New Client? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eAddClient;
		}

		cout << "\nDelete Client? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eDelete;
		}

		cout << "\nUpdate Client? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eUpdate;
		}

		cout << "\nFind Client? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eFindClient;
		}

		cout << "\nTransaction? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eTransaction;
		}

		cout << "\nManage Users? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eManageUser;
		}
		cout << "\nLogin Register List Screen? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eLogRegister;
		}
		cout << "\nCurrency Exchange? [Yes OR No] ? ";
		answer = clsinputvalidation::ReadString();
		if (answer == "yes" || answer == "YES")
		{
			permission += clsBankUsers::enPermission::eCurrencyExchange;
		}
		return permission;
	}

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

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t    Add New User Screen");
		cout << "\nEnter User Name? ";
		string username = clsinputvalidation::ReadString();
		while (clsBankUsers::IsUserExist(username))
		{
			cout << "\nUser by User Name [" << username << "] is already exist , Enter another one: ";
			username = clsinputvalidation::ReadString();
		}

		clsBankUsers user = clsBankUsers::GetAddNewUserObject(username);
		_ReadUserInfo(user);
		clsBankUsers::ensave Save = user.Save();
		switch (Save)
		{
		case clsBankUsers::ensave::Ssuccessed:
			cout << "\nUser Added Successfully.\n";
			_PrintUserCard(user);
			break;
		case clsBankUsers::ensave::SEmpty:
			cout << "\nError Account was not saved because it's empty" << endl;
		}

	}

};

