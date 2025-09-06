/*
    UI - Total balances screen
*/
#pragma once
#include <iostream>
#include <vector>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:
    static void _printClientBalanceHeaderData()
    {
        cout << "\n_____________________________________________________________" << endl;
        cout << "| " << left << setw(15) << "Account Number"
             << "| " << left << setw(30) << "Client name"
             << "| " << left << setw(15) << "Balance";
        cout << endl;
        cout << "_____________________________________________________________" << endl;
    }

    static void _printClientBalanceInfo(clsBankClient client)
    {
        cout << "| " << setw(15) << left << client.accountNumber
             << "| " << setw(30) << left << client.fullName()
             << "| " << setw(12) << left << client.balance;
        cout << endl;
    }

    static void _showTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::getAllClients();

        if (vClients.size() == 0)
        {
            cout << "_____________________________________________________________________________________" << endl;
            cout << "\t\t\t\tNo clients available in the system!" << endl;
            cout << "_____________________________________________________________________________________" << endl;
        }
        else
        {
            cout << "\n\t\tClient list (" << vClients.size() << ") clinet(s)" << endl;
            _printClientBalanceHeaderData();

            double totalBalances = clsBankClient::getTotalClientsBalances();
            for (const clsBankClient &c : vClients)
            {
                _printClientBalanceInfo(c);
            }
            cout << "_____________________________________________________________" << endl;
            cout << "Total clients balance = " << totalBalances << " ";
            cout << '(' << clsUtil::numberToText(totalBalances) << ')' << '\n'
                 << endl;
        }
    };

public:
    static void showTotalBalancesScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tTotal balances screen");
        _showTotalBalances();
    };
};