/*
 * A data stream is a real-time, continuous, ordered sequence of items. Some examples include sensor
data, Internet traffic, financial tickers, on-line auctions, and transaction logs such as Web usage logs
and telephone call records. Likewise, queries over streams run continuously over a period of time and
incrementally return new results as new data arrives. For example, a temperature detection system of
a factory warehouse may run queries like the following.
Query-1: “Every five minutes, retrieve the maximum temperature over the past five minutes.”
Query-2: “Return the average temperature measured on each floor over the past 10 minutes.”
We have developed a Data Stream Management System called Argus, which processes the queries
over the data streams. Users can register queries to the Argus. Argus will keep the queries running
over the changing data and return the results to the corresponding user with the desired frequency.
For the Argus, we use the following instruction to register a query:
Register Q num P eriod
Q num (0 < Qnum ≤ 3000) is query ID-number, and P eriod (0 < P eriod ≤ 3000) is the interval
between two consecutive returns of the result. After P eriod seconds of register, the result will be
returned for the first time, and after that, the result will be returned every P eriod seconds.
Here we have several different queries registered in Argus at once. It is confirmed that all the
queries have different Q num. Your task is to tell the first K queries to return the results. If two or
more queries are to return the results at the same time, they will return the results one by one in the
ascending order of Q num.
Input
The first part of the input are the register instructions to Argus, one instruction per line. You can
assume the number of the instructions will not exceed 1000, and all these instructions are executed at
the same time. This part is ended with a line of ‘#’.
The second part is your task. This part contains only one line, which is one positive integer K
(≤ 10000).
Output
You should output the Q num of the first K queries to return the results, one number per line.
Sample Input
Register 2004 200
Register 2005 300
#
5
Sample Output
2004
2005
2004
2004
2005
*/

#include<iostream>
#include<queue>

bool debug = false;

class Query {
    public:
    int period;
    int queryNum;
    int next;
    Query(int q, int p, int n) : queryNum(q), period(p), next(n) { }
    void incrementNext(void) { next += period; }
};

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    auto cmp = [](const Query &q1, const Query &q2)
    {
        if(q1.next > q2.next) return true;
        if(q2.next > q1.next) return false;

        // both nexts are same
        if(q1.queryNum > q2.queryNum) return true;
        if(q2.queryNum > q1.queryNum) return false;

        return false; // should not hit as q numbers are never repeated
    };
    std::priority_queue<Query, std::vector<Query>, decltype(cmp)> queriesQ(cmp);

    std::string instruction;
    do {
        std::cin >> instruction;
        if(instruction == "Register") {
            int q, p;
            std::cin >> q >> p;
            queriesQ.push(Query(q, p, p));
        } else if(instruction == "#") {
            int K;
            std::cin >> K;
            for(int k = 1; k <= K; k++) {
                Query q = queriesQ.top();
                queriesQ.pop();
                std::cout << q.queryNum << std::endl;
                q.next += q.period;
                queriesQ.push(q);
            }
            break;
        }
    } while(1);

    return 0;
}
