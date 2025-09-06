/*
    -*- Custom Date Library -*-
*/
#pragma once

#include <iostream>
#include <iomanip>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
    int _day;
    int _month;
    int _year;

public:
    enum enDateComparison
    {
        BEFORE = -1,
        EQUAL = 0,
        AFTER = 1
    };
    // default constructor
    clsDate()
    {
        // get current system time
        time_t t = time(0); // get time now
        tm *now = localtime(&t);

        _year = now->tm_year + 1900;
        _month = now->tm_mon + 1;
        _day = now->tm_mday;
    };

    clsDate(string date)
    {
        vector<string> vDate = clsString::split(date, "/");
        _day = stoi(vDate[0]);
        _month = stoi(vDate[1]);
        _year = stoi(vDate[2]);
    };

    clsDate(short day, short month, short year)
    {
        _day = day;
        _month = month;
        _year = year;
    };

    clsDate(short daysFromBeginningOfYear, short year)
    {
        *this = getDateFromTotalDaysInYear(daysFromBeginningOfYear, year);
    };

    void setDay(int day)
    {
        _day = day;
    };

    int getDay()
    {
        return _day;
    };

    void setMonth(int month)
    {
        _month = month;
    };

    int getMonth()
    {
        return _month;
    };

    void setYear(int year)
    {
        _year = year;
    };

    int getYear()
    {
        return _year;
    };

    __declspec(property(get = getDay, put = setDay)) int day;
    __declspec(property(get = getMonth, put = setMonth)) int month;
    __declspec(property(get = getYear, put = setYear)) int year;

    static bool isLeapYear(short year)
    {
        return (((year % 4 == 0) && (year % 100 != 0)) || ((year % 400 == 0)));
    };

    bool isLeapYear()
    {
        return isLeapYear(_year);
    };

    static short daysInYear(short year)
    {
        return isLeapYear(year) ? 366 : 365;
    };

    short daysInYear()
    {
        return daysInYear(_year);
    };

    static short hoursInYear(short year)
    {
        return daysInYear(year) * 24;
    };

    short hoursInYear()
    {
        return hoursInYear(_year);
    };

    static int minutesInYear(short year)
    {
        return hoursInYear(year) * 60;
    };

    int minutesInYear()
    {
        return minutesInYear(_year);
    };

    static int secondsInYear(short year)
    {
        return minutesInYear(year) * 60;
    };

    int secondsInYear()
    {
        return secondsInYear(_year);
    };

    static short daysInMonth(short month, short year)
    {
        short arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (month < 1 || month > 12) ? 0 : (month == 2) ? isLeapYear(year) ? 29 : 28
                                                            : arr[month - 1];
    };

    short daysInMonth()
    {
        return daysInMonth(_month, _year);
    };

    static short hoursInMonth(short month, short year)
    {
        return daysInMonth(month, year) * 24;
    };

    short hoursInMonth()
    {
        return hoursInMonth(_month, _year);
    };

    static int minutesInMonth(short month, short year)
    {
        return hoursInMonth(month, year) * 60;
    };

    int minutesInMonth()
    {
        return minutesInMonth(_month, _year);
    };

    static int secondsInMonth(short month, short year)
    {
        return minutesInMonth(month, year) * 60;
    };

    int secondsInMonth()
    {
        return secondsInMonth(_month, _year);
    };

    static string dayName(short dayOfWeekOrder)
    {
        string dayNames[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return dayNames[dayOfWeekOrder];
    };

    string dayName()
    {
        return dayName(dayOfAWeek());
    };

    static string monthName(short monthNumber)
    {
        string monthsName[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return monthsName[monthNumber - 1];
    };

    string monthName()
    {
        return monthName(_month);
    };

    static short dayOfAWeek(short day, short month, short year)
    {
        short a = (14 - month) / 12;
        short y = year - a;
        short m = month + 12 * a - 2;

        // For the Gregorian calendar:
        short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
        return d;
    };

    static short dayOfAWeek(clsDate date)
    {
        return dayOfAWeek(date.day, date.month, date.year);
    };

    short dayOfAWeek()
    {
        return dayOfAWeek(*this);
    };

    static void printMonthCalendar(short month, short year)
    {
        // indexing days starting from 0 for sunday, upto 6 for saturday
        short startingDayOfWeek = dayOfAWeek(1, month, year);
        short numberOfDays = daysInMonth(month, year);

        cout << "______________" << monthName(month) << "________________" << endl;
        for (short d = 0; d < 7; d++)
            cout << left << setw(5) << dayName(d);
        cout << endl;

        short i;
        for (i = 0; i < startingDayOfWeek; i++)
            cout << setw(5) << ""; // print empty spaces upto the starting day of the month

        for (short j = 1; j <= numberOfDays; j++)
        {
            cout << setw(3) << right << j << "  ";
            if (++i == 7)
            {
                cout << endl;
                i = 0;
            }
        }
        cout << "\n_________________________________\n"
             << endl;
    };

    void printMonthCalendar()
    {
        printMonthCalendar(this->month, this->year);
    };

    static void printYearCalendar(short year)
    {
        cout << "\n_________________________________\n\n";
        cout << "\tCalendar - " << year;
        cout << "\n_________________________________\n\n";

        for (short i = 1; i <= 12; i++)
        {
            printMonthCalendar(i, year);
        }
    };

    void printYearCalendar()
    {
        printYearCalendar(this->year);
    };

    static short daysFromTheBeginingOfYear(short day, short month, short year)
    {
        short totalDays = 0;
        for (short i = 1; i <= month; i++)
            totalDays += daysInMonth(i, year);

        // fixing if day > the daysInMonth, then it will not be added to the totalDays
        short dayDiff = day > daysInMonth(month, year) ? 0 : daysInMonth(month, year) - day;
        return totalDays - dayDiff;
    };

    short daysFromTheBeginingOfYear()
    {
        return daysFromTheBeginingOfYear(_day, _month, _year);
    };

    static clsDate getDateFromTotalDaysInYear(short totalDaysInYear, short year)
    {
        clsDate date;
        date.year = year;
        date.month = 1;
        short remainingDays = totalDaysInYear, monthDays = 0;
        while (true)
        {
            monthDays = daysInMonth(date.month, date.year);
            if (remainingDays > monthDays)
            {
                remainingDays -= monthDays;
                date.month++;
            }
            else
            {
                date.day = remainingDays;
                break;
            }
        }
        return date;
    };

    void addDaysToDate(short days)
    {
        // 10/10/2022 [in days] + 2500 days = 14/8/2029
        short remainingDays = daysFromTheBeginingOfYear() + days;
        short monthDays = 0;
        _month = 1;
        while (true)
        {
            monthDays = daysInMonth();
            if (remainingDays > monthDays)
            {
                remainingDays -= monthDays;
                _month++;
                if (_month > 12)
                {
                    _month = 1;
                    _year++;
                }
            }
            else
            {
                _day = remainingDays;
                break;
            }
        };
    };

    static bool isDate1LessThanDate2(clsDate date1, clsDate date2)
    {
        return (date1.year < date2.year) ? true : (date1.month < date2.month) ? true
                                                                              : date1.day < date2.day;
    };

    bool isDateLessThanDate2(clsDate date2)
    {
        // send the current object to the function via *this pointer.
        return isDate1LessThanDate2(*this, date2);
    };

    static bool isDate1EqualDate2(clsDate date1, clsDate date2)
    {
        return (date1.year != date2.year)     ? false
               : (date1.month != date2.month) ? false
               : (date1.day != date2.day)     ? false
                                              : true;
    };

    bool isDateEqualToDate2(clsDate date2)
    {
        return isDate1EqualDate2(*this, date2);
    };

    static bool isLastDayInMonth(clsDate date)
    {
        return date.day == daysInMonth(date.month, date.year);
    };

    bool isLastDayInMonth()
    {
        return isLastDayInMonth(*this);
    };

    static bool isLastMonthInYear(clsDate date)
    {
        return date.month == 12;
    };

    bool isLastMonthInYear()
    {
        return isLastMonthInYear(*this);
    };

    static bool isFirstDayInMonth(clsDate date)
    {
        return date.day == 1;
    };

    bool isFirstDayInMonth()
    {
        return isFirstDayInMonth(*this);
    };

    static bool isFirstMonthInYear(clsDate date)
    {
        return date.month == 1;
    };

    bool isFirstMonthInYear()
    {
        return isFirstMonthInYear(*this);
    };

    static void increaseDateByOneDay(clsDate &date)
    {
        if (isLastDayInMonth(date))
        {
            if (isLastMonthInYear(date))
            {
                date.day = 1;
                date.month = 1;
                date.year++;
            }
            else
            {
                date.day = 1;
                date.month++;
            }
        }
        else
        {
            date.day++;
        }
    };

    void increaseDateByOneDay()
    {
        increaseDateByOneDay(*this);
    };

    static void swapDates(clsDate &date1, clsDate &date2)
    {
        clsDate tempDate;
        tempDate.year = date1.year;
        tempDate.month = date1.month;
        tempDate.day = date1.day;

        date1.year = date2.year;
        date1.month = date2.month;
        date1.day = date2.day;

        date2.year = tempDate.year;
        date2.month = tempDate.month;
        date2.day = tempDate.day;
    };

    void swapDates(clsDate &date)
    {
        swapDates(*this, date);
    };

    static int diffDaysBetweenTwoDates(clsDate date1, clsDate date2, bool includeEndDay = false)
    {
        int days = 0;
        short swapDaysFlag = 1;
        if (!isDate1LessThanDate2(date1, date2))
        {
            swapDates(date1, date2);
            swapDaysFlag = -1;
        }
        while (isDate1LessThanDate2(date1, date2))
        {
            days++;
            increaseDateByOneDay(date1);
        }
        return includeEndDay ? ++days * swapDaysFlag : days * swapDaysFlag;
    };

    int diffDaysBetweenDate2(clsDate date2, bool includeEndDay = false)
    {
        return diffDaysBetweenTwoDates(*this, date2, includeEndDay);
    };

    static int calculateAgeInDays(clsDate date, bool includeEndDay = false)
    {
        return diffDaysBetweenTwoDates(date, getSystemDate(), includeEndDay);
    };

    int calculateMyAgeInDays(bool includeEndDay = false)
    {
        return calculateAgeInDays(*this, includeEndDay);
    };

    static clsDate getSystemDate()
    {
        clsDate date;
        time_t t = time(0); // get time now
        tm *now = localtime(&t);

        date.year = now->tm_year + 1900;
        date.month = now->tm_mon + 1;
        date.day = now->tm_mday;
        return date;
    };

    void print()
    {
        cout << dateToString() << endl;
    };

    static void increaseDateByXDays(clsDate &date, int days)
    {
        for (int day = 1; day <= days; day++)
            increaseDateByOneDay(date);
    };

    void increaseDateByXDays(int days)
    {
        increaseDateByXDays(*this, days);
        // this way or
        // for (int day = 1; day <= days; day++)
        //     increaseDateByOneDay();
    };

    static void increaseDateByOneWeek(clsDate &date)
    {
        increaseDateByXDays(date, 7);
    };

    void increaseDateByOneWeek()
    {
        increaseDateByOneWeek(*this);
    };

    static void increaseDateByXWeeks(clsDate &date, int weeks)
    {
        for (int week = 1; week <= weeks; week++)
            increaseDateByOneWeek(date);
    };

    void increaseDateByXWeeks(int weeks)
    {
        increaseDateByXWeeks(*this, weeks);
    };

    static void increaseDateByOneMonth(clsDate &date)
    {
        if (isLastMonthInYear(date))
        {
            date.month = 1;
            date.year++;
        }
        else
            date.month++;

        short maxDaysInNewMonth = daysInMonth(date.month, date.year);
        if (date.day > maxDaysInNewMonth)
            date.day = maxDaysInNewMonth;
    };

    void increaseDateByOneMonth()
    {
        increaseDateByOneMonth(*this);
    };

    static void increaseDateByXMonths(clsDate &date, int months)
    {
        for (int month = 1; month <= months; month++)
            increaseDateByOneMonth(date);
    };

    void increaseDateByXMonths(int months)
    {
        increaseDateByXMonths(*this, months);
    };

    static void increaseDateByOneYear(clsDate &date)
    {
        date.year++;
        short daysInMonthOfNewYear = daysInMonth(date.month, date.year);
        if (date.day > daysInMonthOfNewYear)
            date.day = daysInMonthOfNewYear;
    };

    void increaseDateByOneYear()
    {
        increaseDateByOneYear(*this);
    };

    static void increaseDateByXYears(clsDate &date, int years)
    {
        clsDate ogDate = date;
        for (int year = 1; year <= years; year++)
            increaseDateByOneYear(date);
        if (isLeapYear(date.year) && date.month == 2)
        {
            if ((ogDate.day == 29) && date.day == 28)
                date.day = 29;
        }
    };

    void increaseDateByXYears(int years)
    {
        increaseDateByXYears(*this, years);
    };

    static void increaseDateByXYearsFaster(clsDate &date, int years)
    {
        date.year += (years - 1);
        increaseDateByOneYear(date); // handle leap year
    };

    void increaseDateByXYearsFaster(int years)
    {
        increaseDateByXYearsFaster(*this, years);
    };

    static void increaseDateByOneDecade(clsDate &date)
    {
        increaseDateByXYearsFaster(date, 10);
    }

    void increaseDateByOneDecade()
    {
        increaseDateByOneDecade(*this);
    };

    static void increaseDateByXDecades(clsDate &date, int decades)
    {
        for (int decade = 1; decade <= decades; decade++)
            increaseDateByOneDecade(date);
    };

    void increaseDateByXDecades(int decades)
    {
        increaseDateByXDecades(*this, decades);
    };

    static void increaseDateByXDecadesFaster(clsDate &date, int decades)
    {
        date.year += (decades * 10 - 10);
        increaseDateByOneDecade(date); // handle leap year
    };

    void increaseDateByXDecadesFaster(int decades)
    {
        increaseDateByXDecadesFaster(*this, decades);
    };

    static void increaseDateByOneCentury(clsDate &date)
    {
        increaseDateByXYearsFaster(date, 100);
    };

    void increaseDateByOneCentury()
    {
        increaseDateByOneCentury(*this);
    };

    static void increaseDateByOneMillennium(clsDate &date)
    {
        increaseDateByXYearsFaster(date, 1000);
    };

    void increaseDateByOneMillennium()
    {
        increaseDateByOneMillennium(*this);
    };

    static void decreaseDateByOneDay(clsDate &date)
    {
        if (isFirstDayInMonth(date))
        {
            if (isFirstMonthInYear(date))
            {
                date.year--;
                date.month = 12;
                date.day = daysInMonth(date.month, date.year);
            }
            else
            {
                date.month--;
                date.day = daysInMonth(date.month, date.year);
            }
        }
        else
        {
            date.day--;
        }
    };

    void decreaseDateByOneDay()
    {
        decreaseDateByOneDay(*this);
    };

    static void decreaseDateByXDays(clsDate &date, int days)
    {
        for (int day = days; day >= 1; day--)
            decreaseDateByOneDay(date);
    };

    void decreaseDateByXDays(int days)
    {
        decreaseDateByXDays(*this, days);
    };

    static void decreaseDateByOneWeek(clsDate &date)
    {
        decreaseDateByXDays(date, 7);
    };

    void decreaseDateByOneWeek()
    {
        decreaseDateByOneWeek(*this);
    };

    static void decreaseDateByXWeeks(clsDate &date, int weeks)
    {
        for (int week = weeks; week >= 1; week--)
            decreaseDateByOneWeek(date);
    };

    void decreaseDateByXWeeks(int weeks)
    {
        decreaseDateByXWeeks(*this, weeks);
    };

    static void decreaseDateByOneMonth(clsDate &date)
    {
        if (date.month == 1)
        {
            date.year--;
            date.month = 12;
        }
        else
            date.month--;

        short daysInNewMonth = daysInMonth(date.month, date.year);
        if (date.day > daysInNewMonth)
            date.day = daysInNewMonth;
    };

    void decreaseDateByOneMonth()
    {
        decreaseDateByOneMonth(*this);
    };

    static void decreaseDateByXMonths(clsDate &date, int months)
    {
        for (int month = months; month >= 1; month--)
            decreaseDateByOneMonth(date);
    };

    void decreaseDateByXMonths(int months)
    {
        decreaseDateByXMonths(*this, months);
    };

    static void decreaseDateByOneYear(clsDate &date)
    {
        date.year--;
        short daysInMonthOfNewYear = daysInMonth(date.month, date.year);

        if (date.day > daysInMonthOfNewYear)
            date.day = daysInMonthOfNewYear;
    };

    void decreaseDateByOneYear()
    {
        decreaseDateByOneYear(*this);
    };

    static void decreaseDateByXYears(clsDate &date, int years)
    {
        clsDate ogDate = date;
        for (int year = years; year >= 1; year--)
            decreaseDateByOneYear(date);

        if (isLeapYear(date.year) && date.month == 2)
        {
            // Handle decreasing from a leap year to another leap year
            if ((ogDate.day == 29) && (date.day == 28))
                date.day = 29;
        }
    };

    void decreaseDateByXYears(int years)
    {
        decreaseDateByXYears(*this, years);
    };

    static void decreaseDateByXYearsFaster(clsDate &date, int years)
    {
        date.year -= (years - 1);
        decreaseDateByOneYear(date); // handle leap year
    };

    void decreaseDateByXYearsFaster(int years)
    {
        decreaseDateByXYearsFaster(*this, years);
    };

    static void decreaseDateByOneDecade(clsDate &date)
    {
        decreaseDateByXYearsFaster(date, 10);
    };

    void decreaseDateByOneDecade()
    {
        decreaseDateByOneDecade(*this);
    };

    static void decreaseDateByXDecades(clsDate &date, int decades)
    {
        for (int decade = decades; decade >= 1; decade--)
            decreaseDateByOneDecade(date);
    };

    void decreaseDateByXDecades(int decades)
    {
        decreaseDateByXDecades(*this, decades);
    };

    static void decreaseDateByXDecadesFaster(clsDate &date, int decades)
    {
        date.year -= (decades * 10 - 10);
        decreaseDateByOneDecade(date); // handle leap year
    };

    static void decreaseDateByOneCentury(clsDate &date)
    {
        decreaseDateByXYearsFaster(date, 100);
    };

    void decreaseDateByOneCentury()
    {
        decreaseDateByOneCentury(*this);
    };

    static void decreaseDateByOneMillennium(clsDate &date)
    {
        decreaseDateByXYearsFaster(date, 1000);
    };

    void decreaseDateByOneMillennium()
    {
        decreaseDateByOneMillennium(*this);
    };

    static bool isEndOfWeek(clsDate date)
    {
        // End of week is saturday
        return dayOfAWeek(date) == 6;
    };

    bool isEndOfWeek()
    {
        return isEndOfWeek(*this);
    };

    static bool isWeekend(clsDate date)
    {
        short dayOrder = dayOfAWeek(date);
        return (dayOrder == 5 || dayOrder == 6);
    };

    bool isWeekend()
    {
        return isWeekend(*this);
    };

    static bool isBusinessDay(clsDate date)
    {
        return !isWeekend(date);
    };

    bool isBusinessDay()
    {
        return isBusinessDay(*this);
    };

    static short daysUntilEndOfWeek(clsDate date)
    {
        return 6 - dayOfAWeek(date);
    };

    short daysUntilEndOfWeek()
    {
        return daysUntilEndOfWeek(*this);
    };

    static short daysUntilEndOfMonth(clsDate date)
    {
        return daysInMonth(date.month, date.year) - date.day;
    };

    short daysUntilEndOfMonth()
    {
        return daysUntilEndOfMonth(*this);
    };

    static short daysUntilEndOfYear(clsDate date)
    {
        return daysInYear(date.year) - daysFromTheBeginingOfYear(date.day, date.month, date.year);
    };

    short daysUntilEndOfYear()
    {
        return daysUntilEndOfYear(*this);
    };

    static short getVacationPeriod(clsDate startDate, clsDate endDate)
    {
        short vacationDays = 0;
        while (isDate1LessThanDate2(startDate, endDate))
        {
            if (isBusinessDay(startDate))
                vacationDays++;
            increaseDateByOneDay(startDate);
        }
        return vacationDays;
    };

    static clsDate getDateFromVacationPeriod(clsDate startDate, short vacationPeriod)
    {
        while (vacationPeriod > 0)
        {
            if (isBusinessDay(startDate))
                vacationPeriod--;
            increaseDateByOneDay(startDate);
        }
        return startDate;
    }

    static bool isDate1AfterDate2(clsDate date1, clsDate date2)
    {
        return !isDate1LessThanDate2(date1, date2) && !isDate1EqualDate2(date1, date2);
    };

    bool isDateAfterDate2(clsDate date2)
    {
        return isDate1AfterDate2(*this, date2);
    };

    static enDateComparison compareDates(clsDate date1, clsDate date2)
    {
        if (isDate1EqualDate2(date1, date2))
            return enDateComparison::EQUAL;
        else if (isDate1LessThanDate2(date1, date2))
            return enDateComparison::BEFORE;

        return enDateComparison::AFTER;
    };

    enDateComparison compareDate(clsDate date2)
    {
        return compareDates(*this, date2);
    };

    static bool validateDate(clsDate date)
    {
        if ((date.month < 1 || date.month > 12) || (date.day < 1 || date.day > daysInMonth(date.month, date.year)))
            return false;
        return true;
    };

    bool isValid()
    {
        return validateDate(*this);
    };

    static string dateToString(clsDate date)
    {
        return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
    };

    string dateToString()
    {
        return dateToString(*this);
    };
};