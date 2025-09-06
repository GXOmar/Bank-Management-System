/*
    UI - Find currency screen
*/

#pragma once
#include <iostream>
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _printCurrencyDetails(clsCurrency currency)
    {
        cout << left;
        cout << "\n———————————————————————————————\n";
        cout << "Country name: " << currency.getCountryName() << '\n';
        cout << "Currency code: " << currency.getCurrencyCode() << '\n';
        cout << "Currency name: " << currency.getCurrencyName() << '\n';
        cout << "Currency Rate: " << currency.getRate();
        cout << "\n———————————————————————————————\n";
    }

    static void _searchViaCode()
    {
        clsCurrency currency = clsCurrency::findByCode(clsInputValidate::readString("Enter currency code: "));
        if (currency.isEmpty())
        {
            cout << "Currency not found!" << endl;
            return;
        }
        _printCurrencyDetails(currency);
    }

    static void _searchViaCountry()
    {
        clsCurrency currency = clsCurrency::findByCountry(clsInputValidate::readString("Enter country name: "));
        if (currency.isEmpty())
        {
            cout << "Currency not found!" << endl;
            return;
        }
        _printCurrencyDetails(currency);
    }

    static void _runFindCurrencyProccess()
    {
        cout << "Find by\n[1] Currency code\t[2] Country name: ";
        int optionToPerform = clsInputValidate::readIntNumberInRange(1, 2);

        if (optionToPerform == 1)
        {
            _searchViaCode();
        }
        else
        {
            _searchViaCountry();
        };
    };

public:
    static void showFindCurrencyScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\tFind currency screen");
        _runFindCurrencyProccess();
    };
};