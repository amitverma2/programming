#include<iostream>
#include<set>

using namespace std;
typedef std::set<std::pair<int, int> > spii;

bool debug = false;

void find_subseq(spii &subSeqSet, int N, int pos, int K)
{
    int len = 0;

    // with the storage mechanism, the largest subseq
    // is found among the first two entries of the subSeqSet

    spii::const_iterator firstSubSeq = subSeqSet.begin();
    // no sub seq of 1's
    if(firstSubSeq == subSeqSet.end()) {
        std::cout << len << std::endl;
        return ;
    }

    int begin = firstSubSeq->second;
    int end = (firstSubSeq->second - firstSubSeq->first - 1) % N;
    int largestSubSeqSize = - firstSubSeq->first;

    if(debug) {
        std::cerr << "Largest: begin " << begin <<
            ", end " << end << ", size " << largestSubSeqSize
            << std::endl;
        std::cerr << "Pos " << pos << std::endl;
    }

    // check if the position outside the largest subseq
    if(((begin <= end) && !(pos > begin && pos <= end)) ||
       ((begin > end) && !((pos > begin && pos < N) || (pos >= 0 && pos <= end)))) {
        // if thats the case the largest subseq is the first one
        if(debug) std::cerr << "No split." << std::endl;
        len = -firstSubSeq->first;
    } else {
        if(debug) std::cerr << "Split." << std::endl;
        int largestSplit1Len;
        int largestSplit2Len;
        int largestLargestSplitLen;
        // the position is within the largest subseq, need to do more
        // lets see what we get if we break the largest subseq, at pos
        // and one of the child of the largest subseq after breaking
        // is still > K just return K.
        // if the child is < K, then lets check the second largest
        // sub seq (if any), which is surely not broken since the
        // break can happen only at one subsequence, and we made
        // sure to add contiguous subsequence in the sub sequence
        // set, making sure to join the leading and trailing
        // subsequence if we did find both 
        //
        // step 1 find the largest of the splits of largest subseq
        //  step 1.1 does the largest subseq was wrapping at 0
        //           which is to say if the starting index of
        //           largest subseq is less than the ending
        //           index
        if(begin > end) {
            // largest sequence wrapped at 0
            if(pos > begin) {
                // ... begin ..... pos .... (N-1) (0) .... end ....
                largestSplit1Len = pos - begin;
                largestSplit2Len = largestSubSeqSize - largestSplit1Len;
            } else {
                // ... begin ..... (N-1) (0) .... pos ... end ....
                largestSplit2Len = end - pos + 1;
                largestSplit1Len = largestSubSeqSize - largestSplit2Len;
            }
        } else {
            // largest sequence didn't wrap at 0
            // ease case
            // ... begin ..... pos .... end .... (N-1) (0) .....
            largestSplit1Len = pos - begin;
            largestSplit2Len = largestSubSeqSize - largestSplit1Len;
        }
        largestLargestSplitLen = largestSplit1Len;
        if(largestSplit2Len > largestLargestSplitLen)
            largestLargestSplitLen = largestSplit2Len;
        if(largestLargestSplitLen >= K) {
            // no point checking second seq, as we are looking for
            // max K length sub sequences
            len = K;
        } else {
            firstSubSeq++;
            // lets check if the second largest seq is there,
            // and if it is > the first largest seq split max
            if(firstSubSeq != subSeqSet.end()) {
                if(debug)
                    std::cerr << "Checking second largest" << std::endl;
                len = (largestLargestSplitLen >
                       -firstSubSeq->first)?largestLargestSplitLen:
                    (-firstSubSeq->first);
            } else
                // no second seq, the largest of the split is our
                // winner
                len = largestLargestSplitLen;
        }
    }

    if(len > K)
        len = K;

    std::cout << len << std::endl;
}

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    if(argc > 1) debug = true;

    int N, Q, K;
    cin >> N >> Q >> K;

    std::set<std::pair<int,int> > subseqSet;
    bool start_subseq = false;
    int pos_start_subseq = -1;
    bool has_leading = false;
    std::pair<int,int> leadingSubSeq(-1,-1);
    bool saved = false;
    std::pair<int,int> trailingSubSeq(-1,-1);
    bool has_trailing = false;
    for(int n = 0; n < N; n++) {
        int A;
        std::cin >> A;
        if(A) {
            if(n == 0) {
                has_leading = true;
            }
            if(!start_subseq) {
                start_subseq = true;
                pos_start_subseq = n;
            }
        } else {
            if(start_subseq) {
                std::pair<int, int> pii(-(n - pos_start_subseq), pos_start_subseq);
                start_subseq = false;
                pos_start_subseq = -1;
                if(has_leading && !saved) {
                    //if this is the leading subseq lets
                    //wait before we examine the trailing end 
                    saved = true;
                    leadingSubSeq = pii;
                } else {
                    subseqSet.insert(pii);
                }
            }
        }
    }
    // take care of trailing subseq
    if(start_subseq) {
        has_trailing = true;
        std::pair<int, int> pii(-(N - pos_start_subseq), pos_start_subseq);
        trailingSubSeq = pii;
        if(has_leading) {
            //lets join the leading and trailing subseq and add once,
            //it will be broken by default pos of 0
            std::pair<int,int> pii2(leadingSubSeq.first + trailingSubSeq.first,
                                    trailingSubSeq.second);
            subseqSet.insert(pii2);
        } else
            subseqSet.insert(pii);
    }
    if(debug) {
        std::cerr << "SubSeq found = " << subseqSet.size() << std::endl;
        for(spii::const_iterator i = subseqSet.begin();
            i != subseqSet.end();
            i++) {
            std::cerr << "SubSeq of size " << i->first
                << " starting at " << i->second << std::endl;
        }
    }

    std::string query;
    std::cin >> query;

    int pos = 0;
    for(int q = 0; q < Q; q++) {
        if(query[q] == '!') {
            if(pos == 0) {
                pos = N-1;
            } else {
                pos--;
            }
            if(debug) std::cerr << "Pos moved to " << pos << std::endl;
        } else {
            if(debug) std::cerr << "Find command." << std::endl;
            find_subseq(subseqSet, N, pos, K);
        }
    }
    return 0;
}
