/*
 * Maximum Partitioning of Array
 *
 * You are given an array a containing n positive integers: a1,a2,…,an. A subarray is any subset of consecutive elements from this array.
 *
 * Consider a subarray of it: (ai,ai+1,…,aj). The 'strength' of this subarray is defined to be the value of the largest element in the subarray which occurs an odd number of times. For example, the strength of subarray 9, 8, 9, 10, 7, 10 would be 8. This is because the numbers 9 and 10 both appear even (2) number of times in the subarray, whereas the number 8 appears only once. Note that the number 7 also appears only once, but the number 8 is larger than 7. If all the elements of the subarray appear even number of times, then the strength will be zero.
 *
 * Given an integer K, for all k such that 1≤k≤K, you need to partition the given array into k non-empty subarrays (partitioning means that each of the n elements should be in exactly one of the k subarrays), such that the sum of the strengths of the k subarrays is maximized, and report this maximum strength for each k.
 *
 * Input
 * The first line of the input contains an integer T denoting the number of test cases. The description of the test cases follows.
 * The first line of each test case contains two space-separated integers n,K.
 * The second line of each test case contains n space separated integers denoting the array a.
 *
 * Output
 * For each test case, output a single line containing K integers, where k-th (1-based indexing) integer should be the maximum sum of strength when you partition the array into k subarrays.
 *
 * Constraints
 * 1≤T≤5
 * 1≤n≤500
 * 1≤K≤min(300,n)
 * 1≤ai≤106
 *
 * Information to score partial points
 * For 30% of the score: 1≤n≤50
 * Remaining 70%: No extra constraints.
 *
 *
 * Sample Input
 * 2
 * 3 3
 * 1 2 2
 * 4 2
 * 1 2 2 3
 * Sample Output
 * 1 4 5
 * 3 5
 * Explanation
 * Example case 1:
 *
 * k=1. We have to partition the array into a single subarray, i.e. the whole array itself. The strength of whole array is 1. Hence answer is 1.
 * k=2. Here, we have to partition it into two subarrays. If we partition it into [1] and [2, 2], the sum of strengths will be 1 + 0 = 1, whereas if we partition into [1, 2] and [2], the sum of strengths is 2 + 2 = 4. Thus answer is 4.
 * k=3. The only possible partition is [1], [2] and [2]. The sum of strengths is 1 + 2 + 2 = 5. Here, each element will go separately into the subarray.
 *
 *
 */

