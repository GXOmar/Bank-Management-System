/*
    UI - Main screen class for the application

    Note: you should create a class for each screen in the application
*/

#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "../Core/clsBankClient.h"
#include "../global.h"
#include "../Lib/clsInputValidate.h"
#include "../Lib/clsUtil.h"
#include "Client/clsListClientScreen.h"
#include "Client/clsAddNewClientScreen.h"
#include "Client/clsDeleteClientScreen.h"
#include "Client/clsUpdateClientScreen.h"
#include "Client/clsFindClientScreen.h"
#include "clsLoginScreen.h"
#include "Transactions/clsTransactionScreen.h"
#include "UserManagement/clsManageUsersScreen.h"
#include "User/clsLoginRegisterListScreen.h"
#include "Currencies/clsCurrencyMainScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:
    enum enMainMenuOptions
    {
        eListClient = 1,
        eAddClient = 2,
        eUpdateClient = 3,
        eDeleteClient = 4,
        eFindClient = 5,
        eTransactions = 6,
        eManageUsers = 7,
        eShowLoginRegister = 8,
        eCurrencyExchange = 9,
        eLogout = 10,
    };

    static enMainMenuOptions _readMainMenuOption()
    {
        return (enMainMenuOptions)clsInputValidate::readIntNumberInRange(1, 10, "Please enter a number between 1 and 10: ");
    };

    static void _showListClientScreen()
    {
        clsListClientScreen::showListClientScreen();
    };

    static void _showAddClientScreen()
    {
        clsAddNewClientScreen::showAddNewClientScreen();
    };

    static void _showUpdateClientScreen()
    {
        clsUpdateClientScreen::showUpdateClientScreen();
    };

    static void _showDeleteClientScreen()
    {
        clsDeleteClientScreen::showDeleteClientScreen();
    };

    static void _showFindClientScreen()
    {
        clsFindClientScreen::showFindClientScreen();
    };

    static void _showClientTransactionsScreen()
    {
        clsTransactionScreen::showTransactionScreen();
    };

    static void _showManageUsersScreen()
    {
        clsManageUsersScreen::showManageUsersScreen();
    };

    static void _showLoginRegisterScreen()
    {
        clsLoginRegisterListScreen::showLoginRegisterListScreen();
    };

    static void _showCurrencyExchangeMainScreen()
    {
        clsCurrencyMainScreen::showMainScreen();
    };

    static void _logout()
    {
        currentUser = clsUser::find("", "");
    };

    static void _performMainMenuOption(enMainMenuOptions option)
    {
        switch (option)
        {
        case enMainMenuOptions::eListClient:
            _showListClientScreen();
            break;
        case enMainMenuOptions::eAddClient:
            _showAddClientScreen();
            break;
        case enMainMenuOptions::eUpdateClient:
            _showUpdateClientScreen();
            break;
        case enMainMenuOptions::eDeleteClient:
            _showDeleteClientScreen();
            break;
        case enMainMenuOptions::eFindClient:
            _showFindClientScreen();
            break;
        case enMainMenuOptions::eTransactions:
            _showClientTransactionsScreen();
            break;
        case enMainMenuOptions::eManageUsers:
            _showManageUsersScreen();
            break;
        case enMainMenuOptions::eShowLoginRegister:
            _showLoginRegisterScreen();
            break;
        case enMainMenuOptions::eCurrencyExchange:
            _showCurrencyExchangeMainScreen();
            break;

        default:
            _logout();
            break;
        }
    };

public:
    static void showMainMenu()
    {
        enMainMenuOptions optionToPerform = enMainMenuOptions::eLogout;
        do
        {
            clsUtil::clearConsoleScreen();
            _drawScreenHeader("\t\tMain screen");
            cout << left << "================================================\n";
            cout << left << "\t\tMain menu screen\n";
            cout << left << "================================================\n";
            cout << left << "\t\t[1] Show client list\n";
            cout << left << "\t\t[2] Add new client\n";
            cout << left << "\t\t[3] Update client info\n";
            cout << left << "\t\t[4] Delete client\n";
            cout << left << "\t\t[5] Find client\n";
            cout << left << "\t\t[6] Transactions\n";
            cout << left << "\t\t[7] Manage Users\n";
            cout << left << "\t\t[8] Login Register\n";
            cout << left << "\t\t[9] Currency exchange\n";
            cout << left << "\t\t[10] Logout\n";
            cout << left << "================================================\n";

            cout << left << "Choose what you want to perform? [1 to 10]: ";
            optionToPerform = _readMainMenuOption();
            _performMainMenuOption(optionToPerform);
            if (optionToPerform != enMainMenuOptions::eLogout)
                clsUtil::waitForKeyPress(); // wait for key press for

        } while (optionToPerform != enMainMenuOptions::eLogout);
    };
};