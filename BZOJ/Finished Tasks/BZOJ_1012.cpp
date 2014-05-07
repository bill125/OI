/*
  Task: BZOJ_1012
  Created: 2012.03.08
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

const int maxM = 200000+10;
int i,j,M,D,N = 0,top = 0,k = 0,Last = 0;
int f[maxM],s[maxM],q[maxM];
char c;

int getfather(int x)
{
 	if (f[x] == x) return x;
    return f[x] = getfather(f[x]);
}

void Merge(int x,int y)
{
 	 f[y] = x;
}

int main()
{
 	scanf("%d %d\n", &M, &D);
	while (M--) {
      scanf("%c %d\n", &c, &k);
	  if (c == 'A') {
	 	s[N] = (k+Last) % D;f[N] = N;
	 	while (top && s[q[top-1]] <= s[N]) 
		  Merge(N,q[top-1]),--top;
		q[top++] = N++;  
	  }
 	  else {
	    k = N-k;
	    printf("%d\n", Last=s[getfather(k)]);
	  }
    }
 	
 	return 0;
}
