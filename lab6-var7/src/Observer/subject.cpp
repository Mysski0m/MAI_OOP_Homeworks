#include <algorithm>

#include "Observer/subject.h"

void Subject::attach(std::shared_ptr<Observer> observer) {
  observers.push_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> observer) {
  auto it = std::find(observers.begin(), observers.end(), observer);
  if (it != observers.end()) {
    observers.erase(it);
  }
}

void Subject::notify(const std::string &message) const {
  for (auto &observer : observers) {
    if (observer) {
      observer->update(message);
    }
  }
}