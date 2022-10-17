#ifndef NOOB_H
#define NOOB_H

#include "player.h"
#include "game.h"

class Noob : public Player
{
public:
	Noob( unsigned char instance = 0 )		: Player(instance)	{}

	// Player interface
public:
	const char *getName() const				{ return( "Noob" ); }
	const Card * getOneCard() const			{ return( getHand().getFirstCard() ); }

protected:
	int willYouRaise( unsigned int )		{ return( getChips() ); }
};


#endif // NOOB_H
