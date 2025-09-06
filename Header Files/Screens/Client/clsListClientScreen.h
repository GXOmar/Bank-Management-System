/*
    UI - List client screen
*/

#pragma once

#include <iostream>
#include <iomanip>
#include "../../Core/clsUser.h"
#include "../../Core/clsBankClient.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"

using namespace std;

class clsListClientScreen : protected clsScreen
{
private:
    static void _printClientHeaderData()
    {
        cout << "________________________________________________________________________________________________________________" << endl
             << "| " << left << setw(15) << "Account Number"
             << "| " << left << setw(30) << "Client name"
             << "| " << left << setw(20) << "Email"
             << "| " << left << setw(10) << "PIN code"
             << "| " << left << setw(15) << "Phone"
             << "| " << left << setw(15) << "Balance";
        cout << endl;
        cout << "________________________________________________________________________________________________________________" << endl;
    };

    static void _printClientInfo(clsBankClient client)
    {
        cout << "| " << setw(15) << left << client.accountNumber
             << "| " << setw(30) << left << client.fullName()
             << "| " << setw(20) << left << client.email
             << "| " << setw(10) << left << client.pinCode
             << "| " << setw(15) << left << client.phoneNumber
             << "| " << setw(15) << left << client.balance;
        cout << endl;
    };

    static void _showClientsList()
    {
        vector<clsBankClient> vClients = clsBankClient::getAllClients();
        clsUtil::clearConsoleScreen();
        if (vClients.size() == 0)
        {
            cout << "________________________________________________________________________________________________________________" << endl;
            cout << "\t\tNo clients available in the system!" << endl;
            cout << "________________________________________________________________________________________________________________" << endl;
        }
        else
        {

            string title = "\tClient list screen";
            string subTitle = "\t(" + to_string(vClients.size()) + ")" + " client(s).";
            _drawScreenHeader(title, subTitle);

            _printClientHeaderData();
            for (clsBankClient &client : vClients)
            {
                _printClientInfo(client);
            }
            cout << "________________________________________________________________________________________________________________" << endl;
        }
    }

public:
    static void showListClientScreen()
    {
        if (checkAccessRights(clsUser::enPermissions::eListClients))
        {
            _showClientsList();
        }
        else
        {
            displayAccessDeniedScreen();
        };
    };
};
