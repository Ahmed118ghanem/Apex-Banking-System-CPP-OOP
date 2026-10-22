#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsBankClient.h"

class clsTransferScreen : protected clsScreen
{

	static void _PrintClientCard(clsBankClient client)
	{
		cout << "\n________________________________________________\n";
		cout << "\t\tClient Card " << endl;
		cout << "________________________________________________\n";
		cout << "FullName        : " << client.FullName << endl;
		cout << "Account Number  : " << client.AccountNumber << endl;
		cout << fixed << setprecision(0);
		cout << "Account Balance : " << client.AccountBalance << endl;
		cout << "________________________________________________\n";
	}

	static string _ReadAccountNumber()
	{
		string accountnumber = clsinputvalidation::ReadString();
		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nAccount number by [" << accountnumber << "] does not exist on the system , Enter another one: ";
			accountnumber = clsinputvalidation::ReadString();
		}
		return accountnumber;
	}

	static double _ReadAmount(clsBankClient SourceClient)
	{
		double amount;
		cout << "\nEnter Transfer Amount : ";
		amount = clsinputvalidation::ReadDBLNumber("\nWrong Value , Enter another amount : ");
		while (SourceClient.AccountBalance < amount || amount <= 0)
		{
			cout << "\nAmount exceeds balance , you can transfer from 1 up to " << SourceClient.AccountBalance;
			cout << "\nEnter another amount : ";
			amount = clsinputvalidation::ReadDBLNumber("\nWrong Value , Enter another amount : ");
		}
		return amount;
	}

public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t     Transfer Screen");

		cout << "\nPlease Enter Account Number to transfer from : ";
		string sourceAcc = _ReadAccountNumber();
		clsBankClient SourceClient = clsBankClient::Find(sourceAcc);
		_PrintClientCard(SourceClient);
		if (SourceClient.AccountBalance == 0)
		{
			cout << "\nWe are sorry , There are no funds in this account to transfer." << endl;
			return;
		}
		
		cout << "\nPlease Enter Account Number to transfer to : ";
		string DestinationAcc = _ReadAccountNumber();
		while (DestinationAcc == sourceAcc)
		{
			cout << "\nYou can not transfer to the same account number , Please enter another one : ";
			DestinationAcc = _ReadAccountNumber();
		}
        
		clsBankClient DestinationClient = clsBankClient::Find(DestinationAcc);
		_PrintClientCard(DestinationClient);

		double amount = _ReadAmount(SourceClient);

		string answer;
		cout << "\nAre you sure you want to Perform this transaction? [Yes OR No]? ";
		answer = clsinputvalidation::ReadString();

		if (answer == "YES" || answer == "yes")
		{
			if (SourceClient.TransferTo(amount, DestinationClient))
			{
				cout << "\nTransfer Done Successfully.\n";
				_PrintClientCard(SourceClient);
				_PrintClientCard(DestinationClient);
			}
			else
			{
				cout << "\nFailed Transfer\n";
			}
		}
		else
		{
			cout << "\nThe operation was cancelled.\n";
		}
		
	}
};

