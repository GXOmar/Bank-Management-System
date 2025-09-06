/*
    UI - Currency calculator screen
*/

#pragma once
#include <iostream>
#include "../../Core/clsCurrency.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"

class clsCurrencyCalculatorScreen : protected clsScreen
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
    };

    static clsCurrency _searchViaCode()
    {
        return clsCurrency::findByCode(clsInputValidate::readString("Enter currency code: "));
    };

    static clsCurrency _searchViaCountry()
    {
        return clsCurrency::findByCountry(clsInputValidate::readString("Enter country name: "));
    };

    static clsCurrency _runFindCurrencyProccess()
    {
        cout << "Find currency by:\n\t[1] Currency code\n\t[2] Country name\n-----------------------------\n\tChoose an option: ";
        int optionToPerform = clsInputValidate::readIntNumberInRange(1, 2);

        if (optionToPerform == 1)
            return _searchViaCode();
        else
            return _searchViaCountry();
    };

    static clsCurrency _getCurrency()
    {
        clsCurrency currency = _runFindCurrencyProccess();
        while (currency.isEmpty())
        {
            cout << "\nCurrency not found! enter another one.\n";
            currency = _runFindCurrencyProccess();
        }
        return currency;
    };

    static void _runCalculatorProccess()
    {
        float calcResult = 0.0f;
        float amountToExchange = 0.0f;

        cout << "Enter first currency to calclate from\n";
        clsCurrency currency1 = _getCurrency();
        _printCurrencyDetails(currency1);

        cout << "Enter second currency to calclate from\n";
        clsCurrency currency2 = _getCurrency();
        _printCurrencyDetails(currency2);

        cout << "\nEnter amount to exchange: ";
        amountToExchange = clsInputValidate::readFloatNumber();

        calcResult = currency1.convertTo(currency2, amountToExchange);

        cout << '\n'
             << amountToExchange << ' ' << currency1.getCurrencyCode() << " = " << calcResult << ' ' << currency2.getCurrencyCode() << '\n'
             << endl;
    };

public:
    static void showCurrencyCalculatorScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\tCurrency calculator screen");
        _runCalculatorProccess();
    }
};