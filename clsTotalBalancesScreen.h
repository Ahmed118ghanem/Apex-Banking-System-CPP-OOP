#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsinputvalidation.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsutil.h"
class clsTotalBalancesScreen : protected clsScreen
{

private:

	static void _PrintClientRecordBalanceLine(clsBankClient client)
	{
		cout << "\t\t   | " << left << setw(31) << client.AccountNumber;
		cout << "| " << setw(28) << left << client.FullName;
		cout << "| " << setw(17) << left << client.AccountBalance;
	}

public:

	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClient> vclient = clsBankClient::GetClientsList();

		string Title = "\t   Balances List Screen";
		string SubTitle = "\t     (" + to_string(vclient.size()) + ") Client(s).";
		_DrawScreenHeader(Title, SubTitle);

		cout << left << setw(19) << "" << "________________________________________________________________________________\n\n";
		cout << left << setw(17) << "" << "  | Account number";
		cout << left << setw(17) << "" << "| Client Name";
		cout << left << setw(17) << "" << "| Balance\n";
		cout << left << setw(19) << "" << "________________________________________________________________________________\n\n";
		if (vclient.size() == 0)
		{
			cout << "\t\t\t\tNo Client available in system!" << endl;
		}
		else
		{
			for (clsBankClient& c : vclient)
			{
				_PrintClientRecordBalanceLine(c);
				cout << "\n";
			}
		}
		cout << left << setw(19) << "" << "________________________________________________________________________________\n";

		double TotalBalances = clsBankClient::GetTotalBalances();
		cout << "\n\t\t\t\t\t\tTotal Balances = " << TotalBalances << endl;
		cout << "\t\t\t\t\t     (" << clsutil::NumberToText(TotalBalances) << ")" << endl;
	}

};

