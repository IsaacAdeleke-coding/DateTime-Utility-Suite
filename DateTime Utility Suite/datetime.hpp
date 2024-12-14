//
//  datetime.hpp
//  datetime2
//
//  Created by Isaac Adeleke on 12/12/24.
//

#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

// Base class for Day
class Day {
protected:
    int year, month, day;

public:
    Day(int year = 1970, int month = 1, int day = 1);
    virtual ~Day() = default;

    bool isLeapYear(int year) const;
    int daysInMonth(int year, int month) const;
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    std::string toString() const;
    std::string dayOfWeek() const;
};

// Base class for Time
class Time {
protected:
    int hour, minute, second;

public:
    Time(int hour = 0, int minute = 0, int second = 0);
    virtual ~Time() = default;

    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    std::string toString() const;
};

// Date class inheriting from Day
class Date : public Day {
public:
    Date(int year = 1970, int month = 1, int day = 1);
};

// DateTime class inheriting from both Day and Time
class DateTime : public Day, public Time {
private:
    int timeZoneOffset; // Time zone offset in minutes (e.g., -300 for EST)

public:
    DateTime(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset = 0);

    void adjustToTimeZone(int newTimeZoneOffset);
    static int differenceInSeconds(const DateTime& dt1, const DateTime& dt2);

    std::string serialize() const;
    static DateTime deserialize(const std::string& serialized);
    std::string format(const std::string& formatString) const;
};

#endif