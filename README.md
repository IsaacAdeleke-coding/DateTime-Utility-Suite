# DateTime Utility Suite

A comprehensive C++ implementation for working with dates and times. The `DateTime Utility Suite` provides robust functionality to perform arithmetic operations and formatting for dates, times, and combined date-time objects.

---

## Features

### 1. **Date Class**
- Add and subtract days, months, and years
- Handle leap years and varying days per month
- Compute the number of days in a month

### 2. **Time Class**
- Add and subtract seconds, minutes, and hours
- Manage time overflows (e.g., 90 minutes to `23:30`)

### 3. **DateTime Class**
- Combine `Date` and `Time` into a single class
- Calculate the difference between two `DateTime` objects in terms of days, hours, minutes, and seconds
- Format `DateTime` into custom strings using placeholders like `YYYY-MM-DD`, `HH:MM`, etc.

---

## Installation

Clone the repository and compile the code using a C++ compiler:
```bash
git clone <repository_url>
cd DateTimeUtilitySuite
g++ -o datetime datetime_main.cpp datetime.cpp


Usage

Example

#include "datetime.hpp"
#include <iostream>
using namespace std;

int main() {
    DateTime dt1(2023, 12, 10, 23, 59, 59);
    DateTime dt2(2023, 12, 9, 12, 30, 0);

    cout << "DateTime 1: " << dt1.date.toString() << " " << dt1.time.toString() << endl;
    cout << "DateTime 2: " << dt2.date.toString() << " " << dt2.time.toString() << endl;

    cout << "Difference in seconds: " << DateTime::differenceInSeconds(dt1, dt2) << endl;

    cout << "Formatted DateTime: " << dt1.format("Today is YYYY-MM-DD, and the time is HH:MM") << endl;

    return 0;
}


Output:


DateTime 1: 2023-12-10 23:59:59
DateTime 2: 2023-12-09 12:30:00
Difference in seconds: 135599
Formatted DateTime: Today is 2023-12-10, and the time is 23:59


Contributing

Feel free to submit issues or pull requests for enhancements and bug fixes.
