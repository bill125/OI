/*
  Task: Wizards and Minimal Spell
  Created: 2012.03.27
  Author: Zhu Jiahao
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<string>
#include<iostream>

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

const int maxN = 1 << 21;
char now[maxN],last[maxN];

int getlen(char c[])
{
 	rep(i,maxN) if (c[i] == 0) return i;
}

bool scan()
{
 	 int i = 0;
 	 char c;
 	 c = getchar();
 	 while (c != 10) {
       if (c == 13) return false;
	   now[i++] = c; 
	   if (scanf("%c", &c) == EOF) return false;
     }
     now[i] = 0;
     return true;
}

int main()
{
 	int nL,lL = -1,cnt = 0;
 	bool lflag = true;
 	while (scan()) {
      nL = getlen(now);
	  bool flag = false;
	  rep(i,nL) 
	    if (now[i] != ' ') {
	      if (now[i] == '#') flag = true;
	      else flag = false;
	      break;
        }
      if (lflag && cnt != 0) printf("\n");
      cnt = 1;
      if (flag) if (!lflag) printf("\n");
      rep(i,nL) if (flag || now[i] != ' ') printf("%c", now[i]); 
      lflag = flag;
    }
    printf("\n");
	
	return 0;
}
