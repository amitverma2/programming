#include<iostream>
#include<algorithm>
#include<map>

int main()
{
    int N;

    std::ios_base::sync_with_stdio(false);
    while(std::cin >> N, N) {
        std::map<std::string, int> courseMap;
        int maxFrosh = 0;
        while(N--) {
            std::string score[5];
            std::cin >> score[0] >> score[1] >> score[2] >> score[3] >> score[4];
            sort(score, score+5);
            std::string key = score[0] + score[1] + score[2] + score[3] + score[4];
            courseMap[key]++;
            if(courseMap[key] > maxFrosh)
                maxFrosh = courseMap[key];
        }
        int total = 0;
        for(std::map<std::string, int>::const_iterator i = courseMap.begin();
            i != courseMap.end(); i++)
            if(i->second == maxFrosh) total += maxFrosh;
        std::cout << total << '\n';
    }
    return 0;
}
