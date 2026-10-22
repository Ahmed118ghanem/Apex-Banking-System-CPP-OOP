#pragma once
#include<iostream>
#include <vector> 
#include <string>
using namespace std;

class clsstring
{
private:
	string _value;
public:

	clsstring()
	{
		_value = "";
	}

	clsstring(string value)
	{
		_value = value;
	}

	void Set_value(string value)
	{
		_value = value;
	}

	string Get_value()
	{
		return _value;
	}

	__declspec(property(get = Get_value, put = Set_value)) string Value;


	static short Length(string s1)
	{
		return s1.length();
	}

	short Length()
	{
		return Length(_value);
	}

	static short CountWord(string s1)
	{
		short count = 0;
		int pos = 0;
		string belim = " ";
		string word = "";

		while ((pos = s1.find(belim)) != string::npos)
		{
			word = s1.substr(0, pos);
			if (word != "")
			{
				count++;
			}
			s1.erase(0, pos + belim.length());
		}
		if (s1 != "")
		{
			count++;
		}
		return count;
	}

	short CountWord()
	{
		return CountWord(_value);
	}


	static string UpperFirstLetterOfEachword(string s1)
	{
		bool isfirstletter = true;

		for (int x = 0; x < s1.length(); x++)
		{
			if (s1[x] != ' ' && isfirstletter)
			{
				s1[x] = toupper(s1[x]);
				isfirstletter = false;
			}
			if (s1[x] == ' ')
			{
				isfirstletter = true;
			}
		}
		return s1;
	}

	string UpperFirstLetterOfEachword()
	{
		UpperFirstLetterOfEachword(_value);
	}


	static string LowerFirstLetterOfEachword(string s1)
	{
		bool isfirstletter = true;
		int x = 0;

		while (x < s1.length())
		{

			if (s1[x] != ' ' && isfirstletter)
			{
				s1[x] = tolower(s1[x]);
				isfirstletter = false;
			}
			if (s1[x] == ' ')
			{
				isfirstletter = true;
			}
			x++;
		}
		return s1;
	}

	string LowerFirstLetterOfEachword()
	{
		return LowerFirstLetterOfEachword(_value);
	}

	static string UpperAllString(string s1)
	{
		for (int x = 0; x < s1.length(); x++)
		{
			if (s1[x] != ' ')
				s1[x] = toupper(s1[x]);
		}
		return s1;
	}

	string UpperAllString()
	{
		return UpperAllString(_value);
	}

	static string LowerAllString(string s1)
	{
		for (int x = 0; x < s1.length(); x++)
		{
			if (s1[x] != ' ')
				s1[x] = tolower(s1[x]);
		}
		return s1;
	}

	string LowerAllString()
	{
		return LowerAllString(_value);
	}

	static char InvertLetterCase(char s1)
	{
		return (isupper(s1)) ? tolower(s1) : toupper(s1);
	}

	static string InvertAllLettersCase(string s1)
	{
		for (int x = 0; x < s1.length(); x++)
		{
			s1[x] = InvertLetterCase(s1[x]);
		}
		return s1;
	}

	string InvertAllLettersCase()
	{
		return InvertAllLettersCase(_value);
	}

	enum enWhatToCount { EALL = 0, ECapital = 1, ESmall = 3 };

	static short CountLetters(string s1, enWhatToCount whattocount)
	{
		short count = 0;
		for (int x = 0; x < s1.length(); x++)
		{
			if (whattocount == enWhatToCount::EALL)
			{
				if (s1[x] != ' ')
					count++;
			}

			if (whattocount == enWhatToCount::ECapital)
			{
				if (s1[x] != ' ' && isupper(s1[x]))
					count++;
			}

			if (whattocount == enWhatToCount::ESmall)
			{
				if (s1[x] != ' ' && islower(s1[x]))
					count++;
			}
		}
		return count;
	}

	short CountLetters(enWhatToCount whattocount)
	{
		return CountLetters(_value, whattocount);
	}

