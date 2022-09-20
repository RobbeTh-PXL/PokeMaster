#include "texasholdem.h"
#include <stdio.h>
#include <string.h>

/*  willYouRaise
 *  return  0    -> Showdown (Ask players to show cards)
 *  return  1    -> Call (Increase Bet)
 *  return -1    -> Fold (Return cards to dealer, get out the round)
*/

int willYouRaise( struct Game * game, struct Player * player, unsigned int totalBet )
{
    if(player->ID == 0){
        return 1;
    }
    return 0;
}

int main()
{
    struct Game game;

    makeNewDeck(&game);

    struct Player speler1;
    strcpy(speler1.name, "speler1");
    speler1.ID = 0;

    struct Player speler2;
    strcpy(speler2.name, "speler2");
    speler2.ID = 1;

    struct Player speler3;
    strcpy(speler3.name, "speler3");
    speler3.ID = 2;

    struct Player speler4;
    strcpy(speler4.name, "speler4");
    speler4.ID = 3;

    addPlayerToGame(&game, &speler1);
    addPlayerToGame(&game, &speler2);
    addPlayerToGame(&game, &speler3);
    addPlayerToGame(&game, &speler4);


    playGame(&game, 1);
    printf("The winner is %s with %d chips !", game.players[0]->name, game.players[0]->chips);
    return 0;
}
