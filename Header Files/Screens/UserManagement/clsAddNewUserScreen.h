/*
    UI - Add new user screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
    static void _readNewUserData(clsUser &user)
    {
        user.firstName = clsInputValidate::readString("Enter first name: ");
        user.lastName = clsInputValidate::readString("Enter last name: ");
        user.email = clsInputValidate::readString("Enter email name: ");
        user.phoneNumber = clsInputValidate::readString("Enter phone name: ");
        user.password = clsInputValidate::readString("Enter password: ");
    };

    static void _readNewUserPermissions(clsUser &user)
    {
        cout << "\nChoose the permissions to grant this user\n";
        if (clsInputValidate::askYesOrNo("\nGrant full access to the system (Y/N)? "))
        {
            user.grantFullSystemAccessPermission();
        }
        else
        {
            if (clsInputValidate::askYesOrNo("\nGrant list clients permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eListClients);
            if (clsInputValidate::askYesOrNo("\nGrant add clients permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eAddClients);
            if (clsInputValidate::askYesOrNo("\nGrant update clients permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eUpdateClients);
            if (clsInputValidate::askYesOrNo("\nGrant delete clients permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eDeleteClients);
            if (clsInputValidate::askYesOrNo("\nGrant find clients permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eFindClients);
            if (clsInputValidate::askYesOrNo("\nGrant transactions permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eTransactions);
            if (clsInputValidate::askYesOrNo("\nGrant manage users permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eManageUsers);
            if (clsInputValidate::askYesOrNo("\nGrant show login logs permissions (Y/N)? "))
                user.grantUserPermission(clsUser::enPermissions::eShowLoginRegister);
        };
    };

    static void _printUserCard(clsUser user)
    {
        cout << "\nUser Info\n";
        cout << "-------------------------------\n";
        cout << "First name: " << user.firstName << '\n';
        cout << "Last name: " << user.lastName << '\n';
        cout << "Full Name: " << user.fullName() << '\n';
        cout << "Email: " << user.email << '\n';
        cout << "Phone number: " << user.phoneNumber << '\n';
        cout << "Username: " << user.username << '\n';
        cout << "Password: " << user.password << '\n';
        cout << "Permissions: " << user.permissions << '\n';
        cout << "-------------------------------" << endl;
    };

    static void _runAddNewUserProccess()
    {
        string username = clsInputValidate::readString("Enter a username for new user: ");
        while (clsUser::isUserExists(username))
        {
            username = clsInputValidate::readString("username already exists, enter a different one: ");
        };
        clsUser newUser = clsUser::getNewUserObject();
        newUser.username = username;
        _readNewUserData(newUser);
        _readNewUserPermissions(newUser);

        clsUser::enSaveResult saveResult;
        saveResult = newUser.save();

        switch (saveResult)
        {
        case clsUser::enSaveResult::eAdded:
            cout << "\nUser [" << newUser.username << "] added successfully." << endl;
            _printUserCard(newUser);
            break;

        default:
            cout << "\nFailed to create new user!" << endl;
            break;
        };
    };

public:
    static void showAddNewUserScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tAdd new user screen");
        _runAddNewUserProccess();
    };
};
