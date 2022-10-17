#ifndef ROBBE_H
#define ROBBE_H

#include "player.h"

namespace PXL2022
{
	class Robbe : public Player //Robbe is Player
	{
	public:
		Robbe(unsigned char instance = 0) : Player(instance) {}
		const char* getName(void) const; //{ return "Robbe"; }
	protected:
		int willYouRaise(unsigned int totalBet);
	private:
		int Bet();
		int random();
	};
}
#endif // ROBBE_H