#pragma once

#include "fight.h"

#include <vector>
using std::vector;

class FightHistory {
  public:
    void addFight(Fight f);

  private:
    vector<Fight> history;
};
