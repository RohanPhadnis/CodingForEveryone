#include <stdio.h>
#include <stdlib.h>


#define NUM_SUITS 4
#define NUM_PIPS 13
#define NUM_CARDS 52


typedef enum suit {
    HEART,
    DIAMOND,
    CLUB,
    SPADE
} suit;

typedef enum pip {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} pip;

typedef struct card {
    suit suit_val;
    pip pip_val;
} card;


void print_suit(suit s) {
    switch (s) {
        case HEART: printf("heart"); break;
        case DIAMOND: printf("diamond"); break;
        case CLUB: printf("club"); break;
        case SPADE: printf("spade"); break;
        default: printf("error");
    }
}

void print_pip(pip p) {
    switch (p) {
        case ACE: printf("ace"); break;
        case TWO: printf("2"); break;
        case THREE: printf("3"); break;
        case FOUR: printf("4"); break;
        case FIVE: printf("5"); break;
        case SIX: printf("6"); break;
        case SEVEN: printf("7"); break;
        case EIGHT: printf("8"); break;
        case NINE: printf("9"); break;
        case TEN: printf("10"); break;
        case JACK: printf("jack"); break;
        case QUEEN: printf("queen"); break;
        case KING: printf("king"); break;
        default: printf("error");
    }
}


void print_card(card c) {
    print_suit(c.suit_val);
    printf(" ");
    print_pip(c.pip_val);
    printf("\n");
}


void shuffle(card array[], int size) {
    int i, j;
    card temp;
    for (i = 0; i < size; i++) {
        j = rand() % size;
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}


int analyze_hand(card array[], int start) {
    int i = 0;
    int[] count
    for (i = start; i < start + 4; i++) {

    }
}


int main() {
    card deck[NUM_CARDS];
    int i, s, p;
    for (s = 0; s < NUM_SUITS; s++) {
        for (p = 0; p < NUM_PIPS; p++) {
            deck[s * NUM_PIPS + p].suit_val = s;
            deck[s * NUM_PIPS + p].pip_val = p;
        }
    }
    printf("Original Deck:\n");
    for (i = 0; i < NUM_CARDS; i++) {
        print_card(deck[i]);
    }
    shuffle(deck, NUM_CARDS);
    printf("\nShuffled Deck:\n");
    for (i = 0; i < NUM_CARDS; i++) {
        print_card(deck[i]);
    }

    // Simulation

}
