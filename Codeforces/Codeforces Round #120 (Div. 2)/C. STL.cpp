/*
  Task:
  Created:
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>

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
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back

const int maxN = 100000+10,INF = 2147483647;
int N,M;
int next[maxN];
string Query[maxN];
char s[maxN*3][5];
char tmp[5];
bool tf;

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

void Error()
{
 	 printf("Error occurred\n");
}

int scan()
{
 	 char c;
     int cnt = 0;
 	 while (scanf("%c", &c) && c != ' ' && c != '\n' && c != 0) {
	   tmp[cnt++] = c; 
     }
	 tmp[cnt] = 0;
     tf = c == '\n' || c == 0;
     return 1;
}

int main()
{
 	//setIO("test");
 	
 	scanf("%d\n", &N);
 	rep(i,N) Query[i] = "int",next[i] = i+1;
 	next[N-1] = -1;
 	M = 0;
 	
	while (scan()) {
	  rep(j,5) s[M][j] = tmp[j];
	  ++M;
	  if (tf) break;
    }
	
	repD(i,M) 
      if (strlen(s[i]) == 3) --N;
      else {
  	    if (N < 0) {Error();return 0;}
        if (next[N] == -1) {Error();return 0;}
        string S = "pair<"+Query[N]+","+Query[next[N]]+">";
        Query[N] = S;
        next[N] = next[next[N]];
	  }
    if (next[0] != -1) {Error();return 0;}
	cout << Query[0] << endl;

	return 0;
}
