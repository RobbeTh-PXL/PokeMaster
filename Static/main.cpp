#include <iostream>
#include <string.h>
#define DEBUG_PRINT
#include "texasholdem.h"

enum spelerIDs
{
	IK,
	JIJ,
	HIJ,
	ZIJ,
	STUDENT_2022,
	MAX_PLAYER_ID
};

bool init = false;
int maxBetEver[MAX_PLAYER_ID];

int willYouRaise( struct Game * game, struct Player * player, unsigned int totalBet )
{
	if( !init )
	{
		init = true;
		for( int i = 0 ; i < MAX_PLAYER_ID ; i++ )
		{
			maxBetEver[i] = 0;
		}
	}
	switch( player->ID )
	{
	case IK:
	{
    PokerRank mijnHandRank = getMyHandRank( player->hand );
		for (int i = 0 ; i < game->playersSize ; i++) {
			if (game->players[i]->ID == HIJ) {
				return -1;
			}
			if (game->players[i]->hand->cards[0] == nullptr) {
				return 0;
			}
		}
		if (player->hand->cards[0]->rank == player->hand->cards[1]->rank) {
			return (game->blind * 4) - totalBet;
		}
		return 0;
		break;
	}
	case JIJ:
		for( int i = 0 ; i < game->playersSize ; i++ )
		{
			if( game->players[i]->bet > maxBetEver[game->players[i]->ID])
			{
				maxBetEver[game->players[i]->ID] = game->players[i]->bet;
			}
		}
		if( game->amountHands > 2 )
		{
			return( -1 );
		}
		for( int i = 0 ; i < game->playersSize ; i++ )
		{
			if( game->players[i]->ID != JIJ && isHandFilled(game->players[i]->hand) )
			{
				return( maxBetEver[game->players[i]->ID] - totalBet + 1 );
			}
		}
		return( -1 );
		break;
	case HIJ:
		if( totalBet > 50 )
		{
			return( 0 );
		}
		return( 50 - totalBet );
		break;
	case ZIJ:
	{
		bool fold = true;
		for( int i = 0 ; !fold && i < game->playersSize ; i++ )
		{
			if( game->players[i]->ID != HIJ && game->players[i]->ID != ZIJ && game->players[i]->hand->cards[0] != nullptr )
			{
				fold = false;
			}
			if( game->players[i]->ID == HIJ && game->players[i]->hand->cards[0] == nullptr )
			{
				fold = false;
			}
		}
		if( fold )
		{
			return -1;
		}

		return( 0 );
		break;
	}
	case STUDENT_2022:
		PokerRank mijnHandRank = getMyHandRank( player->hand );
		if( table[0] == nullptr ) //Pre flop
		{
			if( player->hand->cards[0]->suit == player->hand->cards[1]->suit )
			{ //suited hands
				int diffBetweenOrderedCards = mijnHandRank.hand[0]->rank - mijnHandRank.hand[1]->rank;
				if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
				{ //suited connected
					return ( game->blind * 7 ) - totalBet; //max 7x blind and fold otherwise
				}
				return ( game->blind * 3 ) - totalBet; //max 3x blind and fold otherwise
			}
			if( player->hand->cards[0]->rank == player->hand->cards[1]->rank )
			{ //1 pair to start
				return ( game->blind * 5 ) - totalBet; //max 5x blind and fold otherwise
			}
			int diffBetweenOrderedCards = mijnHandRank.hand[0]->rank - mijnHandRank.hand[1]->rank;
			if( diffBetweenOrderedCards == 1 || diffBetweenOrderedCards == 13 )
			{ //unsuited connected
				return ( game->blind * 3 ) - totalBet; //max 3x blind and fold otherwise
			}
			if( totalBet > game->blind * 2 )
			{
				return -1;
			}
			return 0;
		}
		else if( table[3] == nullptr )
		{ //on flop
			return 0;
		}
		else if( table[4] == nullptr )
		{ //on turn
			return 0;
		}
		else
		{ //on river
			return 0;
		}
		break;
	}
	return( 0 );
}

int main( void )
{
//INIT GAME AND DECK
	Game game;
	makeNewDeck( &game );
//INIT GAME AND DECK

//DEFINE PLAYERS
	Player ik;
	strcpy( ik.name, "Ikke de beste" );
	ik.ID = IK;

	Player jij;
	strcpy( jij.name, "Gijse zot" );
	jij.ID = JIJ;

	Player hij;
	strcpy( hij.name, "Hij weet niet beter" );
	hij.ID = HIJ;

	Player zij;
	strcpy( zij.name, "Zij speelt vals" );
	zij.ID = ZIJ;

	Player student2022;
	strcpy( student2022.name, "student 2022 example" );
	student2022.ID = STUDENT_2022;
//DEFINE PLAYERS

//ADD PLAYERS
	addPlayerToGame( &game, &ik );
	addPlayerToGame( &game, &jij );
	addPlayerToGame( &game, &hij );
	addPlayerToGame( &game, &zij );
	addPlayerToGame( &game, &student2022 );
//ADD PLAYERS

//RUN GAME
	playGame( &game, 1 );
//RUN GAME

//PRINT WINNER
	printf( "The winner is %s with %d chips !", game.players[0]->name, game.players[0]->chips );
//PRINT WINNER

	return 0;
}
