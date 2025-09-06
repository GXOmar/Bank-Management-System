/*
    UI - Find user screen
*/

#pragma once
#include <iostream>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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

    static void _runFindUserProccess()
    {
        string username = clsInputValidate::readString("Enter a username: ");
        while (!clsUser::isUserExists(username))
        {
            username = clsInputValidate::readString("User with this username is not found, enter a different one: ");
        }
        clsUser user = clsUser::find(username);
        if (user.isUserExists())
        {
            cout << "\nUser found!\n";
            _printUserCard(user);
        }
        else
        {
            cout << "\nUser was not found!\n";
        }
    };

public:
    static void showFindUserScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tFind user screen");
        _runFindUserProccess();
    };
};
