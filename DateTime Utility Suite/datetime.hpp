//
//  datetime.hpp
//  DateTime Utility Suite
//
//  Created by Isaac Adeleke on 12/12/24.
//

#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

// Base class for common functionality
class DateTimeBase {
public:
    virtual std::string toString() const = 0; // Pure virtual function
};

// Time class inheriting from DateTimeBase
class Time : public DateTimeBase {
public:
    int hour, minute, second;

    Time(int hour = 0, int minute = 0, int second = 0);
    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    std::string toString() const override;
};

// Date class inheriting from DateTimeBase
class Date : public DateTimeBase {
public:
    int year, month, day;

    Date(int year = 1970, int month = 1, int day = 1);
    bool isLeapYear(int year) const;
    int daysInMonth(int year, int month) const;
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    std::string toString() const override;
};

// DateTime class combining Date and Time
class DateTime : public DateTimeBase {
private:
    Date date;
    Time time;

public:
    DateTime(int year, int month, int day, int hour, int minute, int second);
    static int differenceInSeconds(const DateTime& dt1, const DateTime& dt2);
    std::string toString() const override;
    std::string format(const std::string& formatString) const;
};

#endif
