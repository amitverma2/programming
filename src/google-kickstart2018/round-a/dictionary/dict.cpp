#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<list>
#include<map>

bool debug = false;

void makeParagraph(std::vector<char> &p,
                  char S1, char S2,
                  int N, int A, int B, int C, int D)
{
    p.push_back(S1);
    p.push_back(S2);
    long long int x1 = S1;
    long long int x2 = S2;
    for(int n = 2; n < N; n++) {
        long long int x = ((A * x2 + B * x1) % D + C) % D;
        p.push_back((char)('a' + (x % 26)));
        x1 = x2;
        x2 = x;
    }
#if 0
    if(debug) {
        for(int i = 0 ; i < N; i++) {
            std::cout << p[i];
        }
        std::cout << std::endl;
    }
#endif
    return;
}

bool matches(std::vector<char> &p, std::string s)
{
    std::vector<int> mapS(26);

    if(debug)
        std::cout << "Matching with " << std::endl << s << std::endl;
    for(int i = 0 ; i < s.size(); i++) {
        mapS[s[i] - 'a']++;
    }
    for(int i = 0; i < p.size(); i++) {
        if(p[i] == s[0]) {
            if(i + s.size() - 1 >= p.size()) {
                return false;
            }
            if(p[i + s.size() - 1] != s[s.size()-1]) {
                continue;
            }
            std::vector<int> mapP(26);
            for(int j = 0 ; j < s.size(); j++)
                mapP[p[i+j] - 'a']++;
            bool match = true;
            for(int j = 0; j < 26; j++) {
                if(mapS[j] != mapP[j]) {
                    match = false;
                    break;
                }
            }
            if(match)
                return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    int T;
    std::cin >> T;
    for(int t = 1; t <= T; t++) {
        int present = 0;
        std::list<std::string> dict;
        int L;
        std::cin >> L;
        for(int l = 0; l < L; ++l)
        {
            std::string word;
            std::cin >> word;
            dict.push_back(word);
        }
        if(debug)
            std::cout << "Dictionary has " << dict.size() << " words." << std::endl;

        std::vector<char> paragraph;
        paragraph.reserve(1000000);

        if(debug)
            std::cout << "Paragraph size is " <<
                paragraph.size() << std::endl;

        char S1, S2;
        int N, A, B, C, D;
        std::cin >> S1 >> S2 >> N >> A >> B >> C >> D;
        makeParagraph(paragraph, S1, S2, N, A, B, C, D);
        if(debug)
            std::cout << "Post construction Paragraph size is " <<
                paragraph.size() << std::endl;
        int dictWord = 1;
        for(std::list<std::string>::const_iterator i = dict.begin();
            i != dict.end();
            i++, dictWord++) {
            if(debug)
                std::cout << "Matching with dictWord " << dictWord << std::endl;
            if(matches(paragraph, *i)) present++;
        }

        std::cout << "Case #" << t << ": " << present << std::endl;
    }

    return 0;
}
