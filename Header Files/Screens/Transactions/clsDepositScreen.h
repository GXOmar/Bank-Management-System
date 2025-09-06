/*
    UI - Deposit screen
*/
#pragma once
#include <iostream>
#include "../../Core/clsBankClient.h"
#include "../clsScreen.h"
#include "../../Lib/clsUtil.h"
#include "../../Lib/clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

    static void _depositFundsProccess()
    {
        string accountNumber = clsInputValidate::readString("Please enter an account number: ");
        while (!clsBankClient::isClientExists(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account not found, enter a different one: ");
        };

        clsBankClient client = clsBankClient::find(accountNumber);
        _printClient(client);

        cout << "\nEnter an amount to deposit to client: ";
        double amount = clsInputValidate::readPositiveDblNumber();

        if (clsInputValidate::askYesOrNo("Do you want to deposit the amount (Y/N)? "))
        {
            client.deposit(amount);
            client.save();
            cout << "\nDeposited successfully.\n";
            cout << "New balance = " << client.balance << endl;
        };
    };

public:
    static void showDepositScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tDeposit screen");
        _depositFundsProccess();
    };
};