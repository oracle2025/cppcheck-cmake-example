#include <iostream>
#include <list>
#include <vector>
using namespace std;

#ifndef GAME_H_
#define GAME_H_

class Player {
	public:
		Player(const string& _name) :
			name(_name),
			place(0),
			purse(0),
			inPenaltyBox(false)
	{}
		void movePlacesForward(int roll)
		{
    		place = place + roll;
    		if (place > 11)
        		place = place - 12;
		}
		string currentCategory()
		{
			switch (place) {
  				case 0:
  				case 4:
  				case 8:
    				return "Pop";
  				case 1:
  				case 5:
  				case 9:
    				return "Science";
  				case 2:
  				case 6:
  				case 10:
    				return "Sports";
    			default:
  					return "Rock";
  			}
		}
		void addOneToPurse()
		{
			purse++;
		}
		bool didPlayerWin() { return !(purse == 6); }
		string name;
		int place;

		bool inPenaltyBox;
		int getPurse() const { return purse; }
	private:
		int purse;
};

class Game{

	private:
		vector<Player> players;


		list<string> popQuestions;
		list<string> scienceQuestions;
		list<string> sportsQuestions;
		list<string> rockQuestions;

		vector<Player>::iterator playerIterator;
		Player& player();
		bool isGettingOutOfPenaltyBox;

	public:
		Game();
		string createRockQuestion(int index);
		bool isPlayable();
		bool add(string playerName);

		int howManyPlayers();
		void roll(int roll);

	private:
		void askQuestion();
		bool addPointAndQueryWinner();
		void advancePlayer();
		bool isOdd(int roll) const;

	public:
		bool wasCorrectlyAnswered();
		bool wrongAnswer();

};

#endif /* GAME_H_ */
