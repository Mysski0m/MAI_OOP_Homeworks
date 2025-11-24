#include "exceptions.h"
#include "thirteen_num_syst.h"
#include <iostream>
#include <ostream>
#include <string>

int main() {
  std::cout << "Enter number to show" << std::endl;
  std::string input;
  std::cin >> input;
  try {
    thirteen::Thirteen number(input);
    std::cout << number.Show() << std::endl;
  } catch (exception::ExceptionNull) {
    std::cout << "Wrong input: not a number in thirteen numerical system"
              << std::endl;
  }
  return 0;
}