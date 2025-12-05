#pragma once

#include <memory>

class Orc;
class Knight;
class Bear;

class Visitor {
public:
  virtual ~Visitor() = default;
  virtual void visit(Orc &orc) = 0;
  virtual void visit(Knight &knight) = 0;
  virtual void visit(Bear &bear) = 0;
};