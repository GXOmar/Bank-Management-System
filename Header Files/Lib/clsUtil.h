/*
    -*- Custom Utility Library -*-
*/
#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:
    enum enNumberType
    {
        OOD = 1,
        EVEN = 2
    };

    enum enCharType
    {
        SMALL = 1,
        CAPITAL = 2,
        SPECIAL = 3,
        DIGITS = 4,
        MIX = 5
    };

    enum enPrimeOrNot
    {
        NotPrime,
        Prime
    };

    static enNumberType checkNumberType(int num)
    {
        return (num % 2 == 0) ? enNumberType::EVEN : enNumberType::OOD;
    };

    static void swap(int &x, int &y)
    {
        int temp = x;
        x = y;
        y = temp;
    };

    static void swap(float &x, float &y)
    {
        float temp = x;
        x = y;
        y = temp;
    };

    static void swap(double &x, double &y)
    {
        double temp = x;
        x = y;
        y = temp;
    };

    static void swap(string &s1, string &s2)
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    };

    static void swap(clsDate &date1, clsDate &date2)
    {
        clsDate tempDate = date1;
        date1 = date2;
        date2 = tempDate;
    };

    static enPrimeOrNot isPrime(int N)
    {
        int half_of_N = round(N / 2.0);
        for (int counter = 2; counter <= half_of_N; counter++)
        {
            if (N % counter == 0)
                return enPrimeOrNot::NotPrime;
        }
        return enPrimeOrNot::Prime;
    };

    static bool isPerfectNumber(int number)
    {
        int halfOfNumber = round(number / 2.0);
        int sumNumberDivisors = 0;
        for (int i = 1; i <= halfOfNumber; i++)
        {
            if (number % i == 0)
                sumNumberDivisors += i;
        }
        return sumNumberDivisors == number;
    };

    static int getDigitFrequencyInNumber(int number, int digit)
    {
        int digitFrequency = 0;
        int remainder = 0;
        while (number > 0)
        {
            remainder = number % 10;
            number /= 10;
            if (digit == remainder)
                digitFrequency += 1;
        }
        return digitFrequency;
    };

    static int reverseNumber(int number)
    {
        int remainder = 0, revNum = 0;
        while (number > 0)
        {
            remainder = number % 10;
            number = number / 10;
            revNum = revNum * 10 + remainder;
        }
        return revNum;
    };

    static bool isPalindromeNumber(int number)
    {
        return number == reverseNumber(number);
    };

    static string encrypt(string text, short encryptionKey)
    {
        string encryptedText = "";
        for (int i = 0; i < text.length(); i++)
        {
            encryptedText += char(text[i] + encryptionKey); // shifting to next X letters from original text
        }
        return encryptedText;
    };

    static string decrypt(string text, short encryptionKey)
    {
        string decryptedText = "";
        for (int i = 0; i < text.length(); i++)
        {
            decryptedText += char(text[i] - encryptionKey); // unshifting to previous X letters from encrypted text
        }
        return decryptedText;
    };

    static void generateSeedForRandomNumber()
    {
        srand((unsigned)time(NULL));
    };

    static int randomNumber(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    };

    static short randomDigit()
    {
        return rand() % 10;
    };

    static char getRandomCharacter(enCharType charType)
    {
        switch (charType)
        {
        case enCharType::SMALL:
            return char(randomNumber(97, 122));
        case enCharType::CAPITAL:
            return char(randomNumber(65, 90));
        case enCharType::SPECIAL:
            return char(randomNumber(33, 47));
        case enCharType::DIGITS:
            return char(randomNumber(48, 57));
        default:
            return getRandomCharacter((enCharType)randomNumber(1, 4));
        }
    };

    static string generateRandomKey(enCharType charType)
    {
        string randomKey = "";
        for (int i = 1; i <= 16; i++)
        {
            randomKey += getRandomCharacter(charType);
            if (i % 4 == 0 && i != 16)
                randomKey += '-';
        }
        return randomKey;
    };

    static string generateWord(enCharType charType, short length)
    {
        string Word;
        for (int i = 1; i <= length; i++)
        {
            Word = Word + getRandomCharacter(charType);
        }
        return Word;
    };

    static string generateKey()
    {
        string key = "";
        key = generateWord(enCharType::CAPITAL, 4) + "-";
        key += generateWord(enCharType::CAPITAL, 4) + "-";
        key += generateWord(enCharType::CAPITAL, 4) + "-";
        key += generateWord(enCharType::CAPITAL, 4);
        return key;
    };

    static void fillArrayWithRandomNumbers(int array[], int elementsToFill)
    {
        for (int i = 0; i < elementsToFill; i++)
            array[i] = randomNumber(1, 100);
    };

    static int getMaxNumberInArray(int array[], int arrayLength)
    {
        int maxValue = 0;
        for (int i = 0; i < arrayLength; i++)
            if (array[i] > maxValue)
                maxValue = array[i];
        return maxValue;
    };

    static int getMinNumberInArray(int array[], int arrayLength)
    {
        int minValue = array[0];
        for (int i = 0; i < arrayLength; i++)
            if (array[i] < minValue)
                minValue = array[i];
        return minValue;
    };

    static void shuffleArray(int arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            swap(arr[randomNumber(1, arrLength) - 1],
                 arr[randomNumber(1, arrLength) - 1]);
        }
    };

    static void fillArrayWithRandomKeys(string array[], int arrayLength)
    {
        for (int i = 0; i < arrayLength; i++)
            array[i] = generateKey();
    };

    static int findNumberIndexInArray(int array[], int arrayLength, int numberToSearch)
    {
        for (int i = 0; i < arrayLength; i++)
            if (array[i] == numberToSearch)
                return i;
        return -1;
    };

    static bool isNumberInArray(int array[], int arrayLength, int numberToSearch)
    {
        return findNumberIndexInArray(array, arrayLength, numberToSearch) != -1;
    };

    static bool isPositiveNumber(int number)
    {
        return number >= 0;
    };

    static bool isNegativeNumber(int number)
    {
        return number < 0;
    };

    static int countPositiveNumberInArray(int array[], int arrayLength)
    {
        int count = 0;
        for (int i = 0; i < arrayLength; i++)
            if (isPositiveNumber(array[i]))
                count++;
        return count;
    };

    static int countNegativeNumberInArray(int array[], int arrayLength)
    {
        int count = 0;
        for (int i = 0; i < arrayLength; i++)
            if (isNegativeNumber(array[i]))
                count++;
        return count;
    };

    static float myABS(float Number)
    {
        if (Number > 0)
            return Number;
        else
            return Number * -1;
    };

    static int myRound(float number)
    {
        int remainder = 0;
        float result = number;

        result = myABS(number); // convert negative to positive using absolute value: -10.7 = 10.7

        result *= 10;                 // 10.7 • 10 = 107
        remainder = int(result) % 10; // 107 % 10 = 7
        result /= 10;                 // 107 ÷ 10 = 10

        if (remainder >= 5)
            result++;
        if (number < 0)
            result *= -1;

        return result;
    };

    static int myFloor(float number)
    {
        if (number > 0)
            return int(number);
        else
            return int(number) - 1;
    };

    static float getFractionPart(float number)
    {
        return number - int(number); // 10.7 - 10 = return 0.7;
    }

    static void taps(short num)
    {
        for (short i = 0; i < num; i++)
        {
            cout << '\t';
        };
        cout << endl;
    };

    static string numberToText(int number)
    {
        if (number == 0)
            return "";

        else if (number >= 1 && number <= 19)
        {
            string arr[] = {
                "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
                "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
            return arr[number];
        }
        else if (number >= 20 && number <= 99)
        {
            string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return arr[number / 10] + ' ' + numberToText(number % 10);
        }
        else if (number >= 100 && number <= 999)
        {
            return numberToText(number / 100) + " Hundreds " + numberToText(number % 100);
        }
        else if (number >= 1000 && number <= 999999)
        {
            return numberToText(number / 1000) + " Thousands " + numberToText(number % 1000);
        }
        else if (number >= 1000000 && number <= 9999999)
        {
            return numberToText(number / 1000000) + " Millions " + numberToText(number % 1000000);
        }
        else if (number >= 1000000000 && number <= 1999999999)
        {
            return "One Billions " + numberToText(number % 1000000000);
        }
        else
        {
            return numberToText(number / 1000000000) + " Billions " + numberToText(number % 1000000000);
        }
    };

    static void clearConsoleScreen()
    {
        system("clear");
    };

    static void waitForKeyPress(string message = "Press any key to go back...")
    {
        cout << message << endl;
        system("read -n 1 -s -p ''; echo");
    };
};