	static short CountSpecificLetter(string s1, char letter, bool matchcase = true)
	{
		short count = 0;

		for (int x = 0; x < s1.length(); x++)
		{
			if (matchcase)
			{
				if (s1[x] == letter)
					count++;
			}
			else
			{
				if (tolower(s1[x]) == tolower(letter))
					count++;
			}
		}
		return count;
	}

	short CountSpecificLetter(char letter, bool matchcase = true)
	{
		return CountSpecificLetter(_value, letter, matchcase);
	}

	static bool IsVowel(char letter)
	{
		letter = tolower(letter);

		return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u');
	}

	static short CountVowels(string s1)
	{
		short count = 0;

		for (int x = 0; x < s1.length(); x++)
		{
			if (IsVowel(s1[x]))
				count++;
		}
		return count;
	}

	short CountVowels()
	{
		return CountVowels(_value);
	}

	static vector <string> Split(string s1, string delim)
	{
		vector <string> vstring;

		int pos = 0;
		string word = "";
		while ((pos = s1.find(delim)) != string::npos)
		{
			word = s1.substr(0, pos);
			if (word != "")
			{
				vstring.push_back(word);
			}
			s1.erase(0, pos + delim.length());
		}
		if (s1 != "")
		{
			vstring.push_back(s1);
		}
		return vstring;
	}

	vector <string> Split(string delim)
	{
		return Split(_value, delim);
	}

	static string TrimLeft(string s1)
	{
		for (int x = 0; x < s1.length(); x++)
		{
			if (s1[x] != ' ')
				return s1.substr(x, s1.length() - x);
		}
		return s1;
	}

	string TrimLeft()
	{
		return TrimLeft(_value);
	}

	static string TrimRight(string s1)
	{
		for (int x = s1.length() - 1; x >= 0; x--)
		{
			if (s1[x] != ' ')
				return s1.substr(0, x + 1);
		}
	}

	string TrimRight()
	{
		return TrimRight(_value);
	}

	string Trim()
	{
		return TrimLeft(TrimRight(_value));
	}

	static string JoinString(vector <string> vstring, string delim)
	{
		string word = "";

		for (string s : vstring)
		{
			word += s + delim;
		}
		return word.substr(0, word.length() - delim.length());
	}

	static string JoinString(string arr[], int length, string delim)
	{
		string word = "";

		for (int x = 0; x < length; x++)
		{
			word += arr[x] + delim;
		}


		return word.substr(0, word.length() - delim.length());
	}

	static string ReverseWordsInString(string s1)
	{
		vector <string> vstring = Split(s1, " ");
		string word = "";
		vector <string>::iterator iter = vstring.end();

		while (iter != vstring.begin())  // ahmed mohamed ghanem
		{
			iter--;
			word += *iter + " ";
		}
		return word.substr(0, word.length() - 1);
	}

	string ReverseWordsInString()
	{
		return ReverseWordsInString(_value);
	}


	static string ReplaceWord(string s1, string stringtoreplace, string replaceto, bool matchcase = true)
	{
		vector <string> vstring = Split(s1, " ");

		for (string& s : vstring)
		{
			if (matchcase)
			{
				if (s == stringtoreplace)
				{
					s = replaceto;
				}
			}
			else
			{
				if (LowerAllString(s) == LowerAllString(stringtoreplace))
				{
					s = replaceto;
				}
			}
		}
		return JoinString(vstring, " ");
	}

	string ReplaceWord(string stringtoreplace, string replaceto, bool matchcase)
	{
		return ReplaceWord(_value, stringtoreplace, replaceto, matchcase);
	}

	static string removepunctuation(string s1)
	{
		string s2;
		for (int x = 0; x < s1.length(); x++)
		{
			if (!ispunct(s1[x]))
			{
				s2 += s1[x];
			}
		}
		return s2;
	}

	string removepunctuation()
	{
		return removepunctuation(_value);
	}

	static void SwapString(clsstring& s1, clsstring& s2)
	{
		clsstring temp;

		temp = s1;
		s1 = s2;
		s2 = temp;
	}

	void SwapString(clsstring& s2)
	{
		SwapString(*this, s2);
	}

};


