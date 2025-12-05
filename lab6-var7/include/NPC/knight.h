#pragma once

#include "Visitor/visitor.h"
#include "npc.h"

class Knight : public NPC {
public:
  Knight(const std::string &name, int x, int y);

  void accept(Visitor &visitor) override { visitor.visit(*this); }

  std::string getType() const override { return "Knight"; }
};