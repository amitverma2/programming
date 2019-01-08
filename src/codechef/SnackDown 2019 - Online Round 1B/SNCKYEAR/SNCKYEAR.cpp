#include<iostream>

bool debug = false;

bool hosted[10] = {
    true, // 2010
    false,
    false,
    false,
    false,
    true, // 2015
    true, // 2016
    true, // 2017
    false,
    true
};

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    int T;
    std::cin >> T;
    while(T-- > 0) {
        int N;
        std::cin >> N;

        if(hosted[N-2010])
            std::cout << "HOSTED" << std::endl;
        else
            std::cout << "NOT HOSTED" << std::endl;
    }
    return 0;
}
