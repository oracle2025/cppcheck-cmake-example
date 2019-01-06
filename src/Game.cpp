#include "Game.hpp"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

Game::Game() : playerIterator(players.begin()) {
  for (int i = 0; i < 50; i++) {

    ostringstream oss(ostringstream::out);
    oss << "Pop Question " << i;

    popQuestions.push_back(oss.str());

    char str[255];
    sprintf(str, "Science Question %d", i);
    scienceQuestions.push_back(str);

    char str1[255];
    sprintf(str1, "Sports Question %d", i);
    sportsQuestions.push_back(str1);

    rockQuestions.push_back(createRockQuestion(i));
  }
}

string Game::createRockQuestion(int index) {
  char indexStr[127];
  sprintf(indexStr, "Rock Question %d", index);
  return indexStr;
}

bool Game::isPlayable() { return (howManyPlayers() >= 2); }

bool Game::add(string playerName) {
  players.push_back(playerName);
  playerIterator = players.begin();
  cout << playerName << " was added" << endl;
  cout << "They are player number " << players.size() << endl;
  return true;
}

int Game::howManyPlayers() { return players.size(); }


bool Game::isOdd(int roll) const
{
	return (roll % 2 != 0);
}
void Game::roll(int roll) {
  cout << player().name << " is the current player" << endl;
  cout << "They have rolled a " << roll << endl;

  if (!player().inPenaltyBox || isOdd(roll)) {
  	  if (player().inPenaltyBox) {
      	  isGettingOutOfPenaltyBox = true;
      	  cout << player().name << " is getting out of the penalty box" << endl;
      }
  	  player().movePlacesForward(roll);
  	  cout << player().name << "'s new location is " << player().place << endl;
  	  cout << "The category is " << player().currentCategory() << endl;
  	  askQuestion();
  } else {
      cout << player().name << " is not getting out of the penalty box" << endl;
      isGettingOutOfPenaltyBox = false;
  }
}

void Game::askQuestion() {
  if (player().currentCategory() == "Pop") {
    cout << popQuestions.front() << endl;
    popQuestions.pop_front();
  }
  if (player().currentCategory() == "Science") {
    cout << scienceQuestions.front() << endl;
    scienceQuestions.pop_front();
  }
  if (player().currentCategory() == "Sports") {
    cout << sportsQuestions.front() << endl;
    sportsQuestions.pop_front();
  }
  if (player().currentCategory() == "Rock") {
    cout << rockQuestions.front() << endl;
    rockQuestions.pop_front();
  }
}

bool Game::addPointAndQueryWinner() {
  player().addOneToPurse();
  cout << player().name << " now has " << player().getPurse() << " Gold Coins."
       << endl;
  bool winner = player().didPlayerWin();
  return winner;
}
Player &Game::player() { return *playerIterator; }

void Game::advancePlayer() {
  playerIterator++;
  if (playerIterator == players.end())
    playerIterator = players.begin();
}

bool Game::wasCorrectlyAnswered() {
	bool winner;
  	if (player().inPenaltyBox) {
    	if (isGettingOutOfPenaltyBox) {
  			cout << "Answer was correct!!!!" << endl;
      		winner = addPointAndQueryWinner();
    	} else {
      		winner = true;
    	}
  	} else {
  	  	cout << "Answer was corrent!!!!" << endl;
    	winner = addPointAndQueryWinner();
  	}
  	advancePlayer();
  	return winner;
}

bool Game::wrongAnswer() {
  cout << "Question was incorrectly answered" << endl;
  cout << player().name + " was sent to the penalty box" << endl;
  player().inPenaltyBox = true;

  advancePlayer();
  return true;
}

