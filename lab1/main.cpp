#include <iostream>
#include "./include/is_number_clean.h"

int main() {
    std::string number;
    std::cout << "Введите число, которое вы хотите проверить на 'чистоту': ";
    std::cin >> number;
    
    if (IsNumberClean(number)) {
        std::cout << "Введеное число является чистым" << std::endl;
        return 0;
    }
    std::cout << "Введеное число не является чистым" << std::endl;
    return 0;
}