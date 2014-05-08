/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Simulates a riffle shuffle of a brand new deck of 52 cards.    *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *        deck.c                                                               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

int main(void) {
    Deck deck;
    initialise_deck(deck);
    printf("A brand new deck of cards, whose seal has just been broken:\n");
    display_deck(deck);
    srand(time(NULL));
    for(int i = 0; i < 3; ++i) {
        shuffle_deck(deck, 1);
        printf("\nAfter shuffling the deck ");
        i == 0 ? printf("once:\n") : i == 1 ? printf("twice:\n") : printf("thrice:\n");
        display_deck(deck);
    }
    shuffle_deck(deck, 5);
    printf("\nAfter shuffling the deck 5 more times:\n");
    display_deck(deck);
    return EXIT_SUCCESS;
}
