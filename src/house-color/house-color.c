/*
https://www.hackerearth.com/practice/algorithms/dynamic-programming/introduction-to-dynamic-programming-1/practice-problems/algorithm/the-colorful-street-1/

There is a street by the name of colorful street in the Pretty Town. The residents of the house have decided that they will paint their houses in either Pink, Orange or Yellow color and not other. They have also decided that no two adjacent houses will have the same color. For house i, i − 1 and i + 1 are the neighbors and note that the first and the last house are not neighbors.

The cost of painting a house in a particular color is different. The cost of painting the first house in color yellow maybe different than what its for painting the second house in the same color.

You have to find the minimum of cost of painting the houses which satisfy the given condition.

Input Constraints - Number of houses will contain between 1 and 20 elements, inclusive.
Each line of input for houses will have three values for cost of coloring in each color. Each value will be between 1 and 1000 .

Input Format 
The first line will contain the number of test cases
T
- The second line will contain an integer 
N that will specify how many houses are there. - Each of the following N lines will contain 
3 numbers separated by space that represents the cost of painting that house in either pink, orange or yellow color.

Output Format Print 
T
 lines showing the cost of painting the houses for each test case.
*/

#include<stdio.h>
#include<limits.h>

enum { PINK, ORANGE, YELLOW, MAX_COLORS };
#define MAX_HOUSES 1024

/* here is the cost array for the house */
int cost[MAX_HOUSES][MAX_COLORS];
int cost_cache[MAX_HOUSES][MAX_COLORS];
int cache_hit;
int find_min_entry;

void reset_cache(void)
{
    cache_hit = 0;
    find_min_entry = 0;
    for(int i = 0 ; i < MAX_HOUSES; i++)
        for(int j = 0; j < MAX_COLORS; j++)
            cost_cache[i][j] = -1;
}

/* find min cost
 * if i'th house is colored with color c,
 * and n is the maximum number of houses
 */
int find_min_cost(int i, int n, int c)
{
    find_min_entry++;
    if(i == n) { /* we are at the last house of the row */
        return cost[i][c];
    }
    if(cost_cache[i][c] != -1) {
        cache_hit++;
        return cost_cache[i][c];
    }
    int cur_cost = cost[i][c];
    int min_remaining = INT_MAX;
    for(int j = 0; j < MAX_COLORS; j++) {
        if(j == c) /* next house color can not be same as this house color */
            continue;
        int remaining = find_min_cost(i + 1, n, j);
        if(remaining < min_remaining)
            min_remaining = remaining;
    }
    cost_cache[i][c] = cur_cost + min_remaining;
    return cost_cache[i][c];
}

void read_input(int *n)
{
    int i = 0;
    int N = 0;
    scanf("%d", &N);
    for(i = 0 ; i < N; i++) {
        for(int c = 0; c < MAX_COLORS; c++) {
            scanf("%d", &cost[i][c]);
        }
    }
    *n = N;
    return;
}

int main(int argc, char * argv[])
{
    int T = 0;
    scanf("%d",&T); /* number of test cases */

    for(int t = 0 ; t < T; t++)
    {
        int n = 0;
        read_input(&n);
        if(n > 0) {
            reset_cache();
            int min = find_min_cost(0, n-1, 0);
            for(int c = 1; c < MAX_COLORS; c++) {
                int cost = find_min_cost(0, n-1, c);
                if(cost < min)
                    min = cost;
            }
            // printf("%d (%d / %d)\n", min, find_min_entry, cache_hit);
            printf("%d\n", min);
        }
    }
    return 0;
}
