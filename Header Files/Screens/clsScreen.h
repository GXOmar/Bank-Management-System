#pragma once
#include <iostream>
#include "../global.h"
#include "../Core/clsUser.h"
#include "../Lib/clsUtil.h"
#include "../Lib/clsDate.h"

using namespace std;

class clsScreen
{
    // clsScreen will be inherited by all other screens in the system
private:
    static void _showLoggedInUser()
    {
        cout << "User: " << currentUser.username;
    };

    static void _showCurrentDate()
    {
        cout << "Date: " << clsDate::dateToString(clsDate());
    };

protected:
    static void _drawScreenHeader(string title, string subTitle = "")
    {
        cout << "\n________________________________________________\n";
        cout << "" << title << '\n';
        if (subTitle != "")
            cout << "" << subTitle << '\n';
        cout << "________________________________________________\n\n";
        cout << "\t";
        _showLoggedInUser();
        cout << " | ";
        _showCurrentDate();
        cout << endl
             << endl;
    };

    static bool checkAccessRights(clsUser::enPermissions permission)
    {
        return currentUser.hasPermission(permission); // validate the currently logged in user can access/view certain screens
    };

    static void displayAccessDeniedScreen()
    {
        clsUtil::clearConsoleScreen();
        cout << "________________________________________________________________________\n";
        cout << "\tAccess Denied! please contact your administration department.\n";
        cout << "________________________________________________________________________\n";
    };
};