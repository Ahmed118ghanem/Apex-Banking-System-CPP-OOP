#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsGlobal.h"
#include <iomanip>
class clsTransferLogScreen : protected clsScreen
{
private:

	static void _FillDataFromTransferLogFile(vector <clsBankClient::stTransferLog> vtransferlog)
	{
		for (clsBankClient::stTransferLog v : vtransferlog)
		{
			cout << setw(12) << right << "| " << setw(22) << left << v.Date_Time;
			cout << "| " << setw(11) << left << v.SourceAccount;
			cout << "| " << setw(11) << left << v.DestinationAccount;
			cout << fixed << setprecision(0);
			cout << "| " << setw(11) << left << v.amount;
			cout << "| " << setw(14) << left << v.SBalance;
			cout << "| " << setw(14) << left << v.DBalance;
			cout << "| " << setw(11) << left << v.UserName;
			cout << endl;
		}
	}

public:

	static void ShowTransferLogScreen()
	{
		vector <clsBankClient::stTransferLog> vtransferlog = clsBankClient::LoadDataFromTransferLogFile();
		string Titel = "\t Transfer Log List Screen";
		string SubTitel = "\t      (" + to_string(vtransferlog.size()) + ") Record(s).";
		_DrawScreenHeader(Titel, SubTitel);

		cout << left << setw(10) << "" << "_________________________________________________________________________________________________________\n\n";
		cout << left << setw(10) << "" << setw(19) << left << "| Date/Time";
		cout << left << setw(5) << "" << "| S.Acct";
		cout << left << setw(5) << "" << "| D.Acct";
		cout << left << setw(5) << "" << "| Amount";
		cout << left << setw(5) << "" << "| S.Balance";
		cout << left << setw(5) << "" << "| D.Balance";
		cout << left << setw(5) << "" << "| UserName\n";
		cout << left << setw(10) << "" << "_________________________________________________________________________________________________________\n\n";
		if (vtransferlog.size() == 0)
		{
			cout << left << setw(40) << "" << "There are no Transfer Log on the system!\n";
		}
		else
		{
			_FillDataFromTransferLogFile(vtransferlog);
		}
		cout << left << setw(10) << "" << "_________________________________________________________________________________________________________\n";

	}

};



