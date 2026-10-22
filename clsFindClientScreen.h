#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsBankClient.h"
#include <iomanip>
class clsFindClientScreen : protected clsScreen
{
private:

	static void _PrintClientCard(clsBankClient client)
	{
		cout << "\n________________________________________________\n";
		cout << "\t\tClient Card " << endl;
		cout << "________________________________________________\n";
		cout << "First Name      : " << client.FirstName << endl;
		cout << "Last Name       : " << client.LastName << endl;
		cout << "FullName        : " << client.FullName << endl;
		cout << "Email           : " << client.Email << endl;
		cout << "Phone           : " << client.Phone << endl;
		cout << "Account Number  : " << client.AccountNumber << endl;
		cout << fixed << setprecision(0);
		cout << "Password        : " << client.PinCode << endl;
		cout << "Account Balance : " << client.AccountBalance << endl;
		cout << "________________________________________________\n";
	}

public:

	static void ShowFindClientScreen()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eFindClient))
		{
			return; //it will exit the function and it will not continue.
		}
		_DrawScreenHeader("\t    Find Client Screen");
		cout << "\nEnter Account Number : ";
		string accountnumber = clsinputvalidation::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nClient by account number [" << accountnumber << "] not available! , Enter another one : ";
			accountnumber = clsinputvalidation::ReadString();
		}
		clsBankClient client = clsBankClient::Find(accountnumber);

		if (!client.IsEmptyMode())
		{
			cout << "\nClient Found.\n";
			_PrintClientCard(client);
		}
		else
		{
			cout << "\nClient was not Found.\n";
		}

	}

};

