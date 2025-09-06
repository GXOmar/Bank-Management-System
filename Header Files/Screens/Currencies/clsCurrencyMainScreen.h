/*
    UI - Currency exchange main screen
*/

#pragma once
#include <iostream>
#include <iomanip>
#include "../clsScreen.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyMainScreen : protected clsScreen
{
private:
    enum enCurrencyMenuOptions
    {
        eListCur = 1,
        eFindCur = 2,
        eUpdateCur = 3,
        eCalculateCurrency = 4,
        eExitCurMenu = 5
    };

    static void _displayScreenOptions()
    {
        cout << left;
        cout << "\n————————————————————————————————————————————\n";
        cout << "\t[1] List currencies\n";
        cout << "\t[2] Find currency\n";
        cout << "\t[3] Update currency\n";
        cout << "\t[4] Currency calculator\n";
        cout << "\t[5] Main menu";
        cout << "\n————————————————————————————————————————————" << endl;
    };

    static enCurrencyMenuOptions _readMenuOption()
    {
        return (enCurrencyMenuOptions)clsInputValidate::readIntNumberInRange(1, 5);
    };

    static void _showListCurrenciesScreen()
    {
        clsListCurrenciesScreen::showListCurrenciesScreen();
    };

    static void _showFindCurrencyScreen()
    {
        clsFindCurrencyScreen::showFindCurrencyScreen();
    };

    static void _showUpdateCurrencyScreen()
    {
        clsUpdateCurrencyRateScreen::showUpdateCurrencyScreen();
    };

    static void _showCurrencyCalculationScreen()
    {
        clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
    };

    static void _performMenuOption(enCurrencyMenuOptions optionToPerform)
    {
        switch (optionToPerform)
        {
        case enCurrencyMenuOptions::eListCur:
            _showListCurrenciesScreen();
            break;
        case enCurrencyMenuOptions::eFindCur:
            _showFindCurrencyScreen();
            break;
        case enCurrencyMenuOptions::eUpdateCur:
            _showUpdateCurrencyScreen();
            break;
        case enCurrencyMenuOptions::eCalculateCurrency:
            _showCurrencyCalculationScreen();
            break;

        default:
            break;
        };
    };

    static void _runMainScreenProccess()
    {
        enCurrencyMenuOptions optionToPerform = enCurrencyMenuOptions::eExitCurMenu;
        do
        {
            clsUtil::clearConsoleScreen();
            _drawScreenHeader("\tCurrency exchange main screen");
            _displayScreenOptions();
            cout << "Choose an option to perform [1 to 5]: ";
            optionToPerform = _readMenuOption();
            if (optionToPerform == enCurrencyMenuOptions::eExitCurMenu)
                return;
            _performMenuOption(optionToPerform);
            clsUtil::waitForKeyPress("Press a key to return to menu...");
        } while (optionToPerform != enCurrencyMenuOptions::eExitCurMenu);
    };

public:
    static void showMainScreen()
    {
        _runMainScreenProccess();
    };
};