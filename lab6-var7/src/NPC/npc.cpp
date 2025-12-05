#include <cmath>

#include "NPC/npc.h"

NPC::NPC(const std::string &name, int x, int y) : name(name), x(x), y(y) {}

std::string NPC::getName() const { return name; }

int NPC::getX() const { return x; }

int NPC::getY() const { return y; }

bool NPC::isClose(const NPC &other, int distance) const {
  int dx = x - other.x;
  int dy = y - other.y;
  return std::sqrt(dx * dx + dy * dy) <= distance;
}