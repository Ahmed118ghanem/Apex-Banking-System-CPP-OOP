#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"

class clsClientsListScreen : protected clsScreen
{
private:

	static void FillClientsDataInTheTable(vector <clsBankClient> vclient)
	{
		for (clsBankClient c : vclient)
		{
			cout << setw(9) << right << "| " << left << setw(18) << c.AccountNumber;
			cout << "| " << left << setw(18) << c.FullName;
			cout << "| " << left << setw(15) << c.Phone;
			cout << "| " << left << setw(19) << c.Email;
			cout << fixed << setprecision(0);
			cout << "| " << left << setw(12) << c.PinCode;
			cout << "| " << left << setw(15) << c.AccountBalance;
			cout << "\n";
		}
	}

public:

	static void ShowClientListScreen()
	{
		if(!_CheckAccessRight(clsBankUsers::enPermission::eListScreen))
		{
			return; //it will exit the function and it will not continue.
		}
		vector <clsBankClient> vclients = clsBankClient::GetClientsList();
		string Titel = "\t     Client List Screen";
		string SubTitel = "\t       (" + to_string(vclients.size()) + ") Client(s).";
		_DrawScreenHeader(Titel, SubTitel);
		cout << setw(7) << left << "" << "_____________________________________________________________________________________________________________\n\n";
		cout << setw(9) << right << "| " << setw(18) << left << "Account Number";
		cout << setw(20) << left << "| Full Name";
		cout << setw(17) << left << "| Phone";
		cout << setw(21) << left << "| Email";
		cout << setw(14) << left << "| Password";
		cout << setw(20) << left << "| Account Balance\n";
		cout << setw(5) << left << "" << "_____________________________________________________________________________________________________________\n\n";
		if (vclients.size() == 0)
		{
			cout << "\t\t\tThere are no clients on the system\n";
		}
		else
		{
			FillClientsDataInTheTable(vclients);
		}
		cout << setw(7) << left << "" << "_____________________________________________________________________________________________________________\n";
	}
};

