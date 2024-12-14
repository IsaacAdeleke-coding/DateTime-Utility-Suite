//
//  datetime.cpp
//  DateTime Utility Suite
//
//  Created by Isaac Adeleke on 12/12/24.
//

#include "datetime.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

// Time Class Implementation
Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {}

void Time::addSeconds(int seconds) {
    second += seconds;
    minute += second / 60;
    second %= 60;
    if (second < 0) {
        second += 60;
        minute--;
    }

    hour += minute / 60;
    minute %= 60;
    if (minute < 0) {
        minute += 60;
        hour--;
    }

    hour %= 24;
    if (hour < 0) hour += 24;
}

void Time::addMinutes(int minutes) {
    addSeconds(minutes * 60);
}

void Time::addHours(int hours) {
    addSeconds(hours * 3600);
}

std::string Time::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << hour << ":"
        << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second;
    return oss.str();
}

// Date Class Implementation
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int year, int month) const {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

void Date::addDays(int days) {
    day += days;
    while (day > daysInMonth(year, month)) {
        day -= daysInMonth(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    while (day <= 0) {
        month--;
        if (month <= 0) {
            month = 12;
            year--;
        }
        day += daysInMonth(year, month);
    }
}

void Date::addMonths(int months) {
    month += months;
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month <= 0) {
        month += 12;
        year--;
    }
    day = min(day, daysInMonth(year, month));
}

void Date::addYears(int years) {
    year += years;
    if (month == 2 && day == 29 && !isLeapYear(year)) {
        day = 28;
    }
}

std::string Date::toString() const {
    ostringstream oss;
    oss << setw(4) << setfill('0') << year << "-"
        << setw(2) << setfill('0') << month << "-"
        << setw(2) << setfill('0') << day;
    return oss.str();
}

// DateTime Class Implementation
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : date(year, month, day), time(hour, minute, second) {}

int DateTime::differenceInSeconds(const DateTime& dt1, const DateTime& dt2) {
    // Calculate days difference
    int days1 = dt1.date.year * 365 + dt1.date.day;
    for (int i = 1; i < dt1.date.month; ++i) {
        days1 += dt1.date.daysInMonth(dt1.date.year, i);
    }

    int days2 = dt2.date.year * 365 + dt2.date.day;
    for (int i = 1; i < dt2.date.month; ++i) {
        days2 += dt2.date.daysInMonth(dt2.date.year, i);
    }

    int dayDifference = days1 - days2;
    int timeDifference = (dt1.time.hour * 3600 + dt1.time.minute * 60 + dt1.time.second) -
                         (dt2.time.hour * 3600 + dt2.time.minute * 60 + dt2.time.second);
    return dayDifference * 86400 + timeDifference;
}

std::string DateTime::toString() const {
    return date.toString() + " " + time.toString();
}

std::string DateTime::format(const std::string& formatString) const {
    // Placeholder for custom formatting logic
    return toString();
}
