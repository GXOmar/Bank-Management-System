/*
    UI - Transfer screen
*/

#pragma once
#include <iostream>
#include "../../global.h"
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsInputValidate.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"
#include "../../Lib/clsLoggerRegister.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static void _printClient(clsBankClient client)
    {
        cout << "\nClient Info\n";
        cout << "-------------------------------\n";
        cout << "Full Name: " << client.fullName() << '\n';
        cout << "Account number: " << client.accountNumber << '\n';
        cout << "Balance: " << client.balance << '\n';
        cout << "-------------------------------\n";
    };

    static string _readAccountNumber(string message)
    {
        string accNum = clsInputValidate::readString(message);
        while (!clsBankClient::isClientExists(accNum))
        {
            accNum = clsInputValidate::readString("Account not found!, enter account number: ");
        }
        return accNum;
    };

    static double _readTransferAmount(clsBankClient sourceClient)
    {
        double amount;
        cout << "\nEnter transfer amount: ";
        amount = clsInputValidate::readPositiveDblNumber();
        while (!sourceClient.canWithdrawAmount(amount))
        {
            cout << "\nAmount exceeds the available balance, enter a different amount: ";
            amount = clsInputValidate::readPositiveDblNumber();
        }
        return amount;
    };

    static void _runTransferProccess()
    {

        clsBankClient sourceClient = clsBankClient::find(_readAccountNumber("Enter account number to transfer from: "));
        _printClient(sourceClient);

        clsBankClient destinationClinet = clsBankClient::find(_readAccountNumber("\nEnter account number to transfer to: "));
        _printClient(destinationClinet);

        double amountToTransfer = _readTransferAmount(sourceClient);

        if (clsInputValidate::askYesOrNo("Are you sure you want to perform this transfer operation (Y/N)? "))
        {
            if (sourceClient.transfer(amountToTransfer, destinationClinet))
            {
                sourceClient.save();
                destinationClinet.save();

                cout << "\nTransfer Done successfully\n";
                _printClient(sourceClient);
                _printClient(destinationClinet);

                clsLoggerRegister::logTransfer(
                    sourceClient.accountNumber,
                    destinationClinet.accountNumber,
                    amountToTransfer,
                    sourceClient.balance,
                    destinationClinet.balance,
                    currentUser.username);
            }
            else
            {
                cout << "\nCould not make a transfer!" << endl;
            }
        }
        else
        {
            cout << "\nTransfer operation was canceled" << endl;
        }
    }

public:
    static void showTransferScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tTransfer screen");
        _runTransferProccess();
    };
};