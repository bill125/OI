/*
  Task:
  Created:
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long ll;
typedef long double ld; 
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != 0;i = E[i].next)
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back

const int maxN = 100000+10;
int N,M;

struct Item
{
 	   int money,size,num; 	   
}Shoes[maxN],Cus[maxN];

struct Edge
{
 	   int to,next;
}E[maxN];

int h[maxN],prev[maxN],cnt = 0;
bool v[maxN];

bool operator < (Item a,Item b)
{
         return (a.size < b.size);
}

void addedge(int a,int b)
{
 	 E[++cnt].next = h[a];h[a] = cnt;
 	 E[cnt].to = b;
}

bool check(int a,int b)
{
 	 return (a == b || a - 1 == b);
}

bool Find(int x)
{
 	 v[x] = false;
 	 ForE(i,h[x]) 
       if (prev[E[i].to] == -1 || (Find(E[i].to) &&v[prev[E[i].to]])) {
		 prev[E[i].to] = x;
		 return true;
       }
     return false;
}

int main()
{
 	freopen("input.txt" , "r" , stdin);
 	freopen("output.txt" , "w" , stdout);
	
	scanf("%d", &N);
	int x,y;
	rep(i,N) scanf("%d %d", &x, &y),Shoes[i].money = x,Shoes[i].size = y,Shoes[i].num = i;
	sort(Shoes, Shoes + N);
	rep(i,N) printf("%d\n", Shoes[i].size);
	scanf("%d", &M);
	rep(i,N) scanf("%d %d", &x, &y),Cus[i].money = x,Cus[i].size = y;
    rep(i,N) {
      int l = 0,r = N;
      while (l + 1 < r) {
        int mid = (l+r)/2;
        if (Shoes[mid].size <= Cus[i].size) l = mid;
		else r = mid; 
	  }
	  if (check(Shoes[l].size,Cus[i].size) && Shoes[l].money <= Cus[l].money) addedge(i,Shoes[l].num);
	  if (l > 0 && check(Shoes[l-1].size,Cus[i].size) && Shoes[l-1].money <= Cus[l].money) addedge(i,Shoes[l-1].num);
	} 
	int ans = 0;
	rep(i,N) prev[i] = -1;
	rep(i,M) {
      fill(v,true);
      if (Find(i)) ++ans;
	} 
	printf("%d\n", ans);
	rep(i,N) 
      if (prev[i] != -1) 
        printf("%d %d\n", i+1, prev[i]+1);
	
	return 0;
}
