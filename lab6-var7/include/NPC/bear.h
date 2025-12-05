#pragma once

#include "Visitor/visitor.h"
#include "npc.h"

class Bear : public NPC {
public:
  Bear(const std::string &name, int x, int y);

  void accept(Visitor &visitor) override { visitor.visit(*this); }

  std::string getType() const override { return "Bear"; }
};