#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsinputvalidation.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
private:

	static void _ReadClientData(clsBankClient& client)
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
		cout << "Password        : " << client.PinCode << endl;
		cout << "Account Balance : " << client.AccountBalance << endl;
		cout << "________________________________________________\n";
	}

public:

	static void ShowAddNewClientScreen()
	{
		if (!_CheckAccessRight(clsBankUsers::enPermission::eAddClient))
		{
			return; //it will exit the function and it will not continue.
		}
		_DrawScreenHeader("\t    Add New Client Screen");
		cout << "\nEnter Account Number? ";
		string accountnumber = clsinputvalidation::ReadString();
		while (clsBankClient::IsClientExist(accountnumber))
		{
			cout << "Client By account number [" << accountnumber << "] is already exist , enter another one: ";
			accountnumber = clsinputvalidation::ReadString();
		}
		clsBankClient client = clsBankClient::GetAddNewClientObject(accountnumber);
		_ReadClientData(client);
		clsBankClient::ensave save = client.Save();
		switch (save)
		{
		case clsBankClient::ensave::Ssuccessed:
			cout << "\nClient Added Successfully.\n";
			_PrintClientCard(client);
			break;
		case clsBankClient::ensave::Sfaildempty:
			cout << "The operation was failed!\n";
			break;
		}
	}

};

