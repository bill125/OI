/*
  Task: Another Problem on Strings
  Created: 2012.03.16
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<string>

using namespace std;

#define rep(i,n) for (i = 0;i < n;++i)

const int maxN = 1000000+10;
long long i,j,k,K,ans;
long long cnt[maxN];
char c[maxN];

int main()
{
 	//freopen("input.txt" , "r" , stdin);
 	//freopen("output.txt" , "w" , stdout);
 	scanf("%d\n", &K);
 	scanf("%s", c);
 	j = 0;
    j = 0,++cnt[j];
    rep(i,maxN) if (c[i] == 0) {
      k = i;break;  
    }
    rep(i,k) {
      if (c[i] == '1') ++j;
	  ++cnt[j];
    } 
	rep(i,j+1) {
	  k = i - K; 
      if (k >= 0) 
	 	if (i != k) ans += cnt[i] * cnt[k];
	 	else ans += cnt[i]*(cnt[i]-1)/2;
	}
	
    printf("%I64d\n", ans);
 	return 0;
}
