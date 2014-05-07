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

const int INF = 2147483647,maxN = 5,maxL = 1000;
int N;
char Team[maxN][maxL];
struct Score
{
       int A,W,L;
}P[maxN];
bool v[maxN][maxN];
int num[maxN],R[maxN];

void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}

int strlen(char c[])
{
    rep(i,maxL) if (c[i] == 0) return i;
}

int Find(char c[])
{
    int l = strlen(c);
    rep(i,N) {
      bool flag = l == strlen(Team[i]);
      rep(j,l) if (Team[i][j] != c[j]) {
        flag = false; break;
      }
      if (flag) return i; 
    }
    rep(i,l) Team[N][i] = c[i];
    Team[N][l] = 0;
    ++N;
    return N-1;
}

bool small(char c1[],char c2[])
{
     int l1 = strlen(c1),l2 = strlen(c2);
     rep(i,min(l1,l2)) {
       if (c1[i] > c2[i]) return false;
       if (c1[i] < c2[i]) return true;
     }
     if (l1 > l2) return false;
     if (l1 < l2) return true;
}

bool cmp(int a,int b)
{
     return (small(Team[a],Team[b]));
}

bool cmp2(int a,int b)
{
     if (P[a].A > P[b].A) return true;
     if (P[a].A == P[b].A && P[a].W - P[a].L > P[b].W - P[b].L) return true;
     if (P[a].A == P[b].A && P[a].W - P[a].L == P[b].W - P[b].L && P[a].W > P[b].W) return true;
     if (P[a].A == P[b].A && P[a].W - P[a].L == P[b].W - P[b].L && P[a].W == P[b].W && R[a] < R[b]) return true;
     return false;
}

int main()
{
 	//setIO("test");
 	
 	char t[] = "BERLAND";
 	N = 0;
 	Find(t);
 	
 	int X,Y,a,b; 	
 	fill(v,false);
 	rep(i,5) {
      char c1[maxL],c2[maxL];
      scanf("%s %s %d:%d\n", c1, c2, &X, &Y);
      a = Find(c1),b = Find(c2);
      if (X < Y) {
        swap(a,b);swap(X,Y);
      }
      v[a][b] = v[b][a] = true;
      P[a].W += X,P[a].L += Y,P[b].W += Y,P[b].L += X;
      if (X == Y) ++P[a].A,++P[b].A;
      else P[a].A += 3;
    }
    For(i,1,3) if (!v[0][i]) {
      X = 0,Y = i;
      break;
    } 
    rep(i,4) num[i] = i;
    sort(num,num+4,cmp);
    rep(i,4) R[num[i]] = i;
    P[0].A += 3;
    int ansX = 1000,ansY = 0;
    rep(x,100) rep(y,x) {
      P[X].W += x,P[X].L += y,P[Y].W += y,P[Y].L += x; 
      rep(i,4) num[i] = i;
      sort(num,num+4,cmp2);
      P[X].W -= x,P[X].L -= y,P[Y].W -= y,P[Y].L -= x;
      if ((num[0] == 0 || num[1] == 0) && (x - y < ansX - ansY || x - y == ansX - ansY && y < ansY)) {
        ansX = x,ansY = y;
      }
    }
    if (ansX == 1000) printf("IMPOSSIBLE\n");
    else printf("%d:%d\n", ansX, ansY);
    
	return 0;
}
