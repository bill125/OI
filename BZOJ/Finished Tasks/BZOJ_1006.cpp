/*
  Task: BZOJ_1006
  Created: 2012.02.24
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>

using namespace std;

#define For(i,a,b) for (i = a;i <= b;++i)
#define ForD(i,a,b) for (i = a;i >= b;--i)
#define ForE(i,a) for (i = a;i != 0;i = next[i])
#define fill(a,b) memset(a,b,sizeof(a))
#define max(a,b) (a > b) ? a : b

const int maxN = 10000+10,maxM = 1000000+10;
int i,j,k,n,m,maxj,a,b,t,cnt = 0,ans = 0;
int e[maxM*2],next[maxM*2],h[maxN],label[maxN],q[maxN],hash[maxN];
bool v[maxN];

void addedge(int x,int y)
{
 	 ++cnt;
 	 next[cnt] = h[x];h[x] = cnt;e[cnt] = y;
}

int main()
{
    freopen("in" , "r" , stdin);
    
 	scanf("%d%d", &n, &m);
 	For(i,1,m) {
      scanf("%d%d", &a, &b);
      addedge(a,b);addedge(b,a);
    }
    fill(label,0);fill(v,0);
    label[-1] = -1;
	ForD(i,n,1) {
      maxj = -1;
      For(j,1,n) 
        if (!v[j] && label[j] > label[maxj]) 
          maxj = j;
      q[i] = maxj;
      ForE(j,h[maxj]) ++label[e[j]]; 
      v[maxj] = true;
	}
	fill(hash,0);fill(label,0);
	label[q[n]] = 1;
	ForD(i,n-1,1) {
      t = q[i];
      ForE(j,h[t]) hash[label[e[j]]] = i;
      For(j,1,n) 
        if (hash[j] != i) {
	      label[t] = j;
	      break;
        }
	}
	For(i,1,n) ans = max(ans,label[i]);
 	
 	printf("%d\n", ans);
 	return 0;
}
