#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsinputvalidation.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

	static double _ReadAmountToExchange()
	{
		cout << "Enter Amount to Exchange: ";
		double AmountToExchange = clsinputvalidation::ReadDBLNumber("Wrong Value , enter the number of Amount to Exchange: ");
		return AmountToExchange;
	}

	static clsCurrency _GetCurrency(string message)
	{
		string Code;
		cout << message;
		Code = clsinputvalidation::ReadString();
		while (!clsCurrency::IsCurrencyExist(Code))
		{
			cout << "Incorrect Currency Code , Enter another one: ";
			Code = clsinputvalidation::ReadString();
		}
		clsCurrency Currency = clsCurrency::FindByCode(Code);
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency Currency , string message)
	{
		cout <<message;
		cout << "________________________________________\n\n";
		cout << "Country      : " << Currency.Country << endl;
		cout << "Code         : " << Currency.CurrencyCode << endl;
		cout << "Name         : " << Currency.CurrencyName << endl;
		cout << "Rate(1$) is  : " << Currency.Rate << endl;
		cout << "\n________________________________________\n\n";
	}

	static void _PerformExchangeProcess(clsCurrency FromCurrency, clsCurrency ToCurrency, double AmountToExchange)
	{

		_PrintCurrencyCard(FromCurrency, "\nConvert From\n");

		double AmountInUsd = FromCurrency.ConvertToUsd(AmountToExchange);

		cout << AmountToExchange << " " << FromCurrency.CurrencyCode << " = "
			<< AmountInUsd << " USD\n";

		if (ToCurrency.CurrencyCode == "USD")
		{
			return;
		}
		_PrintCurrencyCard(ToCurrency, "\nConverting from USD to: \n");
		cout << AmountToExchange << " " << FromCurrency.CurrencyCode << " = "
			 << FromCurrency.ConvertRateToOtherCurrency(AmountToExchange,ToCurrency)<< " "
			 << ToCurrency.CurrencyCode << endl;
	}

	static void _PerformCurrencyCalculatorScreen()
	{
		_DrawScreenHeader("\t Currency Calculator Screen");

		clsCurrency FromCurrency = _GetCurrency("Please Enter Currency1 Code : ");
		clsCurrency ToCurrency = _GetCurrency("Please Enter Currency2 Code : ");
		double AmountToExchange = _ReadAmountToExchange();
		_PerformExchangeProcess(FromCurrency, ToCurrency, AmountToExchange);

	}

public:

	static void ShowCurrencyCalculatorScreen()
	{
		string Answer;
		do
		{
			system("cls");
			_PerformCurrencyCalculatorScreen();
			cout << "\nDo you want to perform another Calculation? Y/N ? ";
			Answer = clsinputvalidation::ReadString();
		} while (Answer == "y" || Answer == "Y");
	}

};

