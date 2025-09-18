#include "../include/is_number_clean.h"
#include <iostream>

bool IsNumberClean(std::string number) {
    if (number.size() == 1 && (number[0] < '0' || number[0] > '9')) { return false; }
    for (size_t i = 0; i < number.size() - 1; ++i) {
        if (number[i] < '0' || number[i] > '9') {
            return false;
        }
        if (number[i] > number[i + 1]) {
            return false;
        }
    }
    return true;
}