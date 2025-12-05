#include <algorithm>
#include <iostream>

#include "DungeonMap.h"
#include "NPC/npc_factory.h"
#include "Visitor/fight_visitor.h"

void DungeonEditor::attachObserver(std::shared_ptr<Observer> observer) {
  killSubject.attach(observer);
}

void DungeonEditor::detachObserver(std::shared_ptr<Observer> observer) {
  killSubject.detach(observer);
}

void DungeonEditor::addNPC(const std::string &type, const std::string &name,
                           int x, int y) {
  try {
    for (const auto &npc : npcs) {
      if (npc->getName() == name) {
        throw std::runtime_error("NPC with name " + name + " already exists");
      }
    }

    auto npc = NPCFactory::createNPC(type, name, x, y);
    npcs.push_back(npc);

    std::string message = "Added " + type + " '" + name + "' at (" +
                          std::to_string(x) + ", " + std::to_string(y) + ")";
    killSubject.notify(message);
  } catch (const std::exception &e) {
    std::string error = "Error adding NPC: " + std::string(e.what());
    killSubject.notify(error);
    throw;
  }
}

void DungeonEditor::removeNPC(const std::string &name) {
  size_t before = npcs.size();

  size_t write_index = 0;
  bool found = false;

  for (size_t i = 0; i < npcs.size(); ++i) {
    if (npcs[i] && npcs[i]->getName() == name) {
      found = true;
    } else {
      if (write_index != i) {
        npcs[write_index] = std::move(npcs[i]);
      }
      write_index++;
    }
  }

  if (found) {
    npcs.resize(write_index);
  }

  if (npcs.size() < before) {
    killSubject.notify("Removed NPC: " + name);
  } else {
    killSubject.notify("NPC not found: " + name);
  }
}

void DungeonEditor::clearAll() {
  npcs.clear();
  killSubject.notify("Cleared all NPCs");
}

void DungeonEditor::printAll() const {
  if (npcs.empty()) {
    std::cout << "No npc in dungeon" << std::endl;
    return;
  }

  std::cout << "\n=== Dungeon NPCs (" << npcs.size() << ") ===" << std::endl;
  std::cout << "ID\tType\t\tName\t\tX\tY" << std::endl;
  std::cout << "------------------------------------------------" << std::endl;

  int id = 1;
  for (const auto &npc : npcs) {
    if (npc) {
      std::cout << id++ << "\t" << npc->getType() << "\t\t" << npc->getName()
                << "\t\t" << npc->getX() << "\t" << npc->getY() << std::endl;
    }
  }
}

void DungeonEditor::saveToFile(const std::string &filename) const {
  try {
    NPCFactory::saveToFile(npcs, filename);
    killSubject.notify("Saved dungeon to: " + filename);
  } catch (const std::exception &e) {
    std::string error = "Save error: " + std::string(e.what());
    killSubject.notify(error);
    throw;
  }
}

void DungeonEditor::loadFromFile(const std::string &filename) {
  try {
    auto loaded = NPCFactory::loadFromFile(filename);
    npcs = loaded;
    killSubject.notify("Loaded dungeon from: " + filename);
  } catch (const std::exception &e) {
    std::string error = "Load error: " + std::string(e.what());
    killSubject.notify(error);
    throw;
  }
}

void DungeonEditor::fight(int distance) {
  if (npcs.empty()) {
    killSubject.notify("No NPCs to fight");
    return;
  }

  killSubject.reportBattleStart(npcs.size(), distance);

  auto npcsCopy = npcs;
  FightVisitor visitor(npcs, distance);

  for (size_t i = 0; i < npcsCopy.size(); ++i) {
    if (npcsCopy[i]) {
      visitor.setAttacker(npcsCopy[i]);
      npcsCopy[i]->accept(visitor);
    }
  }

  visitor.applyKills(killSubject);

  size_t write_index = 0;
  for (size_t i = 0; i < npcs.size(); ++i) {
    if (npcs[i] != nullptr) {
      if (write_index != i) {
        npcs[write_index] = std::move(npcs[i]);
      }
      write_index++;
    }
  }

  npcs.resize(write_index);

  killSubject.reportBattleEnd(npcs.size());
}

const std::vector<std::shared_ptr<NPC>> &DungeonEditor::getNPC() const {
  return npcs;
}

size_t DungeonEditor::getNPCCount() const { return npcs.size(); }

const KillSubject &DungeonEditor::getKillSubject() const { return killSubject; }