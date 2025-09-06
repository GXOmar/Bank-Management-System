/*
    UI - Withdraw screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:
    static void _printClient(clsBankClient client)
    {
        cout << "\nClient Info\n";
        cout << "-------------------------------\n";
        cout << "First name: " << client.firstName << '\n';
        cout << "Last name: " << client.lastName << '\n';
        cout << "Full Name: " << client.fullName() << '\n';
        cout << "Email: " << client.email << '\n';
        cout << "Phone number: " << client.phoneNumber << '\n';
        cout << "Account number: " << client.accountNumber << '\n';
        cout << "PIN code: " << client.pinCode << '\n';
        cout << "Balance: " << client.balance << '\n';
        cout << "-------------------------------\n";
    };

    static void _withdrawFundsProccess()
    {
        string accountNumber = clsInputValidate::readString("Please enter an account number: ");
        while (!clsBankClient::isClientExists(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account not found, enter a different one: ");
        };

        clsBankClient client = clsBankClient::find(accountNumber);
        _printClient(client);

        cout << "\nEnter an amount to withdraw from client: ";
        double amount = clsInputValidate::readPositiveDblNumber();

        if (amount > client.balance)
        {
            cout << "\nInsufficient balance, couldn't withdraw amount" << '\n';
            cout << "The amount that can be withdrawn is: " << client.balance << '\n';
        }
        else if (clsInputValidate::askYesOrNo("Do you want to withdraw the amount (Y/N)? "))
        {
            if (client.withdraw(amount))
            {
                client.save();
                cout << "\nWithdraw successfully.\n";
                cout << "Your new balance: " << client.balance << endl;
            }
            else
            {
                cout << "Could not withdraw amount!" << endl;
            };
        }
        else
        {
            cout << "\nOperation was canceled." << endl;
        }
    };

public:
    static void showWithdrawScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tDeposit screen");
        _withdrawFundsProccess();
    };
};