#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsBankClient.h"
#include <iomanip>
class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& client)
	{
		cout << "Enter First Name: ";
		client.FirstName = clsinputvalidation::ReadString();
		cout << "Enter Last Name: ";
		client.LastName = clsinputvalidation::ReadString();
		cout << "Enter Email: ";
		client.Email = clsinputvalidation::ReadString();
		cout << "Enter Phone: ";
		client.Phone = clsinputvalidation::ReadString();
		cout << "Enter Password: ";
		client.PinCode = clsinputvalidation::ReadString();
		cout << "Enter Account Balance: ";
		client.AccountBalance = clsinputvalidation::ReadDBLNumber("Wrong Account Balance , Enter another one: ");
	}

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

	static void ShowUpdateClientScreen()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eUpdate))
		{
			return; //it will exit the function and it will not continue.
		}
		_DrawScreenHeader("\t   Update Client Screen");
		cout << "\nEnter Account Number? ";
		string accountnumber = clsinputvalidation::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nClient by account number [" << accountnumber << "] not available! , Enter another one : ";
			accountnumber = clsinputvalidation::ReadString();
		}
		clsBankClient client = clsBankClient::Find(accountnumber);
		_PrintClientCard(client);
		string answer = "";
		cout << "\nAre you sure you want to update this client? [Yes OR No]? ";
		answer = clsinputvalidation::ReadString();

		if (answer == "YES" || answer == "yes")
		{
			clsBankClient::ensave saveinfo;
			_ReadClientInfo(client);
			saveinfo = client.Save();
			switch (saveinfo)
			{
			case clsBankClient::ensave::Ssuccessed:
				cout << "\nClient Updated Successfully. \n";
				_PrintClientCard(client);
				break;
			case clsBankClient::ensave::Sfaildempty:
				cout << "\nError Account was not saved because it's empty" << endl;
			}
		}
		else
		{
			cout << "\nThe Operation was Cancelled." << endl;
		}

	}

};

