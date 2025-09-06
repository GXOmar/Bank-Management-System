/*
    UI - Delete user screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
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

    static void _runUserDeletionProccess()
    {
        string username = clsInputValidate::readString("Please enter a username: ");
        while (!clsUser::isUserExists(username))
        {
            username = clsInputValidate::readString("User with this username is not found! please enter a different one: ");
        };

        clsUser user = clsUser::find(username);
        _printUserCard(user);

        if (clsInputValidate::askYesOrNo("Are you sure you want to delete this clinet (Y/N)? "))
        {
            user.deleteUser();
        }

        _printUserCard(user);

        if (user.isInvalidUser())
        {
            cout << "\nUser deleted successfully" << endl;
        }
        else
        {
            cout << "\nUser was not deleted!" << endl;
        }
    };

public:
    static void showDeleteUserScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tDelete user screen");
        _runUserDeletionProccess();
    };
};