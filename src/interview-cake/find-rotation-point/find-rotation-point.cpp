// Find rotation point problem of interview cake
#include<iostream>
#include<vector>

bool debug = false;

void readInput(std::vector<std::string> &words)
{
    int M;
    std::cin >> M;
    while(M-->0) {
        std::string word;
        std::cin >> word;
        words.push_back(word);
    }
}

void findRotationPoint(std::vector<std::string> &words)
{
    int n = words.size();
    if(n == 0) {
        std::cout << "No words.\n";
        return;
    }
    int begin = 0;
    int end = n-1;
    int cur = 0;

    while(begin < end) {
        cur = (begin + end)/2;
        if(debug) {
            std::cout << "B (" << begin << "): " << words[begin]
                << " C (" << cur << "): " << words[cur]
                << " E (" << end << "): " << words[end]
                << std::endl;
        }
        if(words[begin] < words[end]) {
            std::cout << "No rotation point.\n";
            return;
        }
        if(words[cur] > words[begin]) {
            begin = cur;
        } else {
            end = cur;
        }
    }
    if(debug) std::cout << "(b, c, e) (" << begin << ", " << cur << ", " << end << ")\n";
    std::cout << "Rotation point is at index " << end
       << " = " << words[end] << std::endl;
}

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    // input format
    // N            Number of test cases
    // M1           Number of words in this test case
    // word1
    // word2
    // ...
    // wordM1
    // M2           Number of words in this test case
    // word1
    // word2
    // ...
    // wordM2
    // ...
    // ...
    // MN           Number of words in this test case
    // word1
    // word2
    // ...
    // wordMN
    
    int N;
    std::cin >> N;
    while(N-->0) {
        std::vector<std::string> words;
        readInput(words);
        findRotationPoint(words);
    }
    return 0;
}
