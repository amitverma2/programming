#include<iostream>

bool debug = false;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    int T;
    std::cin >> T;
    while(T-- > 0) {
        int N, K;
        std::cin >> N >> K;

        int cnt = 0;
        for(int i = 0 ; i < N ; i++) {
            int Ai;
            std::cin >> Ai;
            if(Ai != 1) cnt++;
        }
        if(debug) std::cerr << N << " " << K << " " << cnt << std::endl;
        if(cnt <= K)
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;
    }
    return 0;
}
