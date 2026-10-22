#pragma once
#include <iostream>
#include <string> 
#include <vector>
#include <fstream>
#include "clsperson.h"
#include "clsstring.h"
#include "clsDate.h"
#include "clsutil.h"
using namespace std;

class clsBankUsers : public clsperson
{
private:

	enum enMode{eEmptyMode = 1 , eUpdateMode = 2 , eAddMode = 3};
	enMode _Mode;
	string _UserName;
	string _Password;
	short _Permission;
	bool _MarkForDeleted = false;

	static clsBankUsers _ConvertLineFromUsersFileToUserObject(string line , string separator)
	{
		vector <string> vLine = clsstring::Split(line, separator);
		return clsBankUsers(enMode::eUpdateMode, vLine[0], vLine[1], vLine[2], vLine[3], vLine[4],
			                clsutil::DecryptText(vLine[5],4) , stoi(vLine[6]) );
	}

	static vector <clsBankUsers> _LoadDataFromUsersFile()
	{
		vector <clsBankUsers> VUsers;
		fstream myfile;
		myfile.open("UsersFile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsBankUsers user = _ConvertLineFromUsersFileToUserObject(line, "#//#");
				VUsers.push_back(user);
			}
			myfile.close();
		}
		return VUsers;
	}

	static clsBankUsers _GetUserEmptyObject()
	{
		return clsBankUsers(enMode::eEmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ConvertUserObjectToLine(clsBankUsers user, string separator = "#//#")
	{
		string line;
		line += user.FirstName + separator;
		line += user.LastName + separator;
		line += user.Email + separator;
		line += user.Phone + separator;
		line += user.UserName + separator;
		line += clsutil::EncryptText(user.Password,4) + separator;
		line += to_string(user.Permission);
		return line;
	}

	static void _SaveDataToUserFile(vector <clsBankUsers> Vusers)
	{
		fstream myfile;
		myfile.open("UsersFile.txt", ios::out);
		if (myfile.is_open())
		{
			for (clsBankUsers user : Vusers)
			{
				if (!user._MarkForDeleted)
				{
					string line = _ConvertUserObjectToLine(user, "#//#");
					myfile << line << endl;
				}
			}
			myfile.close();
		}
	}

	void _UpdateUser()
	{
		vector <clsBankUsers> Vusers = _LoadDataFromUsersFile();
		for (clsBankUsers &user : Vusers)
		{
			if (user.UserName == this->UserName)
			{
				user = *this;
				break;
			}
		}
		_SaveDataToUserFile(Vusers);
	}

	void _AddUser()
	{
		fstream myfile;
		myfile.open("UsersFile.txt", ios::out | ios::app);
		if (myfile.is_open())
		{
			
			myfile << _ConvertUserObjectToLine(*this) << endl;
			myfile.close();
		}
	}

	string _PrepareLoginRecord(string separator)
	{
		string line;
		line += clsdate::GetDateAndTimeLine(clsdate())+separator;
		line += UserName + separator;
		line += clsutil::EncryptText(Password,4) + separator;
		line += to_string(Permission);
		return line;
	}

	struct stLogRegister;

	static stLogRegister _ConvertLineToRegisterRecord(string line)
	{
		vector <string> vRegister = clsstring::Split(line, "#//#");
		stLogRegister LogRegister;
		LogRegister.Date_Time = vRegister[0];
		LogRegister.Username = vRegister[1];
		LogRegister.Password = clsutil::DecryptText(vRegister[2],4);
		LogRegister.Permission = stoi(vRegister[3]);
		return LogRegister;
	}


public:

	enum enPermission {eAll = -1, eListScreen = 1, eAddClient = 2, eDelete = 4, eUpdate = 8,
		               eFindClient = 16, eTransaction = 32, eManageUser = 64 , eLogRegister = 128,
		               eCurrencyExchange = 256};

	struct stLogRegister
	{
		string Date_Time;
		string Username;
		string Password;
		short Permission;
	};

	clsBankUsers(enMode mode,string firstname, string lastname, string email, string phone, string username,
		string Password, short permission):
		clsperson(firstname,lastname,email,phone)
	{
		_Mode = mode;
		_UserName = username;
		_Password = Password;
		_Permission = permission;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::eEmptyMode;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermission(short Permission)
	{
		_Permission = Permission;
	}

	short GetPermission()
	{
		return _Permission;
	}

	__declspec(property(get = GetPermission, put = SetPermission)) short Permission;

	static clsBankUsers Find(string username)
	{
		fstream myfile;
		myfile.open("usersfile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsBankUsers user = _ConvertLineFromUsersFileToUserObject(line,"#//#");
				if (user.UserName == username)
				{
					myfile.close();
					return user;
				}
			}
			myfile.close();
		}
		return _GetUserEmptyObject();
	}

	static clsBankUsers Find(string username , string password)
	{
		fstream myfile;
		myfile.open("usersfile.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				clsBankUsers user = _ConvertLineFromUsersFileToUserObject(line,"#//#");
				if (user.UserName == username&&user.Password==password)
				{
					myfile.close();
					return user;
				}
			}
			myfile.close();
		}
		return _GetUserEmptyObject();
	}

	static clsBankUsers GetAddNewUserObject(string username)
	{
		return clsBankUsers(enMode::eAddMode, "", "", "", "", username, "", 0);
	}

	static bool IsUserExist(string username)
	{
		clsBankUsers user = clsBankUsers::Find(username);
		return !user.IsEmpty();
	}

	enum ensave {Ssuccessed = 1 , SEmpty};

	ensave Save()
	{
		switch (_Mode)
		{
		case enMode::eEmptyMode:
			return ensave::SEmpty;
		case enMode::eUpdateMode:
			_UpdateUser();
			return ensave::Ssuccessed;
		case enMode::eAddMode:
			_AddUser();
			_Mode = enMode::eUpdateMode;
			return ensave::Ssuccessed;
		}

	}

	bool Delete()
	{
		vector <clsBankUsers> vusers = _LoadDataFromUsersFile();
		for (clsBankUsers &user : vusers)
		{
			if (user.UserName == this->UserName)
			{
				user._MarkForDeleted = true;
				break;
			}
		}
		_SaveDataToUserFile(vusers);
		*this = _GetUserEmptyObject();
		return true;
	}

	static vector <clsBankUsers> GetUsersList()
	{
		return _LoadDataFromUsersFile();
	}

	bool CheckUsersPermission(enPermission permission)
	{
		if (this->Permission == -1)
			return true;
		if ((this->Permission & permission) == permission)
			return true;
		return false;
	}

	void AddLoginRegisterToFile()
	{
		string line = _PrepareLoginRecord("#//#");
		fstream myfile;
		myfile.open("LoginRegister.txt", ios::app | ios::out);
		if (myfile.is_open())
		{
			myfile << line << endl;
			myfile.close();
		}
	}

	static vector <stLogRegister> GetLoginRegisterList()
	{
		vector <stLogRegister> vRegister;
		fstream myfile;
		myfile.open("LoginRegister.txt", ios::in);
		if (myfile.is_open())
		{
			string line;
			while (getline(myfile, line))
			{
				stLogRegister LogRegister = _ConvertLineToRegisterRecord(line);
				vRegister.push_back(LogRegister);
			}
			myfile.close();
		}
		return vRegister;
	}


};

