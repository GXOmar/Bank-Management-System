/*
    -*- Input validation library -*-
*/
#pragma once
#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:
    // short number in C++ like: 10
    static bool isNumberBetween(short num, short from, short to)
    {
        return num >= from && num <= to;
    };

    // int number in C++ like: 10
    static bool isNumberBetween(int num, int from, int to)
    {
        return num >= from && num <= to;
    };

    // float number in C++ like: 10.8f
    static bool isNumberBetween(float num, float from, float to)
    {
        return num >= from && num <= to;
    };

    // double number in C++ like: 10.8
    static bool isNumberBetween(double num, double from, double to)
    {
        return num >= from && num <= to;
    };

    // Converting all above functions into a template function
    template <typename T>
    static T isNumberBetween(T num, T from, T to)
    {
        return num >= from && num <= to;
    };

    static bool isDateBetween(clsDate date, clsDate dateFrom, clsDate dateTo)
    {
        // date >= from && date <= to
        if ((date.isDateAfterDate2(dateFrom) || date.isDateEqualToDate2(dateFrom)) &&
            (date.isDateLessThanDate2(dateTo) || date.isDateEqualToDate2(dateTo)))
        {
            return true;
        }
        // date <= from && date >= to
        else if ((date.isDateLessThanDate2(dateFrom) || date.isDateEqualToDate2(dateFrom)) &&
                 (date.isDateAfterDate2(dateTo) || date.isDateEqualToDate2(dateTo)))
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    static int readIntNumber(string errorMsg = "Invalid number: ")
    {
        // including int type validation
        int n = 0;
        cin >> n;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errorMsg;
            cin >> n;
        }
        return n;
    };

    static int readPositiveIntNumber(string errorMsg = "Invalid number: ")
    {
        int n = 0;
        while ((n = readIntNumber(errorMsg) <= 0))
        {
            cout << "Enter a positive number" << endl;
        };
        return n;
    };

    static float readFloatNumber(string errorMsg = "Invalid number: ")
    {
        // including float type validation
        float n = 0;
        cin >> n;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errorMsg;
            cin >> n;
        }
        return n;
    };

    static float readPositiveFloatNumber(string errorMsg = "Invalid number: ")
    {
        float n = 0;
        while ((n = readFloatNumber(errorMsg) <= 0))
        {
            cout << "Enter a positive number" << endl;
        };
        return n;
    };

    static double readDblNumber(string errorMsg = "Invalid number: ")
    {
        // including double type validation
        double n = 0;
        cin >> n;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errorMsg;
            cin >> n;
        }
        return n;
    };

    template <typename T>
    static T readNumber(string errMsg = "Invalid number: ")
    {
        // including int type validation
        T n;
        cin >> n;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errMsg;
            cin >> n;
        }
        return n;
    };

    template <typename T>
    static T readPositiveNumber(string errMsg = "Invalid number: ")
    {
        T n;
        while ((n = readIntNumber(errMsg) <= 0))
        {
            cout << "Enter a positive number" << endl;
        };
        return n;
    };

    static double readPositiveDblNumber(string errorMsg = "Invalid number: ")
    {
        double n = 0;
        bool error = false;
        do
        {
            if (error)
                cout << "Enter a positive number" << endl;
            n = readDblNumber(errorMsg);
        } while ((error = n <= 0));

        return n;
    };

    static int readIntNumberInRange(int from, int to, string errorMsg = "Invalid number: ")
    {
        int num = 0;
        bool error = false;
        do
        {
            if (error)
                cout << errorMsg;
            num = readIntNumber(errorMsg);
        } while ((error = !isNumberBetween(num, from, to)));
        return num;
    };

    static double readDbleNumberInRange(double from, double to, string errorMsg = "Invalid number: ")
    {
        double num = 0;
        do
        {
            num = readDblNumber(errorMsg);
        } while (!isNumberBetween(num, from, to));
        return num;
    };

    template <typename T>
    static T readNumberInRange(T from, T to, string errMsg = "Invalid Number: ")
    {
        T num;
        bool error = false;
        do
        {
            if (error)
                cout << errMsg;
            num = readNumber<T>(errMsg);
        } while ((error = !isNumberBetween(num, from, to)));
        return num;
    };

    static string readString(string message = "")
    {
        string text = "";
        while (text == "")
        {
            cout << message;
            cin.ignore(0, '\n');
            // usage of std::ws will extract all the whitespace characters
            getline(cin >> ws, text);
        }
        return text;
    };

    static char readChar(string message = "")
    {
        char text = ' ';
        while (text == ' ')
        {
            cout << message;
            cin >> text;
        }
        return text;
    };

    template <typename T>
    static T readText(string message = "")
    {
        T text;
        while (!text)
        {
            cout << message;
            cin.ignore(0, '\n');
            // usage of std::ws will extract all the whitespace characters
            getline(cin >> ws, text);
        }
        return text;
    };

    static bool isValidDate(clsDate date)
    {
        return date.isValid();
    };

    static bool askYesOrNo(string message = "Are you sure (Y/N)? ")
    {
        char answer = readChar(message);
        return answer == 'y' || answer == 'Y' ? true : false;
    };
};