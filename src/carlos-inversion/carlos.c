/*
https://www.codechef.com/APRIL15/problems/CARLOS

The Aa'ugld alphabet consists of M letters, which we'll denote by integers
from 1 to M in alphabetical order - the smaller number a letter has, the
earlier it appears in the alphabet. Since the author of this alphabet wasn't
very creative, many letters can be transformed to other ones using some
simple operations, which we'll call "inversions".

You're given a list of possible operations. The list isn't exhaustive, since
any two inversions can be combined to produce a new inversion. Specifically,
if there is an inversion that transforms a letter x to a letter y and an
inversion that transforms the letter y to a letter z, you may assume that
there's also an inversion that transforms the letter x to the letter z. In
 short, "inversion" operations are transitive.

Combining any inversion with itself produces identity - an operation that
transforms any letter to itself. (That's where the name "inversion" comes
from - an operation that's its own inverse.) Therefore, if there's an
 inversion that transforms a letter x to a letter y, then there's also an
inversion that transforms the letter y to the letter x.

There's a long word W with N letters. You should transform some of these
letters to other ones in order to make the letters of W sorted in
alphabetical order. Is it possible at all? If it is, what's the minimum
 number of letters that should be transformed?

Input
The first line of the input contains an integer T - the number of test cases.
The first line of each test case contains three integers M, K and N.
The following K lines each contain two integers x and y, denoting an inversion
that transforms letter x to letter y.
The last line of each test case contains N integers ai - letters of the word W.

Output
For each test case, output a single line containing -1 if it's impossible to
make the letters of W sorted in alphabetical order. Otherwise, output the
smallest number of letters that need to be transformed to achieve that.

Constraints
1 ≤ T ≤ 10
1 ≤ N ≤ 200000
0 ≤ K ≤ M(M-1)/2
1 ≤ x,y ≤ M
all unordered pairs (x,y) will be distinct
1 ≤ ai ≤ M

Subtask 1 (18 points):

1 ≤ M ≤ 10
1 ≤ N ≤ 20
Subtask 2 (60 points):

1 ≤ M ≤ 50
1 ≤ N ≤ 20000
Subtask 3 (22 points):

1 ≤ M ≤ 200
1 ≤ N ≤ 200000

Example
Input:
2
3 3 3
1 2
2 3
3 1
3 2 1
3 1 2
2 3
2 1
Output:
2
-1

*/

#include <stdio.h>
#include <string.h>

int graph[200+1][200+1];
int visited[200+1];
int smallest[200+1];
int A[200001];
int M, K, N;

void reset_dp(void)
{
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    memset(A, 0, sizeof(A));
    memset(smallest, 0, sizeof(smallest));
}

void dfs(int i, int *min)
{
    if(visited[i])
        return;
    visited[i] = 1;
    printf("... visited %d\n", i);
    if(i < *min)
        *min = i;
    for(int v = 1; v <= M; v++) {
        if(graph[i][v] && !visited[v]) {
            printf("From %d\n", i);
            dfs(v, min);
        }
    }
}

int find_smallest_alphabet(int i)
{
    if(smallest[i])
        return smallest[i];
    memset(visited, 0, sizeof(visited));
    int min = i;
    printf("*** starting dfs for %d\n", i);
    dfs(i, &min);
    smallest[i] = min;
    return smallest[i];
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) {
        reset_dp();
        int changes = 0;
        scanf("%d %d %d", &M, &K, &N);
        for(int k = 1 ; k <= K; k++) {
            int x, y;
            scanf("%d %d", &x, &y);
            graph[x][y] = 1;
            graph[y][x] = 1;
        }
        for(int i = 1 ; i <= N; i++)
           scanf("%d", &A[i]);

        for(int m = 1; m <= M; m++)
            find_smallest_alphabet(m);

        printf("Smallest alphabet:\n");
        for(int m = 1; m <= M; m++)
            printf("%d => %d\n", m, smallest[m]);

        printf("%d\n", changes);
    }
    return 0;
}
