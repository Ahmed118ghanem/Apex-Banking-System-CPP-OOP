#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "clsdate.h"
using namespace std;

class clsutil
{
public:

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

	enum encharacter { capitalLetter = 1, SmallLetter = 2, Digit = 3, SpecialChar = 4, MixChars = 5 };

	static char GetRandomCharacter(encharacter character)
	{

		if (character == MixChars)
		{
			character = (encharacter)RandomNumber(1, 4);
		}

		switch (character)
		{
		case encharacter::capitalLetter:
			return char(RandomNumber(65, 90));
		case encharacter::SmallLetter:
			return char(RandomNumber(97, 122));
		case encharacter::Digit:
			return char(RandomNumber(48, 57));
		case encharacter::SpecialChar:
			return char(RandomNumber(33, 47));
		default:
			return char(RandomNumber(65, 90));
		}
	}

	static string GenerateWord(encharacter character, int number)
	{
		string word = "";
		for (int x = 1; x <= number; x++)
		{
			word += GetRandomCharacter(character);
		}
		return word;
	}

	static string GenerateKey(encharacter character)
	{
		string keyword = "";
		for (int x = 1; x <= 4; x++)
		{
			keyword += GenerateWord(character, 4) + "-";

		}
		keyword.pop_back();
		return keyword;
	}

	static void GenerateKeys(int number, encharacter character)
	{
		for (int x = 1; x <= number; x++)
		{
			cout << "Key [" << x << "] : " << GenerateKey(character) << endl;
		}
	}

	static void Swap(int& num1, int& num2)
	{
		int temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}

	static void Swap(string& s1, string& s2)
	{
		string temp = s1;
		s1 = s2;
		s2 = temp;
	}

	static void Swap(clsdate& date1, clsdate& date2)
	{
		clsdate::SwapDates(date1, date2);
	}

	static void ShuffleArray(int arr[], int length)
	{
		for (int x = 0; x < length; x++)
		{
			int randomindex = rand() % length;
			int temp = arr[x];
			arr[x] = arr[randomindex];
			arr[randomindex] = temp;
		}
	}

	static void ShuffleArray(string arr[], int length)
	{
		for (int x = 0; x < length; x++)
		{
			int randomindex = rand() % length;
			string temp = arr[x];
			arr[x] = arr[randomindex];
			arr[randomindex] = temp;
		}
	}

	static void FillArrayWithRandomNumbers(int arr[], int length, int from, int to)
	{
		for (int x = 0; x < length; x++)
		{
			arr[x] = RandomNumber(from, to);
		}
	}

	static void FillArrayWithRandomWords(string arr[], int length, encharacter character, int numberofwords)
	{
		for (int x = 0; x < length; x++)
		{
			arr[x] = GenerateWord(character, 8);
		}
	}

	static void FillArrayWithRandomKeys(string arr[], int length, encharacter character)
	{
		for (int x = 0; x < length; x++)
		{
			arr[x] = GenerateKey(character);
		}
	}

	static string Tabs(int numt)
	{
		string t = "";
		for (int x = 1; x <= numt; x++)
		{
			t += "\t";
		}
		return t;
	}

	static string  EncryptText(string Text, short EncryptionKey = 3)
	{

		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + EncryptionKey);
		}

		return Text;

	}

	static string  DecryptText(string Text, short EncryptionKey = 3)
	{

		for (int i = 0; i < Text.length(); i++)
		{

			Text[i] = char((int)Text[i] - EncryptionKey);

		}
		return Text;

	}

	static string NumberToText(long number)
	{
		if (number == 0)
		{
			return "";
		}

		if (number >= 1 && number <= 19)
		{
			string arr[] = { "One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten",
							"Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
			return arr[number - 1];
		}

		if (number >= 20 && number <= 99)
		{
			string arr[] = { "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return arr[(number / 10) - 2] + " " + NumberToText(number % 10);
		}

		if (number >= 100 && number <= 999)
		{
			return NumberToText(number / 100) + " Hundred " + NumberToText(number % 100);
		}

		if (number >= 1000 && number <= 999999)
		{
			return NumberToText(number / 1000) + " Thousand" + NumberToText(number % 1000);
		}

		if (number >= 1000000 && number <= 999999999)
		{
			return NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000);
		}

		if (number >= 1000000000 && number <= 999999999999)
		{
			return NumberToText(number / 1000000000) + " Billion " + NumberToText(number % 1000000000);
		}

	}

};

