#pragma once

#include "subject.h"

class KillSubject : public Subject {
public:
  void reportKill(const std::string &killer, const std::string &victim) {
    std::string message = "KILL: " + killer + " killed " + victim;
    notify(message);
  }

  void reportBattleStart(int participants, int radius) {
    std::string message = "BATTLE START: " + std::to_string(participants) +
                          " NPCs, raduis: " + std::to_string(radius);
    notify(message);
  }

  void reportBattleEnd(int survivors) {
    std::string message =
        "BATTLE END: " + std::to_string(survivors) + " sirvivors";
    notify(message);
  }
};