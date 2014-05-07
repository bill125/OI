/*
  Task: Chores
  Created: 2012.03.25
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
#define ForE(i,a) for (int i = a;i != 0;i = next[i])
#define shl(a,b) (a << b)
#define shr(a,b) (a >> b)
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back

const int maxN = 2000+10;
int N,A,B,a[maxN],b[maxN],c[maxN];

int main()
{
	scanf("%d %d %d", &N, &A, &B); 
	rep(i,N) scanf("%d", &a[i]);
	sort(a,a + N);
	int cnt = 0;b[0] = a[0];c[0] = 1;
	For(i,1,N-1) 
	  if (a[i] != a[i-1]) b[++cnt] = a[i],c[cnt] = 1;
	  else ++c[cnt];
    ++cnt;
    int k = 0;
    int t;
	rep(i,cnt) {
      k += c[i];t = i;
      if (k >= B) break;
	}
	if (k == B) printf("%d\n", b[t+1]-b[t]);
    else printf("0\n");
	
	return 0;
}
