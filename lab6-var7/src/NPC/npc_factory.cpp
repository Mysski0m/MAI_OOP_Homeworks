#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>

#include "NPC/bear.h"
#include "NPC/knight.h"
#include "NPC/npc_factory.h"
#include "NPC/orc.h"

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string &type,
                                           const std::string &name, int x,
                                           int y) {
  if (!isValidCoordinates(x, y)) {
    throw std::runtime_error("Invalid coordinates. Must be in range 0-500");
  }

  if (type == "Orc")
    return std::make_shared<Orc>(name, x, y);
  if (type == "Knight")
    return std::make_shared<Knight>(name, x, y);
  if (type == "Bear")
    return std::make_shared<Bear>(name, x, y);

  throw std::runtime_error("failed to create npc: Unknown NPC type: " + type);
}

std::shared_ptr<NPC> NPCFactory::loadFromString(const std::string &data) {
  std::stringstream ss(data);
  std::string type;
  std::string name;
  int x;
  int y;

  ss >> type >> name >> x >> y;
  return createNPC(type, name, x, y);
}

std::string NPCFactory::saveToString(const NPC &npc) {
  return npc.getType() + " " + npc.getName() + " " +
         std::to_string(npc.getX()) + " " + std::to_string(npc.getY());
}

void NPCFactory::saveToFile(const std::vector<std::shared_ptr<NPC>> &npcs,
                            const std::string &filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file for writing: " + filename);
  }

  size_t aliveCnt = 0;
  for (const auto &npc : npcs) {
    if (npc)
      aliveCnt++;
  }

  file << aliveCnt << "\n";

  for (const auto &npc : npcs) {
    if (npc) {
      file << saveToString(*npc) << "\n";
    }
  }

  file.close();
}

std::vector<std::shared_ptr<NPC>>
NPCFactory::loadFromFile(const std::string &filename) {
  std::vector<std::shared_ptr<NPC>> loadedNPC;
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file for reading: " + filename);
  }

  size_t cnt;
  if (!(file >> cnt)) {
    throw std::runtime_error("Invalid file format: cannot read NPC count");
  }

  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  for (size_t i = 0; i < cnt; ++i) {
    std::string line;
    if (!std::getline(file, line)) {
      throw std::runtime_error("Unexpected end of file at NPC " +
                               std::to_string(i + 1));
    }

    if (!line.empty()) {
      try {
        auto npc = loadFromString(line);
        loadedNPC.push_back(npc);
      } catch (const std::exception &e) {
        std::cerr << "Warning: Error loading NPC from line " << (i + 1)
                  << std::endl;
      }
    }
  }

  file.close();
  return loadedNPC;
}

bool NPCFactory::isValidCoordinates(int x, int y) {
  return x >= 0 && x <= 500 && y >= 0 && y <= 500;
}