#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsperson.h"
#include "clsstring.h"
#include "clsDate.h"
#include "clsGlobal.h"
using namespace std;

class clsBankClient : public clsperson
{
private:

	enum enMode { EmptyMode = 1, UpdateMode = 2 , AddMode = 3};
	string _Accountnumber;
	string _pincode;
	double _accountbalance;
	enMode _Mode;
	bool _MarkForDeleted = false;

	static clsBankClient _ConvertLineRecordToClientObject(string line , string separator = "#//#")
	{
		vector <string> vObjectMember = clsstring::Split(line, separator);
		return clsBankClient(enMode::UpdateMode, vObjectMember[0], vObjectMember[1], vObjectMember[2], vObjectMember[3],
			vObjectMember[4], vObjectMember[5], stod(vObjectMember[6]));
	}
	
	static vector <clsBankClient> _LoadDataFromClientsFile()
	{
		vector <clsBankClient> VClients;
		fstream myfile;
		myfile.open("ClientsFile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsBankClient client = _ConvertLineRecordToClientObject(line);
				VClients.push_back(client);
			}
			myfile.close();
		}
		return VClients;
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertClientObjectToLine(clsBankClient client , string separator)
	{
		string line;
		line += client.FirstName + separator;
		line += client.LastName + separator;
		line += client.Email + separator;
		line += client.Phone + separator;
		line += client.AccountNumber + separator;
		line += client.PinCode + separator;
		line += to_string(client.AccountBalance);
		return line;
	}

	void _SaveClientsDataToFile(vector <clsBankClient> vclient)
	{
		fstream myfile;
		myfile.open("ClientsFile.txt", ios::out);
		if(myfile.is_open())
		{
			for (clsBankClient c : vclient)
			{
				if (!c._MarkForDeleted)
				{
					string line = _ConvertClientObjectToLine(c, "#//#");
					myfile << line << endl;
				}
			}
			myfile.close();
		}
		
	}

	void _UpdateClient()
	{
		vector <clsBankClient> vclient = _LoadDataFromClientsFile();
		for (clsBankClient& c : vclient)
		{
			if (c.AccountNumber == this->AccountNumber)
			{
				c = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vclient);
	}

	void _AddClient()
	{
		fstream myfile;
		myfile.open("ClientsFile.txt", ios::out | ios::app);
		if(myfile.is_open())
		{
			myfile << _ConvertClientObjectToLine(*this, "#//#") << endl;
		}
		myfile.close();
	}

	struct stTransferLog;

	string PrepareTransferLogLine(double amount, clsBankClient DestinationClient , string separator = "#//#")
	{
		string line;
		line +=clsdate::GetDateAndTimeLine(clsdate()) + separator;
		line += this->AccountNumber+separator;
		line += DestinationClient.AccountNumber+separator;
		line += to_string(amount)+separator;
		line += to_string(this->AccountBalance)+separator;
		line += to_string(DestinationClient.AccountBalance)+separator;
		line += CurrentUser.UserName;
		return line;
	}

	void _AddRegisterTransferToFile(double amount, clsBankClient DestinationClient)
	{
		string line = PrepareTransferLogLine(amount, DestinationClient);
		fstream myfile;
		myfile.open("TransferLog.txt", ios::out | ios::app);
		if (myfile.is_open())
		{
			myfile << line << endl;
			myfile.close();
		}
	}

	static stTransferLog _ConvertLineFromTransferFileToRecord(string line , string separator = "#//#")
	{
		vector <string> vRecord = clsstring::Split(line, separator);
		stTransferLog TransferLog;
		TransferLog.Date_Time = vRecord[0];
		TransferLog.SourceAccount = vRecord[1];
		TransferLog.DestinationAccount = vRecord[2];
		TransferLog.amount = stoi(vRecord[3]);
		TransferLog.SBalance = stoi(vRecord[4]);
		TransferLog.DBalance = stoi(vRecord[5]);
		TransferLog.UserName = vRecord[6];
		return TransferLog;
	}

public:

	clsBankClient(enMode mode,string firstname, string lastname, string email, string phone, string accountnumber,
		string pincode, double accountbalance) :
		clsperson(firstname, lastname, email, phone)
	{
		_Accountnumber = accountnumber;
		_pincode = pincode;
		_accountbalance = accountbalance;
		_Mode = mode;
	}

	struct stTransferLog
	{
		string Date_Time;
		string SourceAccount;
		string DestinationAccount;
		double amount;
		double SBalance;
		double DBalance;
		string UserName;
	};

	bool IsEmptyMode()
	{
		return _Mode == enMode::EmptyMode;
	}

	string GetAccountNumber()
	{
		return _Accountnumber;
	}

	_declspec(property(get = GetAccountNumber)) string AccountNumber;

	void SetPinCode(string PinCode)
	{
		_pincode = PinCode;
	}

	string GetPinCode()
	{
		return _pincode;
	}

	_declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_accountbalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _accountbalance;
	}

