//
//  Datetime Source.hpp
//  DateTime Utility Suite
//
//  Created by Isaac Adeleke on 12/12/24.
//

#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

class Time {
public:
    int hour, minute, second;

    Time(int hour = 0, int minute = 0, int second = 0);
    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    std::string toString() const;
};

class Date {
public:
    int year, month, day;

    Date(int year = 1970, int month = 1, int day = 1);
    bool isLeapYear(int year) const;
    int daysInMonth(int year, int month) const;
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    std::string toString() const;
};

class DateTime {
public:
    Date date;
    Time time;

    DateTime(int year, int month, int day, int hour, int minute, int second);
    static int differenceInSeconds(const DateTime& dt1, const DateTime& dt2);
    std::string format(const std::string& formatString) const;
};

#endif
