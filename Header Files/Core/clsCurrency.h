/*
    Currency class
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "../Lib/clsString.h"

using namespace std;

class clsCurrency
{
private:
    enum enMode
    {
        eEmpty,
        eUpdate
    };
    enMode _mode;
    string _countryName;
    string _currencyName;
    string _currencyCode;
    float _rate;

    static clsCurrency _convertCurrencyRecordToObject(string record)
    {
        vector<string> vCurrency = clsString::split(record, "#//#");
        return clsCurrency(
            enMode::eUpdate,
            vCurrency.at(0),
            vCurrency.at(2),
            vCurrency.at(1),
            stof(vCurrency.at(3)));
    };

    static string _convertCurrencyObjectToRecord(clsCurrency currency, string recordSeparator = "#//#")
    {
        string s = "";
        s += currency._countryName + recordSeparator;
        s += currency._currencyCode + recordSeparator;
        s += currency._currencyName + recordSeparator;
        s += to_string(currency._rate);
        return s;
    };

    static vector<clsCurrency> _loadCurrenciesRecordsFromFile()
    {
        vector<clsCurrency> vCurrencies;
        fstream currenciesRecord;
        currenciesRecord.open("Data/Currencies.txt", ios::in); // read mode

        if (currenciesRecord.is_open())
        {
            string lineRecord;
            while (getline(currenciesRecord, lineRecord))
            {
                vCurrencies.push_back(_convertCurrencyRecordToObject(lineRecord));
            };
            currenciesRecord.close();
        }
        return vCurrencies;
    };

    static clsCurrency _getEmptyCurrencyObject()
    {
        return clsCurrency(enMode::eEmpty, "", "", "", 0.0);
    };

    void _update()
    {
        vector<clsCurrency> vCurrencies = _loadCurrenciesRecordsFromFile();
        for (clsCurrency &currency : vCurrencies)
        {
            if (currency._currencyCode == this->_currencyCode)
            {
                currency = *this;
                break;
            };
        }
        _saveCurrencyChangesToFile(vCurrencies);
    };

    void _saveCurrencyChangesToFile(vector<clsCurrency> vCurrencies)
    {
        fstream file;
        file.open("Data/Currencies.txt", ios::out); // write mode
        if (file.is_open())
        {
            for (clsCurrency &currency : vCurrencies)
            {
                file << _convertCurrencyObjectToRecord(currency) << endl;
            }
            file.close();
        }
    }

public:
    clsCurrency(enMode mode, string countryName, string currencyName, string currencyCode, float currencyRate)
    {
        _mode = mode;
        _countryName = countryName;
        _currencyName = currencyName;
        _currencyCode = currencyCode;
        _rate = currencyRate;
    };

    string getCountryName()
    {
        return _countryName;
    };

    string getCurrencyName()
    {
        return _currencyName;
    };

    string getCurrencyCode()
    {
        return _currencyCode;
    };

    float getRate()
    {
        return _rate;
    };

    void setRate(float newRate)
    {
        _rate = newRate; // reflect changes in memory of the object
        _update();       // reflect changes on persistent storage (i.e. file)
    };

    static vector<clsCurrency> getAllCurrencies()
    {
        return _loadCurrenciesRecordsFromFile();
    };

    bool isEmpty()
    {
        return _mode == enMode::eEmpty;
    };

    static bool isExists(clsCurrency currency)
    {
        return !currency.isEmpty();
    };

    bool isExists()
    {
        return isExists(*this);
    };

    bool isUSD()
    {
        return _currencyCode == "USD";
    };

    static float getUSDRate()
    {
        return findByCode("USD").getRate();
    };

    float convertToUSD(float amount)
    {
        return amount / this->_rate;
    };

    float convertTo(clsCurrency currency2, float amount)
    {
        float amountInUSD = convertToUSD(amount);

        if (currency2.isUSD())
            return amountInUSD;

        return amountInUSD * currency2._rate;
    };

    // Note: can't overload the two find methods here due to no unique signetares in number/type of parameters
    static clsCurrency findByCode(string currencyCode)
    {
        currencyCode = clsString::upperAllLetters(currencyCode);
        vector<clsCurrency> vCurrencies = getAllCurrencies();
        for (const clsCurrency &currency : vCurrencies)
        {
            if (currency._currencyCode == currencyCode)
            {
                return currency;
            }
        }
        // if no currency found, return empty object!
        return _getEmptyCurrencyObject();
    };

    static clsCurrency findByCountry(string countryName)
    {
        countryName = clsString::upperAllLetters(countryName);

        vector<clsCurrency> vCurrencies = getAllCurrencies();
        for (const clsCurrency &currency : vCurrencies)
        {
            if (clsString::upperAllLetters(currency._countryName) == countryName)
            {
                return currency;
            }
        }
        // if no currency found, return empty object!
        return _getEmptyCurrencyObject();
    };
};
