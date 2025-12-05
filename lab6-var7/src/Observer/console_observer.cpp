#include <iostream>

#include "Observer/console_observer.h"

void ConsoleObserver::update(const std::string &message) {
  std::cout << "LOG: " << message << std::endl;
}