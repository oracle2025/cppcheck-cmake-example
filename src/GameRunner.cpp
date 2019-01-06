#include <stdlib.h>
#include "Game.hpp"

static bool notAWinner;

void runGame() {
  Game aGame;

  aGame.add("Chet");
  aGame.add("Pat");
  aGame.add("Sue");

  do {

    aGame.roll(rand() % 5 + 1);

    if (rand() % 9 == 7) {
      notAWinner = aGame.wrongAnswer();
    } else {
      notAWinner = aGame.wasCorrectlyAnswered();
    }
  } while (notAWinner);
}

int main() {
  std::srand(0);
  for (int i = 0; i < 1000; i++) {
    // for (int i = 0; i < 1; i++) {
    runGame();
  }
}
