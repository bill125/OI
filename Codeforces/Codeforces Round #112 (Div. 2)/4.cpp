#include<cstdio>
#include<cstring>

using namespace std;

#define For(i,a,b) for (i = a;i <= b;++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define ForE(i,a) for (i = a;i != 0;i = next[i])
#define rep(i,n) for (i = 0;i < n;++i)

const int maxN = 10000+10;
int i,j,k,x,y,N,cnt;
int a[maxN],b[maxN],d[maxN],s[maxN],q[maxN],e[maxN*2],next[maxN*2],h[maxN],hash[maxN];
bool v[maxN];

int lowbit(int x)
{
 	return x & -x;
}

void add(int x,int p)
{
 	 while (x < N) {
       ++d[x];
       x += lowbit(x);
	 }
}

int sum(int x)
{
 	int cnt = 0;
 	while (x > 0) {
      cnt += d[x];
      x -= lowbit(x);
    }
    return cnt;
}

void addedge(int a,int b)
{
 	 ++cnt;
 	 e[cnt] = b;next[cnt] = h[a];h[a] = cnt;
}

int main()
{
 	freopen("input.txt" , "r" , stdin);
 	freopen("output.txt" , "w" , stdout);
 	
    scanf("%d", &N);
    For(i,1,N-1) {
      scanf("%d %d", &a[i], &b[i]),++d[--a[i]],++d[--b[i]];
      addedge(a[i],b[i]);addedge(b[i],a[i]);
	}
 	rep(i,N) if (d[i] == 1) break;
 	fill(v,false);fill(d,0);fill(map,false);
    q[0] = i,v[i] = true,s[0] = 0,d[0] = 1;hash[i] = 0;
	rep(i,N-1) 
      ForE(j,h[q[i]]) 
	    if (!v[e[j]]) {
          q[i+1] = e[j];hash[e[j]] = i+1;v[e[j]] = true;
		  d[i] = 1,s[i+1] = s[i]+1;
		  map[q[i]][e[j]] = true;
        }
 	
    scanf("%d", &M);
 	rep(i,M) {
	  scanf("%d", &k);
	  if (k == 1) {
	 	scanf("%d", &k);
	    x = addflag(true,k);
	  }
      printf("%d\n", ans);
    }
 	
 	return 0;
}
