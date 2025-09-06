/*
    UI - Manage users screen
*/
#pragma once
#include <iostream>
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenuOptions
    {
        eList = 1,
        eAdd = 2,
        eUpdate = 3,
        eDelete = 4,
        eFind = 5,
        eExit = 6
    };

    static enManageUsersMenuOptions _readManageUsersMenuOption()
    {
        return (enManageUsersMenuOptions)clsInputValidate::readIntNumberInRange(1, 6, "Invalid number, enter a number between 1 and 6: ");
    };

    static void _showListUsersScreen()
    {
        clsListUserScreen::showUsersListScreen();
    };

    static void _showAddUserScreen()
    {
        clsAddNewUserScreen::showAddNewUserScreen();
    };

    static void _showUpdateUserScreen()
    {
        clsUpdateUserScreen::showUpdateUserScreen();
    };

    static void _showDeleteUserScreen()
    {
        clsDeleteUserScreen::showDeleteUserScreen();
    };

    static void _showFindUserScreen()
    {
        clsFindUserScreen::showFindUserScreen();
    };

    static void _performManageUsersMenuOption(enManageUsersMenuOptions option)
    {
        switch (option)
        {
        case enManageUsersMenuOptions::eList:
            _showListUsersScreen();
            break;
        case enManageUsersMenuOptions::eAdd:
            _showAddUserScreen();
            break;
        case enManageUsersMenuOptions::eUpdate:
            _showUpdateUserScreen();
            break;
        case enManageUsersMenuOptions::eDelete:
            _showDeleteUserScreen();
            break;
        case enManageUsersMenuOptions::eFind:
            _showFindUserScreen();
            break;

        default:
            break; // eExit
        };
    };

    static void _printUserManagementScreen()
    {
        cout << "================================================\n";
        cout << "\t\tManage users menu screen\n";
        cout << "================================================\n";
        cout << "\t[1] List users\n";
        cout << "\t[2] Add new user\n";
        cout << "\t[3] Update user\n";
        cout << "\t[4] Delete user\n";
        cout << "\t[5] Find user\n";
        cout << "\t[6] Main menu\n";
        cout << "================================================\n";
    };

public:
    static void showManageUsersScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eManageUsers))
        {
            enManageUsersMenuOptions optionToPerform = enManageUsersMenuOptions::eExit;
            do
            {
                clsUtil::clearConsoleScreen();
                _drawScreenHeader("\t\tManage users screen");
                _printUserManagementScreen();
                cout << "Choose an option to perform [1 to 6]: ";
                optionToPerform = _readManageUsersMenuOption();
                if (optionToPerform == enManageUsersMenuOptions::eExit)
                    return;

                _performManageUsersMenuOption(optionToPerform);
                clsUtil::waitForKeyPress();
            } while (optionToPerform != enManageUsersMenuOptions::eExit);
        }
        else
        {
            displayAccessDeniedScreen();
            clsUtil::waitForKeyPress();
        };
    };
};