//
//  main.cpp
//  DateTime Utility Suite
//
//  Created by Isaac Adeleke on 12/12/24.
//

#include "datetime.hpp"
#include <iostream>

int main() {
    DateTime dt(2024, 12, 13, 14, 30, 45);
    std::cout << "Current DateTime: " << dt.toString() << std::endl;

    dt.date.addDays(5);
    dt.time.addHours(3);
    std::cout << "Updated DateTime: " << dt.toString() << std::endl;

    return 0;
}
