//
//  datetime.cpp
//  datetime2
//
//  Created by Isaac Adeleke on 12/12/24.
//

#include "datetime.hpp"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cmath>
using namespace std;

// Day Implementation
Day::Day(int year, int month, int day) : year(year), month(month), day(day) {}

bool Day::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Day::daysInMonth(int year, int month) const {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

void Day::addDays(int days) {
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

void Day::addMonths(int months) {
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

void Day::addYears(int years) { year += years; }

std::string Day::toString() const {
    ostringstream oss;
    oss << setw(4) << setfill('0') << year << "-"
        << setw(2) << setfill('0') << month << "-"
        << setw(2) << setfill('0') << day;
    return oss.str();
}

std::string Day::dayOfWeek() const {
    int q = day;
    int m = (month < 3) ? month + 12 : month;
    int Y = (month < 3) ? year - 1 : year;

    int K = Y % 100;
    int J = Y / 100;

    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    switch (h) {
        case 0: return "Saturday";
        case 1: return "Sunday";
        case 2: return "Monday";
        case 3: return "Tuesday";
        case 4: return "Wednesday";
        case 5: return "Thursday";
        case 6: return "Friday";
        default: return "Invalid";
    }
}

// Time Implementation
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

void Time::addMinutes(int minutes) { addSeconds(minutes * 60); }
void Time::addHours(int hours) { addSeconds(hours * 3600); }

std::string Time::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << hour << ":"
        << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second;
    return oss.str();
}

// Date Implementation
Date::Date(int year, int month, int day) : Day(year, month, day) {}

// DateTime Implementation
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset)
    : Day(year, month, day), Time(hour, minute, second), timeZoneOffset(timeZoneOffset) {}

void DateTime::adjustToTimeZone(int newTimeZoneOffset) {
    int offsetDifference = newTimeZoneOffset - timeZoneOffset;
    addSeconds(offsetDifference * 60);
    timeZoneOffset = newTimeZoneOffset;
}

int DateTime::differenceInSeconds(const DateTime& dt1, const DateTime& dt2) {
    int totalDays1 = dt1.year * 365 + dt1.day;
    for (int i = 0; i < dt1.month - 1; ++i) {
        totalDays1 += dt1.daysInMonth(dt1.year, i + 1);
    }

    int totalDays2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month - 1; ++i) {
        totalDays2 += dt2.daysInMonth(dt2.year, i + 1);
    }

    int dayDifference = totalDays1 - totalDays2;
    int secondDifference = (dt1.hour * 3600 + dt1.minute * 60 + dt1.second) -
                           (dt2.hour * 3600 + dt2.minute * 60 + dt2.second);

    return dayDifference * 86400 + secondDifference;
}

std::string DateTime::serialize() const {
    ostringstream oss;
    oss << year << "-" << setw(2) << setfill('0') << month << "-"
        << setw(2) << setfill('0') << day << "T" << setw(2) << setfill('0') << hour << ":"
        << setw(2) << setfill('0') << minute << ":" << setw(2) << setfill('0') << second
        << "Z" << timeZoneOffset;
    return oss.str();
}

DateTime DateTime::deserialize(const std::string& serialized) {
    int year, month, day, hour, minute, second, offset;
    char dash1, dash2, T, colon1, colon2, Z;

    istringstream iss(serialized);
    iss >> year >> dash1 >> month >> dash2 >> day >> T >> hour >> colon1 >> minute >> colon2 >> second >> Z >> offset;

    if (dash1 != '-' || dash2 != '-' || T != 'T' || colon1 != ':' || colon2 != ':' || Z != 'Z') {
        throw invalid_argument("Invalid serialized format");
    }

    return DateTime(year, month, day, hour, minute, second, offset);
}

std::string DateTime::format(const std::string& formatString) const {
    string result;
    for (size_t i = 0; i < formatString.size(); ++i) {
        if (formatString.substr(i, 4) == "YYYY") {
            result += to_string(year);
            i += 3;
        } else if (formatString.substr(i, 2) == "MM") {
            result += (month < 10 ? "0" : "") + to_string(month);
            i += 1;
        } else if (formatString.substr(i, 2) == "DD") {
            result += (day < 10 ? "0" : "") + to_string(day);
            i += 1;
        } else if (formatString.substr(i, 2) == "HH") {
            result += (hour < 10 ? "0" : "") + to_string(hour);
            i += 1;
        } else if (formatString.substr(i, 2) == "MM") {
            result += (minute < 10 ? "0" : "") + to_string(minute);
            i += 1;
        } else if (formatString.substr(i, 2) == "SS") {
            result += (second < 10 ? "0" : "") + to_string(second);
            i += 1;
        } else {
            result += formatString[i];
        }
    }
    return result;
}