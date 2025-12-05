#pragma once

#include <memory>
#include <vector>

#include "NPC/bear.h"
#include "NPC/knight.h"
#include "NPC/orc.h"
#include "Observer/kill_subject.h"
#include "visitor.h"

class NPC;

class FightVisitor : public Visitor {
private:
  std::shared_ptr<NPC> attacker;
  std::vector<std::shared_ptr<NPC>> &allNPC;
  std::vector<std::shared_ptr<NPC>> victims;
  int fightDistance;

  void markForDeath(std::shared_ptr<NPC> victim);

public:
  FightVisitor(std::vector<std::shared_ptr<NPC>> &npcs, int distance);

  void setAttacker(std::shared_ptr<NPC> npc);
  void visit(Orc &orc) override;
  void visit(Knight &knight) override;
  void visit(Bear &bear) override;

  void applyKills(KillSubject &subject);
};