#include<iostream>
#include<iomanip>
#include<map>

int main()
{
    std::ios_base::sync_with_stdio(false); // make life faster
    int T;
    std::cin >> T;
    std::cin.ignore();
    std::cin.ignore();
    while(T--) {
        int total = 0;
        std::map<std::string, int> myMap;

        std::string line;
        while(!getline(std::cin, line) == false) { // techincally the stream only has !() operator
            if(line == "")
                break;
            myMap[line]++;
            total++;
        }
        typedef std::map<std::string, int>::const_iterator CI;
        for(CI i = myMap.begin(); i != myMap.end(); i++)
            std::cout << i->first << " " << std::fixed << std::setprecision(4) << ((double)i->second * 100.0/(double)total) << std::endl;
        if(T) std::cout << std::endl;
    }
    return 0;
}
