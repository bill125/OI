/*
  Task: BZOJ_1053
  Created: 2012.04.18
  Author: Zhu Jiahao
  Updated: 2012.04.19
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define lowbit(x) ((x) & -(x))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int Len = 15,INF = 2147483647;
int N;
ll hash[Len],ans;
int ansNum;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void getHash()
{
 	 int j = 1;
 	 rep(i,Len) {
       bool flag;
       do {
   	     ++j;
         flag = true;
         rep(k,i) 
 	       if (j % hash[k] == 0) {
             flag = false;break;
           }
       } while (!flag);
       hash[i] = j;
     }
}

void Find(int x,int LastPos,ll sum,int num)
{
 	 if (num > ansNum || (ansNum == num && sum < ans)) {
       ans = sum;ansNum = num;
	 } 
     if (x == Len) return;
	 ll k = sum;
     rep(i,LastPos+1) {
       Find(x+1,i,k,num*(i+1));
       k *= hash[x];
       if (k > N) return;
     }
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d", &N);
	getHash();
	ans = ansNum = 0;
	Find(0,15,1,1);
    printf("%d\n", ans);
	
	return 0;
}
