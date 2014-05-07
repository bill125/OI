/*
  Task: BZOJ_1029
  Created: 2012.03.19
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))

const int maxN = 150000+10;
int N,ans = 0;
int num[maxN];
long long T1[maxN],T2[maxN],Heap[maxN];

bool cmp(int a,int b)
{
 	 return T2[a] < T2[b];
}

void Up(int x)
{
 	 while (x != 1 && Heap[x] > Heap[x/2]) swap(Heap[x],Heap[x/2]),x /= 2;
}

void Down(int x)
{
 	 int t;
 	 while (x*2 <= ans && (Heap[x*2] > Heap[x] || Heap[x*2+1] > Heap[x])) {
       t = (Heap[x*2] > Heap[x*2+1]) ? x*2 : x*2+1;
       swap(Heap[x],Heap[t]);x = t;
	 }
}

void Add(int x)
{
 	 Heap[ans] = x;
 	 Up(ans);
}

int main()
{
	scanf("%d", &N);
	rep(i,N) 
	scanf("%d %d", &T1[i], &T2[i]),num[i] = i;
	sort(num,num + N,cmp);
	fill(Heap,0);
	int now = 0;
	rep(k,N) {
      int i = num[k];
	  if (now + T1[i] <= T2[i]) now += T1[i],++ans,Add(T1[i]);
	  else if (Heap[1] > T1[i]) now -= Heap[1]-T1[i],Heap[1] = T1[i],Down(1);
	}
	printf("%d\n", ans);
	
	return 0;
}
