#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include <iomanip>
class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eDelete))
		{
			return; //it will exit the function and it will not continue.
		}
		_DrawScreenHeader("\t    Delete Client Screen");
		cout << "\nEnter Account number? ";
		string accountnumber = clsinputvalidation::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nClient by Account Number [" << accountnumber << "] not available! , Enter another one: ";
			accountnumber = clsinputvalidation::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(accountnumber);
		_PrintClientCard(Client);
		string Answer;
		cout << "\nAre you sure you want to delete this client? [Yes OR No]? ";
		Answer = clsinputvalidation::ReadString();
		if (Answer == "YES" || Answer == "yes")
		{
			Client.DeleteClient();
			cout << "\nClient Deleted Successfully." << endl;
			_PrintClientCard(Client);
		}
		else
		{
			cout << "\nThe operation was Cancelled.\n";
		}
	}

};

