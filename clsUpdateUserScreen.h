#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankUsers.h"
#include "clsinputvalidation.h"

class clsUpdateUserScreen : protected clsScreen
{
private:

	static void _ReadNewInfoAboutUser(clsBankUsers &ModifiedUser)
	{
		cout << "\nEnter First Name: ";
		ModifiedUser.FirstName = clsinputvalidation::ReadString();
		cout << "\nEnter Last Name: ";
		ModifiedUser.LastName = clsinputvalidation::ReadString();
		cout << "\nEnter Email: ";
		ModifiedUser.Email = clsinputvalidation::ReadString();
		cout << "\nEnter Phone: ";
		ModifiedUser.Phone = clsinputvalidation::ReadString();
		cout << "\nEnter Password: ";
		ModifiedUser.Password = clsinputvalidation::ReadString();
		if (ModifiedUser.UserName != "Admin")
		{
			ModifiedUser.Permission = _ReadPermission();
		}
		
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

	static void _ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\t    Update User Screen");
		cout << "\nEnter User Name: ";
		string username = clsinputvalidation::ReadString();
		while (!clsBankUsers::IsUserExist(username))
		{
			cout << "\nThis user does not exist on the system , Enter another one : ";
			username = clsinputvalidation::ReadString();
		}
		clsBankUsers ModifiedUser = clsBankUsers::Find(username);
		if (username == "Admin"&&CurrentUser.UserName!="Admin")
		{
			cout << "\nThis user can only be updated by him.\n";
		}
		else
		{
			_PrintUserCard(ModifiedUser);
			string answer = "";
			cout << "\nAre you sure you want to update this User? [Yes OR No]? ";
			answer = clsinputvalidation::ReadString();
			if (answer == "yes" || answer == "YES")
			{
				_ReadNewInfoAboutUser(ModifiedUser);
				clsBankUsers::ensave save;
				save = ModifiedUser.Save();
				switch (save)
				{
				case clsBankUsers::ensave::Ssuccessed:
					cout << "\nUser updated successfully\n";
					_PrintUserCard(ModifiedUser);
					break;
				case clsBankUsers::ensave::SEmpty:
					cout << "\nError Account was not saved because it's empty" << endl;
				}
			}
			else
			{
				cout <<"\nThe operation was cancelled.\n";
			}
		}
	}

};

