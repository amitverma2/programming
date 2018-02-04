#include <string> 
#include <vector> 
#include <map> 
#include <set> 
#include <queue> 
#include <bitset> 
#include <algorithm> 

#include <iostream> 
#include <sstream> 

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <string.h> 
#include <ctype.h> 

#define pi acos(-1.0) 
#define EPS 1e-9 
#define INF 1e9 

using namespace std; 

 int can_win (vector <int> p) 
  { 
   int d=0,n,i; 
   n=p.size(); 
   for (i=n-1;i>=0;i-=2) 
    if (i-1>=0) 
     d^=(p[i]-p[i-1]); 
   return d; 
  } 

 string solve (vector <int> p) 
  { 
   int i,cur,s,pos,k; 
   vector<int> b; 
   char c[1024]; 
   s=(int)INF; 
   p.push_back(0); 
   sort(p.begin(),p.end()); 
   cur=0; 
   for (i=1;i<p.size();i++) 
    { 
     b=p; 
     for (k=cur;k<p[i];k++) 
      { 
       b[i]=k; 
       if (can_win(b)==0 && s>p[i]-k) 
        { 
         s=p[i]-k; 
         pos=i-1; 
        } 
      } 
     cur=p[i]; 
    } 
   if (s==(int)INF) return "YOU LOSE"; 
   sprintf(c,"TAKE %d STONES FROM PILE %d",s,pos); 
   return (string)c; 
  } 

 struct StoneGameStrategist  
  { 
   string play(vector <int> piles)  
    { 
     return solve(piles); 
    } 
    

  }; 

int main(int argc, char *argv[])
{
    int N;
    std::cin >> N;
    std::vector<int> piles(N);
    for(int i = 0 ; i < N; i++)
        std::cin >> piles[i];

    StoneGameStrategist sgs;
    std::cout << sgs.play(piles) << std::endl;
    return 0;
}
