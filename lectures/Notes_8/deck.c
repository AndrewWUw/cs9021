/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Implements functions to:                                       *
 *              - initialise a brand new deck of 52 cards;                     *
 *              - display the deck from the first card (at the top)            *
 *                to the last one (at the bottom);                             *
 *              - simulate an n-riffle shuffle of a deck for a positive n.     *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "deck.h"

const wchar_t const SUITS[] = {HEARTS, CLUBS, DIAMONDS, SPADES};

const char *const RANKS[] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
                             JACK, QUEEN, KING};

void initialise_deck(const pt_to_cards deck) {
    for (int i = 0; i < DECK_SIZE; ++i)
        deck[i] = i;
}

void display_deck(const pt_to_const_cards deck) {
    setlocale(LC_CTYPE, "");
    for (int i = 0; i < DECK_SIZE; ++i) {
        const int s = deck[i] / NB_OF_RANKS;
        /* From Ace through King for Hearts and Clubs, but
         * from King through Ace for Diamonds and Spades. */
        if (s < 2)
            printf("%4s", RANKS[deck[i] % NB_OF_RANKS]);
        else
            printf("%4s", RANKS[NB_OF_RANKS - 1 - deck[i] % NB_OF_RANKS]);
        putwchar(SUITS[s]);
        /* Display 13 cards on a line. */
        if (i % NB_OF_RANKS == 12)
            putchar('\n');
    }
}

void shuffle_deck(const pt_to_cards deck, int n) {
    while (n--) {
        /* Simulate the binomial distribution b(52, 1/2, k)
         * to cut the deck after the kth card, for k in {0, ..., 52}
         * (so in both extremely unlikely limiting cases, the deck is not cut). */
        int cut = 0;
        for (int i = 0; i < DECK_SIZE; ++i)
            cut += rand() % 2;
        if (cut == 0 || cut == DECK_SIZE)
            return;
        Deck new_deck;
        /* The deck is cut into stack_1 and stack_2. */
        int stack_1_i = 0;
        int stack_2_i = cut;
        int both_stacks_size = DECK_SIZE;
        /* We keep selecting
         * - the first card from stack_1 with probability
         *      current size of what's left in stack_1 /
         *      current size of what's left in both stacks, and
         * - the first card from stack_2 with probability
         *      current size of what's left in stack_2 /
         *      current size of what's left in both stacks,
         * till one stack becomes empty. */
        int i = 0;
        while (stack_1_i < cut && stack_2_i < DECK_SIZE) {
            int which_stack = rand() % both_stacks_size--;
            if (which_stack < cut - stack_1_i)
                new_deck[i++] = deck[stack_1_i++];
            else
                new_deck[i++] = deck[stack_2_i++];
        }
        /* If stack_2 is emptied first, then shift what remains of stack_1
         * to the end of the original deck. If stack_1 is emptied first,
         * then what remains of stack_2 is at the right place in the original deck. */
        if (stack_1_i < cut)
            for (int j = i; j < DECK_SIZE; ++j)
                deck[j] = deck[stack_1_i++];
        for (int j = 0; j < i; ++j)
            deck[j] = new_deck[j];
    }
}

