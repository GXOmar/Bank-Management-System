/*
    -*- Custom String library -*-
*/

#pragma once

#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
    string _value;

public:
    enum enCharType
    {
        ALL,
        SMALL,
        CAPITAL
    };

    // Default constructor
    // to initialize an instance with no value
    clsString()
    {
        _value = "";
    }

    // Parameterized constructor
    // to initialize an instance with a value
    clsString(string value)
    {
        _value = value;
    }

    // property set
    void setValue(string value)
    {
        _value = value;
    }

    // property get
    string getValue()
    {
        return _value;
    }

    // to use instanceVarName.value = "x" syntax i.e. use property set and get through "=" sign
    __declspec(property(get = getValue, put = setValue)) string value;

    static int countWords(string text)
    {
        string delimiter = " "; // single space
        string word = "";       // store each word from string
        int position = 0;       // store delimeter position
        int count = 0;

        while ((position = text.find(delimiter)) != text.npos)
        {
            word = text.substr(0, position);
            if (word != "")
            {
                count++;
            }
            text.erase(0, position + delimiter.length());
        }
        if (text != "")
        {
            count++;
        }
        return count;
    }

    // overload countWords() method to use with instances of this class without supplying a parameter when calling the member function.
    int countWords()
    {
        return countWords(_value);
    }

    static int length(string text)
    {
        return text.length();
    }

    int length()
    {
        return length(_value);
    }

    static vector<string> split(string text, string delimiter = " ")
    {
        string word = ""; // store each word from string
        int position = 0; // store delimeter position
        vector<string> vStrings;
        while ((position = text.find(delimiter)) != text.npos)
        {
            word = text.substr(0, position);
            if (word != "")
            {
                vStrings.push_back(word);
            }
            text.erase(0, position + delimiter.length());
        }
        if (text != "")
        {
            vStrings.push_back(text);
        }
        return vStrings;
    }

    vector<string> split(string delimiter = " ")
    {
        return split(_value, delimiter);
    }

    static string joinString(vector<string> vString, string delimiter = " ")
    {
        string s = "";
        for (string &word : vString)
        {
            s = s + word + delimiter;
        }
        return s.substr(0, s.length() - delimiter.length());
    }

    static void printFirstLetterOfEachWord(string text)
    {
        cout << text[0] << endl; // assume first character, this could be a space as well!
        for (int i = 0; i < text.length(); i++)
        {
            if (isspace(text[i]))
                cout << text[i + 1] << endl;
        };
    }

    void printFirstLetterOfEachWord()
    {
        printFirstLetterOfEachWord(_value);
    }

    static string upperFirstLetterOfEachWord(string text)
    {
        bool isFirstLetter = true;
        string s = "";
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ' && isFirstLetter)
                s += toupper(text[i]);

            else
                s += text[i];

            isFirstLetter = text[i] == ' ' ? true : false;
        }
        return s;
    };

    void upperFirstLetterOfEachWord()
    {
        _value = upperFirstLetterOfEachWord(_value);
    };

    static string lowerFirstLetterOfEachWord(string text)
    {
        bool isFirstLetter = true;
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ' && isFirstLetter)
                text[i] = tolower(text[i]);

            isFirstLetter = text[i] == ' ' ? true : false;
        }
        return text;
    };

    void lowerFirstLetterOfEachWord()
    {
        _value = lowerFirstLetterOfEachWord(_value);
    };

    static string upperAllLetters(string text)
    {
        for (int i = 0; i < text.length(); i++)
            text[i] = toupper(text[i]);
        return text;
    }

    void upperAllLetters()
    {
        _value = upperAllLetters(_value);
    }

    static string lowerAllLetters(string text)
    {
        for (int i = 0; i < text.length(); i++)
            text[i] = tolower(text[i]);
        return text;
    }

    void lowerAllLetters()
    {
        _value = lowerAllLetters(_value);
    }

    static char invertCharCase(char ch)
    {
        return isupper(ch) ? tolower(ch) : toupper(ch);
    }

    static string invertAllLettersCase(string text)
    {
        for (int i = 0; i < text.length(); i++)
        {
            text[i] = invertCharCase(text[i]);
        }
        return text;
    }

    void invertAllLettersCase()
    {
        _value = invertAllLettersCase(_value);
    }

    static int countSmallLetters(string text)
    {
        int count = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (islower(text[i]))
                count++;
        }
        return count;
    }

    int countSmallLetters()
    {
        return countSmallLetters(_value);
    }

    static int countCapitalLetters(string text)
    {
        int count = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (isupper(text[i]))
                count++;
        }
        return count;
    }

    int countCapitalLetters()
    {
        return countCapitalLetters(_value);
    }

    static int countLetters(string text, enCharType charType = enCharType::ALL)
    {
        if (charType == enCharType::ALL)
            return text.length();

        int count = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (charType == enCharType::CAPITAL && isupper(text[i]))
                count++;

            if (charType == enCharType::SMALL && islower(text[i]))
                count++;
        }
        return count;
    }

    int countLetters(enCharType charType = enCharType::ALL)
    {
        return countLetters(_value, charType);
    }

    static int countLetter(string text, char charToCount, bool matchCase = true)
    {
        int count = 0;
        for (int i = 0; i < text.length(); i++)
        {
            if (matchCase)
            {
                if (text[i] == charToCount)
                    count++;
            }
            else
            {
                if (tolower(text[i]) == tolower(charToCount))
                    count++;
            }
        }
        return count;
    }

    int countLetter(char letter, bool matchCase = true)
    {
        return countLetter(_value, letter, matchCase);
    }

    static bool isVowel(char ch)
    {
        ch = tolower(ch);
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    static int countVowelInString(string text)
    {
        int count = 0;
        for (int i = 0; i < text.length(); i++)
            if (isVowel(text[i]))
                count++;
        return count;
    }

    int countVowelInString()
    {
        return countVowelInString(_value);
    }

    static void printAllVowelsInString(string text)
    {
        for (int i = 0; i < text.length(); i++)
            if (isVowel(text[i]))
                cout << text[i] << ' ';
        cout << endl;
    }

    void printAllVowelsInString()
    {
        printAllVowelsInString(_value);
    }

    static string trimLeft(string text)
    {
        cout << text.length() << endl;

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                text.erase(0, i);
                break;
            }
        }
        return text;
    }

    static string trimRight(string text)
    {
        for (int i = 0; i < text.length(); i++)
        {
            if (text[text.length() - 1 - i] != ' ')
            {
                text.erase(text.length() - i, i);
                break;
            }
        }
        return text;
    }

    static string trim(string text)
    {
        return trimRight(trimLeft(text));
    }

    void trimLeft()
    {
        _value = trimLeft(_value);
    }

    void trimRight()
    {
        _value = trimRight(_value);
    }

    void trim()
    {
        _value = trim(_value);
    }

    string ReverseWordsInString(string str)
    {
        vector<string> vString;
        string revWord = "";
        vString = split(str, " ");

        vector<string>::iterator iter = vString.end(); // declare iterator
        while (iter != vString.begin())
        {
            --iter;
            revWord += *iter + " ";
        }
        revWord = revWord.substr(0, revWord.length() - 1); // remove last space.
        return revWord;
    }

    void ReverseWordsInString()
    {
        _value = ReverseWordsInString(_value);
    };

    string replaceWord(string text, string wordToReplace, string newWord, bool matchCase = true)
    {
        static vector<string> vString = split(text, " ");

        for (string &w : vString)
        {
            if (matchCase)
            {
                if (w == wordToReplace)
                    w = newWord;
            }
            else
            {
                if (lowerAllLetters(w) == lowerAllLetters(wordToReplace))
                    w = newWord;
            }
        }

        return joinString(vString);
    }

    string replaceWord(string oldWord, string newWord, bool matchCase = true)
    {
        return replaceWord(_value, oldWord, newWord, matchCase);
    };

    static string removePunctuationsFromString(string text)
    {
        for (int i = 0; i < text.length(); i++)
            if (ispunct(text[i]))
                text.erase(i, 1);
        return text;
    }
    void removePunctuationsFromString()
    {
        _value = removePunctuationsFromString(_value);
    }
};
