#pragma once

#include <memory>
#include <string>
#include <vector>

#include "NPC/npc.h"
#include "Observer/kill_subject.h"

class DungeonEditor {
private:
  std::vector<std::shared_ptr<NPC>> npcs;
  KillSubject killSubject;

public:
  void attachObserver(std::shared_ptr<Observer> observer);
  void detachObserver(std::shared_ptr<Observer> observer);

  void addNPC(const std::string &type, const std::string &name, int x, int y);
  void removeNPC(const std::string &name);
  void clearAll();

  void printAll() const;

  void saveToFile(const std::string &filename) const;
  void loadFromFile(const std::string &filename);

  void fight(int distance);

  const std::vector<std::shared_ptr<NPC>> &getNPC() const;
  size_t getNPCCount() const;
  const KillSubject &getKillSubject() const;
};