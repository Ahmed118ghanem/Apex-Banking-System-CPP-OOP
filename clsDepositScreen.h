#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsBankClient.h"
#include <iomanip>
class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t      Deposit Screen");
		cout << "Enter Account Number : ";
		string accountnumber = clsinputvalidation::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nClient by account number [" << accountnumber << "] not available! , Enter another one : ";
			accountnumber = clsinputvalidation::ReadString();
		}
		clsBankClient client = clsBankClient::Find(accountnumber);
		_PrintClientCard(client);
		cout << "\nEnter Deposit Amount? ";
		double amount = clsinputvalidation::ReadDBLNumber("Wrong Value , Enter another one : ");
		string answer;
		cout << "\nAre you sure you want to Perform this transaction? [Yes OR No]? ";
		answer = clsinputvalidation::ReadString();

		if (answer == "YES" || answer == "yes")
		{
			client.Deposit(amount);
			cout << "\nDone Successfully , New Balance is : " << client.AccountBalance << endl;
		}
		else
		{
			cout << "\nThe Operation was Cancelled." << endl;
		}

	}

};

