/*
Q. Modify the poker.c program of Section 10.5 by moving all external variables into main 
and modifying functions so that they communicate by passing arguments.

The analyze_hand function needs to change the straight, flush, four, three, and pairs variables,
so it will have to be passed pointers to those variables.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

// prototypes
void read_cards(int num_in_rank[], int num_in_suit[]);
void analyze_hand(int num_in_rank[], int num_in_suit[],
    bool *straight, bool *flush, bool *four, bool *three, int *pairs);
void print_result(bool straight, bool flush, bool four, bool three, int pairs);

int main(void)
{
    int num_in_rank[NUM_RANKS];
    int num_in_suit[NUM_SUITS];
    bool straight, flush, four, three;
    int pairs; // can be 0, 1 or 2

    for (;;) 
    {
        read_cards(num_in_rank, num_in_suit);
        analyze_hand(num_in_rank, num_in_suit,
            &straight, &flush, &four, &three, &pairs);
        print_result(straight, flush, four, three, pairs);
    }
}

void read_cards(int num_in_rank[], int num_in_suit[])
{
    bool card_exist[NUM_RANKS][NUM_SUITS];
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    for (rank = 0; rank < NUM_RANKS; rank++) {
        num_in_rank[rank] = 0;
        for (suit = 0; suit < NUM_SUITS; suit++) {
            card_exist[rank][suit] = false;
        }
    }

    for (suit = 0; suit < NUM_SUITS; suit++)
        num_in_suit[suit] = 0;

    while (cards_read < NUM_CARDS) {
        bad_card = false;
        printf("Enter a card: ");

        rank_ch = getchar();
        switch (rank_ch) {
            case '0':
                exit(EXIT_SUCCESS);
            case '2':
                rank = 0;
                break;
            case '3':
                rank = 1;
                break;
            case '4':
                rank = 2;
                break;
            case '5':
                rank = 3;
                break;
            case '6':
                rank = 4;
                break;
            case '7':
                rank = 5;
                break;
            case '8':
                rank = 6;
                break;
            case '9':
                rank = 7;
                break;
            case 't':
                rank = 8;
                break;
            case 'j':
                rank = 9;
                break;
            case 'q':
                rank = 10;
                break;
            case 'k':
                rank = 11;
                break;
            case 'a':
                rank = 12;
                break;
            default:
                bad_card = true;
        }
        suit_ch = getchar();
        switch (suit_ch) {
            case 'c':   // FALLTHROUGH
            case 'C':
                suit = 0;
                break;
            case 'd':   // FALLTHROUGH
            case 'D':
                suit = 1;
                break;
            case 'h':   // FALLTHROUGH
            case 'H':
                suit = 2;
                break;
            case 's':   // FALLTHROUGH
            case 'S':
                suit = 3;
                break;
            default:
                bad_card = true;
        }

        while ((ch = getchar()) != '\n')
            if (ch != ' ')
                bad_card = true;

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (card_exist[rank][suit])
            printf("Duplicate card; ignored.\n");
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
            card_exist[rank][suit] = true;
            cards_read++;
        }
    }
}

void analyze_hand(int num_in_rank[], int num_in_suit[],
    bool *straight, bool *flush, bool *four, bool *three, int *pairs)
{
    int num_consec = 0;
    int rank, suit;

    *straight = false;
    *flush = false;
    *four = false;
    *three = false;
    *pairs = 0;

    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            *flush = true;

    rank = 0;
    while (num_in_rank[rank] == 0) rank++;

    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;

    if (num_consec == NUM_CARDS) {
        *straight = true;
        return;
    }

    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4) *four = true;
        if (num_in_rank[rank] == 3) *three = true;
        // *pairs++로 하면 안됨:
        // indirection operator와 postfix increment operator의 우선순위가 같은데,
        // right-to-left associativity를 가지므로, *pairs++는 *(pairs++)와 같다.
        if (num_in_rank[rank] == 2) *pairs += 1;
    }
}

void print_result(bool straight, bool flush, bool four, bool three, int pairs)
{
    if (straight && flush)
        printf("Straight flush");
    else if (four)
        printf("Four for a kind");
    else if (three && pairs == 1)
        printf("Full house");
    else if (flush)
        printf("Flush");
    else if (straight)
        printf("Straight");
    else if (three)
        printf("Three of a kind");
    else if (pairs == 2)
        printf("Two pairs");
    else if (pairs == 1)
        printf("Pair");
    else
        printf("High card");

    printf("\n\n");
}