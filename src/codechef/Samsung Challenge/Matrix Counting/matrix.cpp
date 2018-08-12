/*
 * Matrix Counting
 *
 * Consider an n∗n matrix A consisting of all zeros. Find the number of ways to fill this matrix with exactly n+2 ones such that the permanent of the matrix is zero. Output your answer modulo 109+7.
 *
 * Note that permanent of a matrix A is defined to be Perm(A)=∑σ∈Sn∏ni=1A[i][σ(i)], where Sn is the set of all permutations of {1,2,…,n}. For more details on the permanent, you can check here.
 *
 * Input
 * The only line of the input contains an integer n.
 *
 * Output
 * Output a single line containing your answer modulo 109+7.
 *
 *
 * Constraints
 * 2≤n≤10^3
 *
 * Information to score partial points
 * For 30% of the score: 1≤n≤10
 * Remaining 70%: No extra constraints.
 *
 * Sample Input #1
 * 2
 * Sample Output #1
 * 0
 * Explanation #1
 * n is 2. Hence we should fill the matrix with 4 ones. There is only one matrix with 4 ones of size 2 * 2, i.e. all entries of the matrix are one. The permanent of this matrix is 2. Thus, there is no way to fill the matrix with 4 ones and have permanent zero. So, the answer will be zero.
 *
 * Sample Input #2
 * 3
 * Sample Output #2
 * 45
 */
