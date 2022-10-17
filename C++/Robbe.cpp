#include "Robbe.h"
#include "game.h"

namespace PXL2022 {
	const char* Robbe::getName() const {
		return "Robbe";
	}

	int Robbe::willYouRaise(unsigned int totalBet) {
		switch (instance) {
		case 0:
			Bet(); //PLAY
			break;
		case 1:
			if (getTable()->isRiver()) //PLAY ON RIVER
			{
				Bet();
			};
			return -1;
			break;
		case 2:
			random();	//RANDOM
			break;
		case 3:
			if (getTable()->isTurn())
			{
				return (Bet() + 50);
			}
			break;
		default:
			return 0;
			break;
		}
	}

	int Robbe::Bet() {
		PokerRank mijnHandRank = getRank();
		PokerRank tableRank = getCommunityRank();

		if (mijnHandRank.getCategory() >= tableRank.getCategory())
		{
			if (mijnHandRank.getCategory() == STRAIGHT_FLUSH)
			{
				return getChips();	//ALL IN
			}

			if (mijnHandRank.getCategory() == FOUR_OF_A_KIND)
			{
				return getChips();	//ALL IN
			}

			if (mijnHandRank.getCategory() == FULL_HOUSE)
			{
				return getChips();	//ALL IN
			}

			if (mijnHandRank.getCategory() == FLUSH)
			{
				return getChips() * (65/100); //BET 65% OF ALL CHIPS
			}

			if (mijnHandRank.getCategory() == STRAIGHT)
			{
				return getChips() * (40 / 100); //BET 40% OF ALL CHIPS
			}

			if (mijnHandRank.getCategory() == THREE_OF_A_KIND)
			{
				return getChips() * (25 / 100); //BET 25% OF ALL CHIPS
			}

			if (mijnHandRank.getCategory() == ONE_PAIR)
			{
				return getChips() * (10 / 100); //BET 10% OF ALL CHIPS
			}
		}

		return 0;
	}

	int Robbe::random() {
		int a = (rand() % 10);
		if (a >= getChips())
		{
			return 0;
		}
		return a;
	}
}