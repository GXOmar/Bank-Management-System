/*
    Log register class
*/

#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include "clsDate.h"
#include "clsUtil.h"

class clsLoggerRegister
{
private:
    struct _stTime
    {
        int hour, minutes, seconds;
    };

    static clsDate _getCurrentDate()
    {
        return clsDate::getSystemDate();
    };

    static _stTime _getCurrentTime()
    {
        time_t t = time(0); // get time now
        tm *now = localtime(&t);
        _stTime currentTime;
        currentTime.hour = now->tm_hour;
        currentTime.minutes = now->tm_min;
        currentTime.seconds = now->tm_sec;
        return currentTime;
    };

    static string _timeToString(_stTime t, string separator = ":")
    {
        return to_string(t.hour) + separator + to_string(t.minutes) + separator + to_string(t.seconds);
    };

    static string _getLoginLogRecordLine(string username, string password, int permissions, string recordSeparator = "#//#")
    {
        string record = "";
        clsDate date = _getCurrentDate();
        _stTime logTime = _getCurrentTime();

        record += date.dateToString();
        record += " - ";
        record += _timeToString(logTime);
        record += recordSeparator;
        record += username + recordSeparator;
        record += clsUtil::encrypt(password, 2) + recordSeparator;
        record += to_string(permissions);
        return record;
    };

    static string _getTransferLogRecordLine(string srcAccNum, string desAccNum, double transferAmount, double srcBalance, double desBalance, string loggedInUsername, string recordSeparator = "#//#")
    {
        string record = "";
        clsDate date = _getCurrentDate();
        _stTime logTime = _getCurrentTime();

        record += date.dateToString();
        record += " - ";
        record += _timeToString(logTime);
        record += recordSeparator;

        record += srcAccNum + recordSeparator;
        record += desAccNum + recordSeparator;
        record += to_string(transferAmount) + recordSeparator;
        record += to_string(srcBalance) + recordSeparator;
        record += to_string(desBalance) + recordSeparator;
        record += loggedInUsername;
        return record;
    };

    static void _writeToLogFile(string logEntry, string filePath)
    {
        fstream logFile;
        logFile.open(filePath, ios::out | ios::app); // write/append mode
        if (logFile.is_open())
        {
            logFile << logEntry << endl;
            logFile.close();
        }
    };

public:
    static void logLogin(string username, string password, int permissions)
    {
        _writeToLogFile(_getLoginLogRecordLine(username, password, permissions), "Data/LoginRegister.txt");
    };

    static void logTransfer(string srcAccNum, string desAccNum, double amount, double srcBalance, double desBalance, string loggedInUsername)
    {
        _writeToLogFile(_getTransferLogRecordLine(srcAccNum, desAccNum, amount, srcBalance, desBalance, loggedInUsername), "Data/TransferLogs.txt");
    };
};
