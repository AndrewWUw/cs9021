#ifndef _DECK_H_
#define _DECK_H_

#include <locale.h> 
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> 

#define HEARTS L'\u2665'
#define CLUBS L'\u2663'
#define DIAMONDS L'\u2666'
#define SPADES L'\u2660'
#define ACE "A"
#define TWO "2"
#define THREE "3"
#define FOUR "4"
#define FIVE "5"
#define SIX "6"
#define SEVEN "7"
#define EIGHT "8"
#define NINE "9"
#define TEN "10"
#define JACK "J"
#define QUEEN "Q"
#define KING "K"
#define NB_OF_RANKS 13
#define DECK_SIZE 52

typedef int Deck[52];
typedef int *pt_to_cards;
typedef const int *pt_to_const_cards;

/* We assume that the 52 cards are originally ordered as in a brand new set, namely:
 * - Ace through King of Hearts, then
 * - Ace through King of Clubs, then
 * - King through Ace of Diamonds, then
 * - King through Ace of Spades. */
void initialise_deck(const pt_to_cards);
void display_deck(const pt_to_const_cards);
/* The second argument is the number of times the deck is to be shuffled.
 * It can be shown that 12 shuffles are needed for the process to be considered random. */
void shuffle_deck(const pt_to_cards, int);

#endif
