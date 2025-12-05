#include <algorithm>
#include <iostream>

#include "NPC/bear.h"
#include "NPC/knight.h"
#include "NPC/orc.h"
#include "Observer/observer.h"
#include "Visitor/fight_visitor.h"

FightVisitor::FightVisitor(std::vector<std::shared_ptr<NPC>> &npcs,
                           int distance)
    : allNPC(npcs), fightDistance(distance) {}

void FightVisitor::setAttacker(std::shared_ptr<NPC> npc) {
  attacker = npc;
  victims.clear();
}

void FightVisitor::markForDeath(std::shared_ptr<NPC> victim) {
  victims.push_back(victim);
}

void FightVisitor::visit(Orc &orc) {
  for (auto &npc : allNPC) {
    if (!npc || npc.get() == &orc)
      continue;

    if (orc.isClose(*npc, fightDistance)) {
      if (npc->getType() == "Bear" || npc->getType() == "Orc") {
        markForDeath(npc);
      }
    }
  }
}

void FightVisitor::visit(Knight &knight) {
  for (auto &npc : allNPC) {
    if (!npc || npc.get() == &knight)
      continue;

    if (knight.isClose(*npc, fightDistance)) {
      if (npc->getType() == "Orc") {
        markForDeath(npc);
      }
    }
  }
}

void FightVisitor::visit(Bear &bear) {
  for (auto &npc : allNPC) {
    if (!npc || npc.get() == &bear)
      continue;

    if (bear.isClose(*npc, fightDistance)) {
      if (npc->getType() == "Knight") {
        markForDeath(npc);
      }
    }
  }
}

void FightVisitor::applyKills(KillSubject &subject) {
  for (auto &victim : victims) {
    if (victim && attacker) {
      subject.reportKill(attacker->getName(), victim->getName());
      for (size_t i = 0; i < allNPC.size(); ++i) {
        if (allNPC[i].get() == victim.get()) {
          allNPC[i] = nullptr;
          break;
        }
      }
    }
  }
}