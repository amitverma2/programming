#include<iostream>
#include<vector>
#include<algorithm>

bool debug = false;

void printCard(std::string s)
{
    std::cout << s << " ";
}

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    int T;
    std::cin >> T;

    for(int t = 1; t <= T; t++) {
        std::vector<std::string> pile1;
        std::vector<std::string> pile2;
        std::string ythCard;

        for(int i = 1; i <= 52; i++) {
            std::string card;
            std::cin >> card;
            /* front is bottom */
            if(i > 27)
                pile2.push_back(card);
            else
                pile1.push_back(card);
            if(debug)
                std::cout << card << " ";
        }
        if(debug)
            std::cout << std::endl << "pile1 size " << pile1.size() 
                << " pile2 size " << pile2.size() << std::endl;

        /* make the top of pile at front */
        std::reverse(pile1.begin(),pile1.end());
        if(debug) {
            std::cout << "pile1 from top to bottom" << std::endl;
            std::for_each(pile1.begin(), pile1.end(), printCard);
            std::cout << std::endl;
        }
        if(debug) {
            std::cout << "pile2 from bottom to top" << std::endl;
            std::for_each(pile2.begin(), pile2.end(), printCard);
            std::cout << std::endl;
        }
        int Y = 0;
        for(int i = 1; i <= 3; i++) {
            char c;
            int X;
            switch(c = pile1.front()[0]) {
                case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
                    X = c - '2' + 2;
                    break;
                default:
                    X = 10;
                    break; 
            }
            Y += X;
            pile1.erase(pile1.begin());
            pile1.erase(pile1.begin(), pile1.begin()+(10 - X));
            if(debug) {
                std::cout << "Now pile1 from top to bottom" << std::endl;
                std::for_each(pile1.begin(), pile1.end(), printCard);
                std::cout << std::endl << " X = " << X << " Y = " << Y << std::endl;
            }
        }
        /* make the bottom of pile at front */
        std::reverse(pile1.begin(),pile1.end());
        pile1.insert(pile1.end(), pile2.begin(), pile2.end());

        ythCard = *(pile1.begin()+Y-1);
        std::cout << "Case " << t << ": " << ythCard << std::endl;
    }
    return 0;
}
