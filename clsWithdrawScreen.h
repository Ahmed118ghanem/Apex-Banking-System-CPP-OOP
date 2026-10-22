#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsBankClient.h"
#include <iomanip>
class clsWithdrawScreen : clsScreen
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

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t      Withdraw Screen");
		cout << "Enter Account Number : ";
		string accountnumber = clsinputvalidation::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nClient by account number [" << accountnumber << "] not available! , Enter another one : ";
			accountnumber = clsinputvalidation::ReadString();
		}
		clsBankClient client = clsBankClient::Find(accountnumber);
		_PrintClientCard(client);
		cout << "\nEnter Withdraw Amount? ";
		double amount = clsinputvalidation::ReadDBLNumber("Wrong Value , Enter another one : ");
		while (amount > client.AccountBalance || amount<=0)
		{
			cout << "\nAmount Exceeds Balance , you can withdraw from 1 up to : " << client.AccountBalance << endl;
			cout << "\nEnter another Amount? ";
			amount = clsinputvalidation::ReadDBLNumber("Wrong Value , Enter another one : ");
		}
		string answer;
		cout << "\nAre you sure you want to Perform this transaction? [Yes OR No]? ";
		answer = clsinputvalidation::ReadString();

		if (answer == "YES" || answer == "yes")
		{
			client.WithDraw(amount);
			cout << "\nDone Successfully , New Balance is : " << client.AccountBalance << endl;
		}
		else
		{
			cout << "\nThe Operation was Cancelled." << endl;
		}

	}

};

