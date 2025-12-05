#pragma once

#include "observer.h"

class ConsoleObserver : public Observer {
public:
  void update(const std::string &message) override;
};