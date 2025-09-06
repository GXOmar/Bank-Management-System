/*
    UI - List users screen
*/
#pragma once
#include <iostream>
#include <iomanip>
#include "../../Core/clsUser.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"

class clsListUserScreen : protected clsScreen
{
private:
    static void _printUsersRecordsHeader()
    {
        cout << "\n___________________________________________________________________________________________________________\n"
             << "| " << setw(15) << left << "First name"
             << "| " << setw(15) << left << "Last name"
             << "| " << setw(20) << left << "Email"
             << "| " << setw(12) << left << "Phone number"
             << "| " << setw(10) << left << "Username"
             << "| " << setw(10) << left << "Password"
             << "| " << setw(10) << left << "Permissions"
             << "\n___________________________________________________________________________________________________________\n";
    };

    static void _printUserDataRecord(clsUser user)
    {
        cout << "| " << setw(15) << left << user.firstName
             << "| " << setw(15) << left << user.lastName
             << "| " << setw(20) << left << user.email
             << "| " << setw(12) << left << user.phoneNumber
             << "| " << setw(10) << left << user.username
             << "| " << setw(10) << left << user.password
             << "| " << setw(10) << left << user.permissions
             << endl;
    };

    static void _runListUsersProccess()
    {
        vector<clsUser> vUsers = clsUser::getAllUsers();
        if (vUsers.size() == 0)
        {
            cout << "There are no users in the system!" << endl;
        }
        else
        {
            cout << "\t\t\t\t\t\t(" + to_string(vUsers.size()) + ")" + " user(s).";
            _printUsersRecordsHeader();
            for (clsUser &user : vUsers)
            {
                _printUserDataRecord(user);
            }
            cout << "___________________________________________________________________________________________________________\n";
        }
    };

public:
    static void showUsersListScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tList users screen");
        _runListUsersProccess();
    };
};