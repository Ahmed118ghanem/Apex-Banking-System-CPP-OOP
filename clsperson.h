#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsperson
{
private:
	
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsperson(string firstname , string lastname , string email , string phone)
	{
		_FirstName = firstname;
		_LastName = lastname;
		_Email = email;
		_Phone = phone;
	}

	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string GetFirstName()
	{
		return _FirstName;
	}

	_declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

	void SetLastName(string LastName)
	{
		_LastName =LastName;
	}

	string GetLastName()
	{
		return _LastName;
	}

	_declspec(property(get = GetLastName, put = SetLastName)) string LastName;

	void SetEmail(string Email)
	{
		_Email = Email;
	}

	string GetEmail()
	{
		return _Email;
	}

	_declspec(property(get = GetEmail, put = SetEmail)) string Email;

	void SetPhone(string Phone)
	{
		_Phone =Phone;
	}

	string GetPhone()
	{
		return _Phone;
	}

	_declspec(property(get = GetPhone, put = SetPhone)) string Phone;

	string GetFullName()
	{
		return _FirstName + " " + _LastName;
	}

	_declspec(property(get = GetFullName)) string FullName;



};

