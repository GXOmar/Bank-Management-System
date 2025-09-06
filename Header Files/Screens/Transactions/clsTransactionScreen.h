/*
    UI - Transaction screen, a sub menu of main menu
*/
#pragma once
#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionScreen : protected clsScreen
{
private:
    enum enTransactionMenuOptions
    {
        eDeposit = 1,
        eWithdraw = 2,
        eTotalBalance = 3,
        eTransferFunds = 4,
        eTransferLogs = 5,
        eExit = 6
    };

    static enTransactionMenuOptions _readTransactionOption()
    {
        return (enTransactionMenuOptions)clsInputValidate::readIntNumberInRange(1, 6);
    };

    static void _showDepositScreen()
    {
        clsDepositScreen::showDepositScreen();
    };

    static void _showWithdrawScreen()
    {
        clsWithdrawScreen::showWithdrawScreen();
    };

    static void _showTotalBalanceScreen()
    {
        clsTotalBalancesScreen::showTotalBalancesScreen();
    };

    static void _showTransferFundsScreen()
    {
        clsTransferScreen::showTransferScreen();
    };

    static void _showTransferLogScreen()
    {
        clsTransferLogScreen::showTransferLogScreen();
    };

    static void _performTransactionOption(enTransactionMenuOptions option)
    {
        switch (option)
        {
        case enTransactionMenuOptions::eDeposit:
            _showDepositScreen();
            break;
        case enTransactionMenuOptions::eWithdraw:
            _showWithdrawScreen();
            break;
        case enTransactionMenuOptions::eTotalBalance:
            _showTotalBalanceScreen();
            break;
        case enTransactionMenuOptions::eTransferFunds:
            _showTransferFundsScreen();
            break;
        case enTransactionMenuOptions::eTransferLogs:
            _showTransferLogScreen();
            break;
        default:
            return; // exit transaction menu
        };
    };

    static void _printTransactionMenuScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tTransaction Screen");
        cout
            << "================================================\n";
        cout << "\t\tTransaction menu screen\n";
        cout << "================================================\n";
        cout << "\t[1] Deposit\n";
        cout << "\t[2] Withdraw\n";
        cout << "\t[3] Total balances\n";
        cout << "\t[4] Transfer funds\n";
        cout << "\t[5] Transfer logs\n";
        cout << "\t[6] Main menu\n";
        cout << "================================================\n";
    };

public:
    static void showTransactionScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eTransactions))
        {
            enTransactionMenuOptions transactionToPerform = enTransactionMenuOptions::eExit;
            do
            {
                _printTransactionMenuScreen();
                cout << "Select an option to perform [1 to 6]: ";
                transactionToPerform = _readTransactionOption();
                if (transactionToPerform == enTransactionMenuOptions::eExit)
                    return;

                _performTransactionOption(transactionToPerform);
                clsUtil::waitForKeyPress();
            } while (transactionToPerform != enTransactionMenuOptions::eExit);
        }
        else
        {
            displayAccessDeniedScreen();
            clsUtil::waitForKeyPress();
        };
    };
};