	_declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	static clsBankClient Find(string accountnumber)
	{
		vector <clsBankClient> vClients = _LoadDataFromClientsFile();
		for (clsBankClient c : vClients)
		{
			if (c.AccountNumber == accountnumber)
			{
				return c;
			}
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string accountnumber , string pincode)
	{
		vector <clsBankClient> vClients = _LoadDataFromClientsFile();
		for (clsBankClient c : vClients)
		{
			if (c.AccountNumber == accountnumber && c.PinCode==pincode)
			{
				return c;
			}
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string accountnumber)
	{
		clsBankClient client = clsBankClient::Find(accountnumber);
		return !client.IsEmptyMode();
	}

	static clsBankClient GetAddNewClientObject(string accountnumber)
	{
		return clsBankClient(enMode::AddMode, "", "", "", "", accountnumber, "", 0);
	}

	enum ensave{Sfaildempty = 1 , Ssuccessed = 2};

	ensave Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return ensave::Sfaildempty;
		case enMode::UpdateMode:
			_UpdateClient();
			return ensave::Ssuccessed;
		case enMode::AddMode:
			_AddClient();
			_Mode = enMode::UpdateMode;
			return ensave::Ssuccessed;
		}
	}

	bool DeleteClient()
	{
		vector <clsBankClient> VClients = _LoadDataFromClientsFile();
		for (clsBankClient &v : VClients)
		{
			if (v.AccountNumber == this->AccountNumber)
			{
				v._MarkForDeleted = true;
				break;
			}
		}
		_SaveClientsDataToFile(VClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadDataFromClientsFile();
	}

    void Deposit(double amount)
	{
		AccountBalance += amount;
		Save();
	}

	void WithDraw(double amount)
	{
		AccountBalance -= amount;
		Save();
	}

	static double GetTotalBalances()
	{
		double Total = 0;
		vector <clsBankClient> vclients = _LoadDataFromClientsFile();
		for (clsBankClient& c : vclients)
		{
			Total += c.AccountBalance;
		}
		return Total;
	}

	bool TransferTo(double amount, clsBankClient &DestinationClient)
	{
		if (this->AccountBalance < amount || amount <= 0)
			return false;
		if (this->AccountNumber == DestinationClient.AccountNumber)
			return false;
		this->WithDraw(amount);
		DestinationClient.Deposit(amount);
		this->_AddRegisterTransferToFile(amount, DestinationClient);
		return true;
	}

	static vector <stTransferLog> LoadDataFromTransferLogFile()
	{
		vector <stTransferLog> vTransferLog;
		fstream myfile;
		myfile.open("TransferLog.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				stTransferLog TransferLog = _ConvertLineFromTransferFileToRecord(line);
				vTransferLog.push_back(TransferLog);
			}
			myfile.close();
		}
		return vTransferLog;
	}

};

