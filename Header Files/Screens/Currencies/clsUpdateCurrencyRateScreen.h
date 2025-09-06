/*
    UI - Update currency rate
*/

#pragma once
#include <iostream>
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"

class clsUpdateCurrencyRateScreen : protected clsScreen
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

    static clsCurrency _searchViaCode()
    {
        clsCurrency currency = clsCurrency::findByCode(clsInputValidate::readString("Enter currency code: "));
        return currency;
    }

    static clsCurrency _searchViaCountry()
    {
        clsCurrency currency = clsCurrency::findByCountry(clsInputValidate::readString("Enter country name: "));
        return currency;
    }

    static clsCurrency _runFindCurrencyProccess()
    {
        cout << "Find by\n[1] Currency code\t[2] Country name: ";
        int optionToPerform = clsInputValidate::readIntNumberInRange(1, 2);

        if (optionToPerform == 1)
        {
            return _searchViaCode();
        }
        else
        {
            return _searchViaCountry();
        };
    };

    static void _runUpdateProccess()
    {
        clsCurrency currency = _runFindCurrencyProccess();
        if (currency.isEmpty())
        {
            cout << "No currency found to update!" << endl;
            return;
        }
        _printCurrencyDetails(currency);
        if (clsInputValidate::askYesOrNo("\nAre you sure you want to update the currency rate (Y/N)? "))
        {
            cout << "Enter new currency rate: ";
            currency.setRate(clsInputValidate::readFloatNumber());
            cout << "\nRate updated successfully\n";
            _printCurrencyDetails(currency);
        }
    };

public:
    static void showUpdateCurrencyScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\tUpdate currency screen");
        _runUpdateProccess();
    }
};