#ifndef VADER_H
#define VADER_H

#include "player.h"
#include "game.h"

class Vader : public Player
{
	const char *getName() const			{ return( "VADER !!!!!!!!" ); }

	int willYouRaise( unsigned int totalBet )
	{
		if( previousChips != getChips() )
		{
			if( previousChips < getChips() )
			{
				std::cout << "Previous play, I WON !!!" << std::endl;
			}
			previousChips = getChips();
		}
		PokerRank myHandRank = getHand().getMyRank();
		PokerRank tableRank = getCommunityRank();
		if( myHandRank.getCategory() >= THREE_OF_A_KIND )
		{
			if( tableRank.getCategory() == myHandRank.getCategory() )
			{
				return( 0 );
			}
			return( getChips() );
		}
		else if( myHandRank.getCategory() >= TWO_PAIR )
		{
			if( tableRank.getCategory() == myHandRank.getCategory() )
			{
				return( 0 );
			}
			return( totalBet - getBet() ); //raise as much as raised :-D troll
		}
		else if( getTable()->getCommunityCards().empty() && ( getHand().getFirstCard()->getRank() == 1 || getHand().getSecondCard()->getRank() == 1 ) )
		{
			return( 1 );
		}
		else if( ( getBet() <= getGame()->getBlind() * 2 ) && ( totalBet > getGame()->getBlind() * 2 ) )
		{
			return( -1 );
		}
		return( 0 );
	}

private:
	unsigned int previousChips;
};

#endif // VADER_H
