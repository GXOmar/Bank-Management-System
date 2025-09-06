/*
    UI - List currencies screen
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"

class clsListCurrenciesScreen : protected clsScreen
{
private:
    static void _printScreenHeader()
    {
        cout << left;
        cout << "\n————————————————————————————————————————————————————————————————————————————————————————————————————————————\n";
        cout << "| " << setw(40) << "Country name";
        cout << " | " << setw(5) << "Code";
        cout << " | " << setw(40) << "Currency name";
        cout << " | " << setw(10) << "Rate/$1";
        cout << " |";
        cout << "\n————————————————————————————————————————————————————————————————————————————————————————————————————————————\n";
    };

    static void _printCurrencyDetailRecord(clsCurrency &currency)
    {
        cout << "| " << setw(40) << currency.getCountryName();
        cout << " | " << setw(5) << currency.getCurrencyCode();
        cout << " | " << setw(40) << currency.getCurrencyName();
        cout << " | " << setw(10) << currency.getRate();
        cout << " |" << endl;
    };

    static void _showCurrenciesList()
    {
        vector<clsCurrency> vCurrencies = clsCurrency::getAllCurrencies();
        cout << '(' << vCurrencies.size() << ')' << " Currencies." << endl;
        _printScreenHeader();
        for (clsCurrency &currency : vCurrencies)
        {
            _printCurrencyDetailRecord(currency);
        }
        cout << "\n————————————————————————————————————————————————————————————————————————————————————————————————————————————\n";
    };

public:
    static void showListCurrenciesScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\tCurrencies list screen");
        _showCurrenciesList();
    }
};