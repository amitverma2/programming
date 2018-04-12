#include<iostream>
#include<set>

bool debug = false;

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    std::ios_base::sync_with_stdio(false);

    int n;
    while(std::cin >> n, n) {
        if(debug) std::cout << "Test case with " << n << " days\n";
        std::multiset<int> billsSet;
        long long int total = 0;
        for(int i = 0; i < n; i++) {
            int k = 0;
            std::cin >> k;
            for(int bills = 0 ; bills < k; bills++) {
                int bill;
                std::cin >> bill;
                billsSet.insert(bill);
            }
            int min = *billsSet.begin(); 
            int max = *--billsSet.end();

            total += (max-min);

            if(debug) std::cout << "Day " << i+1 << ' ' << max << ' ' << min << ' ' << total << std::endl;

            billsSet.erase(billsSet.begin());
            billsSet.erase(--billsSet.end());
        }
        std::cout << total << std::endl;
    }
    return 0;
}
