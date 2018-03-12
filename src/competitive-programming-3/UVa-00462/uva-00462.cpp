/*
 * 462 Bridge Hand Evaluator
 * https://uva.onlinejudge.org/external/4/462.pdf
 *
 * In the card game “Bridge”, players must assess the strength of their hands
 * prior to bidding against one
another. Most players use a point-count scheme which employs the following
rules: 1. Each ace counts 4 points. Each king counts 3 points. Each queen
counts 2 points. Each jack counts one point.  2. Subtract a point for any king
of a suit in which the hand holds no other cards.  3. Subtract a point for any
queen in a suit in which the hand holds only zero or one other cards.  4.
Subtract a point for any jack in a suit in which the hand holds only zero, one,
or two other cards.  5. Add a point for each suit in which the hand contains
exactly two cards.  6. Add two points for each suit in which the hand contains
exactly one card.  7. Add two points for each suit in which the hand contains
no cards.  A suit is stopped if it contains an ace, or if it contains a king
and at least one other card, or if it contains a queen and at least two other
cards.  During the opening assessment, the three most common possibilities are:
• If the hand evaluates to fewer than 14 points, then the player must pass.  •
One may open bidding in a suit if the hand evaluates to 14 or more points.
Bidding is always opened in one of the suits with the most cards.  • One may
open bidding in “no trump” if the hand evaluates to 16 or more points ignoring
rules 5, 6, and 7 and if all four suits are stopped. A no trump bid is always
preferred over a suit bid when both are possible.  Input Input to your program
consists of a series of lines, each line containing 13 cards. Each card
consists of two characters. The first represents the rank of the card: ‘A’,
‘2’, ‘3’, ‘4’, ‘5’, ‘6’, ‘7’, ‘8’, ‘9’, ‘T’, ‘J’, ‘Q’, ‘K’. The second
represents the suit of the card: ‘S’, ‘H’, ‘D’, ‘C’, standing for “spades”,
“hearts”, “diamonds”, and “clubs”, respectively.  Output For each line of the
input, print one line containing the recommended bid, either ‘PASS’, the first
‘BID suit’, where suit is ‘S’, ‘H’, ‘D’, or ‘C’ (sorted in this natural way if
two or more are possible), or ‘BID NO-TRUMP’.  Note: For the first example
below, the evaluation starts with 6 points for the two kings, 4 for the ace, 6
for the three queens, and one for the jack. To this tally of 17 points, we add
1 point for having only two cards in spades, and subtract 1 for having a queen
in spaces with only one other card in spades.  The resulting 17 points is
enough to justify opening in a suit.  The evaluation for no-trump is 16 points,
since we cannot count the one point for having only two spades. We cannot open
in no-trump, however, because the hearts suit is not stopped.  Hence we must
open bidding in a suit. The two longest suits are clubs and diamonds, with four
cards each, so the possible outputs are ‘BID C’, or ‘BID D’.

Sample Input
KS QS TH 8H 4H AC QC TC 5C KD QD JD 8D
AC 3C 4C AS 7S 4S AD TD 7D 5D AH 7H 5H
Sample Output
BID D
BID NO-TRUMP

*/
#include<iostream>
#include<cstdio>
#include<cstring>

bool debug = false;

bool getInput(char * inputRank, char *inputSuite)
{
    for(int i = 0; i < 13; i++) {
        if(scanf("%c%c", &inputRank[i], &inputSuite[i]) == EOF)
            return false;
        if(i != 12)
            scanf(" ");
        else
            scanf("\n");
    }
    return true;
}

void convert(int hand[4][13], int cards[4], char * inputRank, char *inputSuite)
{
    if(debug) {
        for(int i = 0 ; i < 13; i++)
            std::cout << inputRank[i] << inputSuite[i] << ((i == 12)?"":" ");
        std::cout << std::endl;
    }

    int row;
    for(int i = 0 ; i < 13; i++) {
        switch(inputSuite[i]) {
            case 'S': row = 0;  break;
            case 'H': row = 1; break;
            case 'D': row = 2; break;
            case 'C': row = 3; break;
        }
        cards[row]++;
        switch(inputRank[i]) {
            case 'A': hand[row][0] = 1; break;
            case '2': case '3': case '4': case '5' : case '6': case '7': case '8': case '9':
                      hand[row][inputRank[i]-'2'+1] = 1;
                      break;
            case 'T': hand[row][9] = 1; break;
            case 'J': hand[row][10] = 1; break;
            case 'Q': hand[row][11] = 1; break;
            case 'K': hand[row][12] = 1; break;
        }
    }

    if(debug) {
        for(int s = 0 ; s < 4; s++) {
            for(int r = 0 ; r < 13; r++)
                std::cout << hand[s][r] << " ";
            std::cout << std::endl;
        }
    }
    return;
}

int evaluate(int hand[4][13], int cards[4], int &eval2, bool &allSuitesStopped)
{
    int eval1 = 0;
    eval2 = 0;

    bool stopped[4];

    for(int suite = 0; suite < 4; suite++) {
        /* rule 1 */
        if(hand[suite][0]) { eval1 += 4; eval2 += 4; }
        if(hand[suite][12]) { eval1 += 3; eval2 += 3; }
        if(hand[suite][11]) { eval1 += 2; eval2 += 2; }
        if(hand[suite][10]) { eval1 += 1; eval2 += 1; }
        /* rule stopped */
        if(hand[suite][0]) stopped[suite] = true;
        else if(hand[suite][12] && cards[suite] > 2) stopped[suite] = true;
        else if(hand[suite][11] && cards[suite] > 3) stopped[suite] = true;
    }
    allSuitesStopped = true;
    for(int suite = 0 ; suite < 4; suite++) {
        if(stopped[suite] == false) allSuitesStopped = false;
    }
    return eval1;
}

std::string getBidSuite(int hand[4][13])
{
    return "";
}

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    char inputRank[13];
    char inputSuite[13];
    while(getInput(inputSuite, inputRank)) {
        int eval1, eval2;
        bool allSuitesStopped;

        int hand[4][13];
        int cards[4];

        memset(hand, 0, sizeof(hand));
        memset(cards, 0, sizeof(cards));

        convert(hand, cards, inputSuite, inputRank);
        eval1 = evaluate(hand, cards, eval2, allSuitesStopped);

        if(eval1 >= 16 && allSuitesStopped)
           std::cout << "BID NO-TRUMP" << std::endl;
        else if(eval2 >= 14)
           std::cout << "BID " << getBidSuite(hand) << std::endl;
        else std::cout << "BID PASS" << std::endl;
    }
    return 0;
}
