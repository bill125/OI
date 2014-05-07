// Author: bill125
// ntr czr
// orz zyx
// using namespace inline

#include <cstdio>

#define gi gI()
int n,a,cnt,k,p;
int gI() {char c=getchar();while (c<'0' || c>'9') c=getchar();p=0;while (c>='0' && c<='9') p=p*10+(c-'0'),c=getchar();return p;}

int main() {
	n=gi;
	cnt=0,k;
	while (n--) {
		if (cnt==0) a=gi, cnt=1;
		else (a==gi)?++cnt:--cnt;
	}
	printf("%d\n", a);
	
	
	return 0;
}
