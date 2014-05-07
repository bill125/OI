/*
  Task: Supercentral Point
  Created: 2012.03.16
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

#define rep(i,n) for (i = 0;i < n;++i)

const int maxN = 200+10;
int i,j,ans = 0,N;
int x[maxN],y[maxN];
bool flag[4];

int main()
{
 	scanf("%d", &N);
 	rep(i,N) scanf("%d %d", &x[i], &y[i]);
 	rep(i,N) {
      rep(j,4) flag[j] = false;
      rep(j,N) {
        if (x[i] == x[j] && y[i] < y[j]) flag[0] = true;
        if (x[i] == x[j] && y[i] > y[j]) flag[1] = true;
        if (y[i] == y[j] && x[i] < x[j]) flag[2] = true;
        if (y[i] == y[j] && x[i] > x[j]) flag[3] = true;
	  }
	  ++ans;
	  rep(j,4) if (!flag[j]) {
        --ans;break;
      }
    }
    printf("%d\n", ans);
 	
 	return 0;
}
