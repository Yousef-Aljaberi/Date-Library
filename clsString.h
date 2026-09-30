#pragma once
#include<iostream>
#include<vector>
using namespace std;

class clsString
{
private:
	string _Value;
public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}

	void setValue(string Value)
	{
		_Value = Value;
	}

	string getValue()
	{
		return _Value;
	}



	__declspec(property(get = getValue, put = setValue))  string Value;


	short Length()
	{
		return _Value.length();
	}
	static short Length(string Value)
	{
		return Value.length();
	}
	static void PrintFirstLetterOfEachWors(string text)
	{
		bool IsFirstLetter = true;
		cout << "Firsts Letter Of This String: \n";

		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ' && IsFirstLetter)
			{
				cout << text[i] << "\n";
			}
			IsFirstLetter = (text[i] == ' ' ? true : false);
		}
	}

	void PrintFirstLetterOfEachWors()
	{
		PrintFirstLetterOfEachWors(_Value);

	}

	static string UpperFirstLeeterOfEachWord(string text)
	{
		bool IsFirstLetter = true;
		for (short i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ' && IsFirstLetter)
			{
				text[i] = toupper(text[i]);
			}

			IsFirstLetter = (text[i] == ' ' ? true : false);
		}
		return text;
	}

	void  UpperFirstLeeterOfEachWord()
	{
		_Value = UpperFirstLeeterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string text)
	{
		bool IsFirstLetter = true;
		for (short i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ' && IsFirstLetter)
			{
				text[i] = tolower(text[i]);
			}
			IsFirstLetter = (text[i] == ' ' ? true : false);
		}
		return text;
	}

	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string LowerAllLetterOfString(string text)
	{
		for (short i = 0; i < text.length(); i++)
		{

			text[i] = tolower(text[i]);

		}
		return text;

	}

	void LowerAllLetterOfString()
	{
		_Value = LowerAllLetterOfString(_Value);
	}

	static 	char InvertCharecterCase(char L)
	{
		return isupper(L) ? tolower(L) : toupper(L);
	}

	static string InverAllLettersCase(string text)
	{
		for (int i = 0; i < text.length(); i++)
		{
			text[i] = InvertCharecterCase(text[i]);
		}
		return text;
	}

	void InverAllLettersCase()
	{
		_Value = InverAllLettersCase(_Value);
	}

	static enum enWhatToCount { Capital = 1, Small = 2, All = 3 };

	static int CountSmallCapitalLetters(string text, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
		{
			return text.length();
		}
		int Counter = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (WhatToCount == enWhatToCount::Small && islower(text[i]))
				Counter++;

			else if (WhatToCount == enWhatToCount::Capital && isupper(text[i]))
				Counter++;
		}
		return Counter;
	}

	int CountSmallCapitalLetters(enWhatToCount WhatToCount)
	{
		return CountSmallCapitalLetters(_Value, WhatToCount);
	}

	static int  CountLetters(string text, char TargetChar)
	{
		int count = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] == TargetChar)
				count++;
		}
		return count;
	}

	int CountLetters(char TargetChar)
	{
		return CountLetters(_Value, TargetChar);
	}

	static short CountLetterNoMatchCase(string text, char TargetLetter, bool NoMatchCase = true)
	{
		short Count = 0;
		for (short i = 0; i < text.length(); i++)
		{
			if (NoMatchCase)
			{
				if (text[i] == TargetLetter)
				{
					Count++;
				}
			}
			else if (!NoMatchCase)
			{
				if (tolower(text[i]) == tolower(TargetLetter))
					Count++;
			}
		}
		return Count;
	}

	short CountLetterNoMatchCase(char TargetLetter, bool NoMatchCase = true)
	{
		return  CountLetterNoMatchCase(_Value, TargetLetter, NoMatchCase);
	}

	static bool IsVowel(char Ch1)
	{
		Ch1 = tolower(Ch1);
		return((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));

	}
	static short CountVowels(string text)
	{
		int counter = 0;
		for (short i = 0; i < text.length(); i++)
		{
			if (IsVowel(text[i]))
			{
				counter++;
			}
		}
		return counter;


	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintAllVowelsLetter(string text)
	{
		cout << "\nVowels Letters in string is/are: ";
		for (short i = 0; i < text.length(); i++)
		{
			if (IsVowel(text[i]))
			{
				cout << text[i] << "	";
			}
		}


	}

	void PrintAllVowelsLetter()
	{
		PrintAllVowelsLetter(_Value);
	}

	static void PrintEachWordOfString(string text)
	{
		int pos = 0;
		string delim = " ";			//delimiter
		string sWord;				//define a string varible

		//use find() functioin to get delimiter position 
		while ((pos = text.find(delim)) != std::string::npos)
		{
			sWord = text.substr(0, pos);  //store the word
			if (sWord != "")
			{
				cout << sWord << endl;
			}

			text.erase(0, pos + delim.length()); //erase until position and move to next word.

		}
		if (text != "")
		{
			cout << text << endl;   //it print last word of the string 
		}

	}

	void PrintEachWordOfString()
	{
		PrintEachWordOfString(_Value);
	}

	static short CountEachWordOfString(string text)
	{
		short Count = 0;

		short pos = 0;
		string delim = " ";
		string sWord;
		while ((pos = text.find(delim)) != std::string::npos)
		{
			sWord = text.substr(0, pos);
			if (sWord != "")
			{
				Count++;
			}
			text.erase(0, pos + delim.length());
		}

		if (text != "")
		{
			Count++;
		}
		return Count;
	}
	short CountEachWordOfString()
	{
		return  CountEachWordOfString(_Value);
	}


	static vector<string> SplitString(string text, string delim)
	{
		vector <string> vString;
		short pos = 0;
		string sWord;
		while ((pos = text.find(delim)) != std::string::npos)
		{
			sWord = text.substr(0, pos);
			if (sWord != "")
			{
				vString.push_back(sWord);
			}
			text.erase(0, pos + delim.length());
		}
		if (text != "")
		{
			vString.push_back(text);
		}

		return vString;

	}

	vector<string> SplitString(string delim)
	{
		return SplitString(_Value, delim);
	}

	static string TrimLeft(string text)
	{
		for (int i = 0; i < text.length(); i++)
		{
			if (text[i] != ' ')
			{
				return text.substr(i, text.length() - i);
			}
		}

		return "";


	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string text)
	{


		for (int i = text.length() - 1; i >= 0; i--)
		{
			if (text[i] != ' ')
			{
				return text.substr(0, i + 1);
			}
		}
		return "";

	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string text)
	{
		return TrimLeft(TrimRight(text));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector <string> vString, string delim)
	{
		string S1 = "";
		for (string& Word : vString)
		{
			S1 += Word + delim;
		}

		return S1.substr(0, S1.length() - delim.length());
	}

	static string JoinString(string arrString[], short Length, string delim)
	{
		string S1 = "";
		for (short i = 0; i < Length; i++)
		{
			S1 += arrString[i] + delim;
		}


		return S1.substr(0, S1.length() - delim.length());
	}

	static string ReversWordsInString(string text)
	{

		vector <string> vWords;
		vWords = SplitString(text, " ");
		string text2 = "";
		vector<string>::iterator iter = vWords.end();

		while (iter != vWords.begin())
		{
			--iter;
			text2 += *iter + " ";
		}

		text2 = text2.substr(0, text.length() - 1);


		return text2;

	}
	void ReversWordsInString()
	{
		_Value = ReversWordsInString(_Value);
	}


	static string ReplaceWordInString(string text, string StringToReplace, string sReplaceTo)
	{
		short pos = text.find(StringToReplace);
		while (pos != std::string::npos)
		{
			text = text.replace(pos, StringToReplace.length(), sReplaceTo);
			pos = text.find(StringToReplace);
		}
	}
	void ReplaceWordInString(string StringToReplace, string sReplaceTo)
	{
		_Value = ReplaceWordInString(_Value, StringToReplace, sReplaceTo);
	}

	static string ReplaceWord(string S13, string StringToReplace, string sRepalceTo, bool MatchCase = true)
	{
		vector <string> vString = SplitString(S13, " ");
		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace) s = sRepalceTo;
			}
			else
			{
				if (LowerAllLetterOfString(s) == LowerAllLetterOfString(StringToReplace)) s = sRepalceTo;
			}
		}
		return JoinString(vString, " ");
	}
	void ReplaceWords(string StringToReplace, string sRplaceTo, bool MatchCase = true)
	{
		_Value = ReplaceWord(_Value, StringToReplace, sRplaceTo, MatchCase);
	}

	static string RemovePunctuations(string text)
	{
		string S1 = "";
		for (int i = 0; i < text.length(); i++)
		{
			if (!ispunct(text[i]))
			{
				S1 += text[i];
			}
		}
		return S1;
	}
	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}


};


