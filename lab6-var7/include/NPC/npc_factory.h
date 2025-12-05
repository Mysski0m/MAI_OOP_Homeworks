#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "npc.h"

class NPCFactory {
public:
  static std::shared_ptr<NPC> createNPC(const std::string &type,
                                        const std::string &name, int x, int y);
  static std::shared_ptr<NPC> loadFromString(const std::string &data);
  static std::string saveToString(const NPC &npc);

  static void saveToFile(const std::vector<std::shared_ptr<NPC>> &npcs,
                         const std::string &filename);
  static std::vector<std::shared_ptr<NPC>>
  loadFromFile(const std::string &filename);

  static bool isValidCoordinates(int x, int y);
};