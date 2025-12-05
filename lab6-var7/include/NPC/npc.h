#pragma once

#include <string>
#include <memory>

class Visitor;

class NPC {
protected:
    std::string name;
    int x;
    int y;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual void accept(Visitor& visitor) = 0;
    virtual std::string getType() const = 0;

    std::string getName() const;
    int getX() const;
    int getY() const;

    bool isClose(const NPC& other, int distance) const;
};