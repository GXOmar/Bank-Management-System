/*
    UI - Update user screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:
    static void _readUserData(clsUser &user)
    {
        user.firstName = clsInputValidate::readString("Enter first name: ");
        user.lastName = clsInputValidate::readString("Enter last name: ");
        user.email = clsInputValidate::readString("Enter email name: ");
        user.phoneNumber = clsInputValidate::readString("Enter phone name: ");
        user.password = clsInputValidate::readString("Enter password: ");
    };

    static void _readUserPermissions(clsUser &user)
    {
        cout << "\nChoose the permissions to grant this user\n";
        if (clsInputValidate::askYesOrNo("\nGrant full access to the system (Y/N)? "))
        {
            user.grantFullSystemAccessPermission();
        }
        else
        {
            user.revokeUserPermissions();
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

    static void _runUpdateUserProccess()
    {
        string username = clsInputValidate::readString("Please enter a username: ");
        while (!clsUser::isUserExists(username))
        {
            username = clsInputValidate::readString("User with this username not found, enter a different one: ");
        }
        clsUser user = clsUser::find(username);
        _printUserCard(user);

        if (clsInputValidate::askYesOrNo("Do you wish to update user information (Y/N)? "))
        {
            _readUserData(user);
            _readUserPermissions(user);
            clsUser::enSaveResult updateResult;
            updateResult = user.save();
            switch (updateResult)
            {
            case clsUser::enSaveResult::eSuccess:
                cout << "User data updated successfully" << endl;
                _printUserCard(user);
                break;

            default:
                cout << "User data couldn't be updated!" << endl;
                break;
            }
        }
        else
        {
            cout << "Update operation was canceled" << endl;
        }
    };

public:
    static void showUpdateUserScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tUpdate user screen");
        _runUpdateUserProccess();
    };
};
