/*
    UI - Transfer log screen
*/

#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "../../Core/clsBankClient.h"
#include "../../Lib/clsUtil.h"
#include "../clsScreen.h"
#include "../../Lib/clsString.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
    struct _stTransferLog
    {
        string date;
        string time;
        string srcAccNum;
        string desAccNum;
        double transferAmount;
        double srcBalance;
        double desBalance;
        string transferOperator; // i.e. user who made the transfer between accounts
    };

    static _stTransferLog _convertLineRecordToTransferStruct(string recordLine, string separator = "#//#")
    {
        _stTransferLog log;
        vector<string> vRecord = clsString::split(recordLine, separator);
        vector<string> vDateTime = clsString::split(vRecord[0], " - ");
        log.date = vDateTime[0];
        log.time = vDateTime[1];
        log.srcAccNum = vRecord[1];
        log.desAccNum = vRecord[2];
        log.transferAmount = stod(vRecord[3]);
        log.srcBalance = stod(vRecord[4]);
        log.desBalance = stod(vRecord[5]);
        log.transferOperator = vRecord[6];
        return log;
    };

    static vector<_stTransferLog> _loadTransferLogRecords()
    {
        vector<_stTransferLog> vTransferLogs;
        fstream file;
        file.open("Data/TransferLogs.txt", ios::in); // read mode
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                vTransferLogs.push_back(_convertLineRecordToTransferStruct(line));
            }
            file.close();
        };
        return vTransferLogs;
    };

    static void _printTransferLogTableHeader()
    {
        cout << "________________________________________________________________________________________________________\n";
        cout << "| " << setw(20) << "Date - Time";
        cout << "| " << setw(12) << "src. acct.";
        cout << "| " << setw(12) << "des. acct.";
        cout << "| " << setw(12) << "Amount";
        cout << "| " << setw(12) << "src. amount";
        cout << "| " << setw(12) << "des. amount";
        cout << "| " << setw(12) << "User";
        cout << "\n________________________________________________________________________________________________________\n";
    };

    static void _printTransferLogRecord(_stTransferLog record)
    {
        cout << "| " << setw(20) << record.date + " - " + record.time;
        cout << "| " << setw(12) << record.srcAccNum;
        cout << "| " << setw(12) << record.desAccNum;
        cout << "| " << setw(12) << record.transferAmount;
        cout << "| " << setw(12) << record.srcBalance;
        cout << "| " << setw(12) << record.desBalance;
        cout << "| " << setw(12) << record.transferOperator;
        cout << endl;
    };

    static void _listTransferRecordOnScreen()
    {
        vector<_stTransferLog> vLogs = _loadTransferLogRecords();
        _printTransferLogTableHeader();
        for (_stTransferLog &record : vLogs)
        {
            _printTransferLogRecord(record);
        }
        cout << "\n________________________________________________________________________________________________________\n";
    };

public:
    static void showTransferLogScreen()
    {
        clsUtil::clearConsoleScreen();
        _drawScreenHeader("\t\tTransfer logs screen");
        _listTransferRecordOnScreen();
    };
};
