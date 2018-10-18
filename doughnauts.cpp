#include "fight.h"
#include "fight_history.h"

int main() {
  Fight f1;

  FightHistory fh;

  for (unsigned int i=0; i<1000; i++) {
    fh.addFight(f1);
  }

  return 0;
}
