#pragma once

#include <memory>
#include <vector>

#include "observer.h"

class Subject {
private:
  std::vector<std::shared_ptr<Observer>> observers;

public:
  void attach(std::shared_ptr<Observer> observer);
  void detach(std::shared_ptr<Observer> observer);
  void notify(const std::string &message) const;
};