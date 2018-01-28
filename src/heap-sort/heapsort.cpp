/*
 * Heapsort in an array of integers
 *
 * https://www.youtube.com/watch?v=B7hVxCmfPtM&t=2679s&list=WL&index=4
 *
 */
#include<iostream>
#include<vector>

bool verbose = false;

class HeapSort {
    public:
        static void sort(std::vector<int> &v);
    private:
        static void maxheapify(std::vector<int> &v, int i, int n);
        static void swap(std::vector<int> &v, int a, int b)
        {
            int temp = v[a];
            v[a] = v[b]; v[b] = temp;
        }
        static int maxof(std::vector<int> &v, int a, int b)
        {
            if(v[a] > v[b]) return a;
            
            return b;
        }
};

void HeapSort::maxheapify(std::vector<int> &v, int i, int n)
{
    int left = 2 * i;
    int right = 2 * i + 1;

    if(left <= n) {
        if(right > n) {
            //only one child
            if(v[i-1] < v[left-1]) {
                swap(v, i-1, left-1);
                maxheapify(v, left, n);
            }
        } else {
            if(v[right-1] > v[left-1]) {
                if(v[i-1] < v[right-1]) {
                    swap(v, i-1, right-1);
                    maxheapify(v, right, n);
                }
            } else {
                if(v[i-1] < v[left-1]) {
                    swap(v, i-1, left-1);
                    maxheapify(v, left, n);
                }
            }
        }
    }
    return;
}

void HeapSort::sort(std::vector<int> &v)
{
    int n = v.size();

    for(int i = n/2; i >= 1 ; i--)
        maxheapify(v, i, n);

    std::cout << "Output : ";
    for(int i = n; i >= 1; i--) {
        std::cout << v[0] << ' ';
        swap(v, 0, i-1);
        n--;
        maxheapify(v, 1, n);
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
        verbose = true;

    int T;
    std::cin >> T;

    while(T--) {
        int N;
        std::cin >> N;

        std::vector<int> v(N);
        for(int i = 0 ; i < N; i++)
            std::cin >> v[i];

        if(verbose) {
            std::cout << "Input  : ";
            for(std::vector<int>::const_iterator i = v.begin();
                i != v.end();
                i++)
                std::cout << *i << ' ';

            std::cout << std::endl;
        }

        HeapSort::sort(v);

    }

    return 0;
}
