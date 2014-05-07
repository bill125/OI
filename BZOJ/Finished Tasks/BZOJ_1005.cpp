#include<cstdio>
#include<cstring>
#include<cstdlib>

#define MAXN 20000 
#define For(i,a,b) for (i = a;i <= b;++i)
#define ForDown(i,a,b) for (i = a;i >= b;--i)
#define fill(a,b) memset(a,b,sizeof(a))

using namespace std;

const int P = 10000;
int i,j,k,n,hlmotot = 0,nonl = 0,lst[MAXN];;

struct bign
{
   int s[5000],top;
   bign(){fill(s,0);top = 1;}
   void operator *=(const int a)
   {
      int i;
      For(i,1,top) s[i] *= a;
      For(i,1,top) s[i+1] += s[i] / P,s[i] %= P;
      if (s[top+1]) ++top;
   }
   void operator /=(const int a)
   {
      int rem = 0;
      ForDown(i,top,1) s[i] += rem * P,rem = s[i] % a,s[i] /= a;
      while (!s[top] && top>1) --top;
   }
   void print()
   {
      printf("%d",s[top]);
      ForDown(i,top-1,1)
        printf("%04d",s[i]);
      puts("");
   }
};

int main()
{
 	int n;
    bign res;
    res.s[1] = 1;
    scanf("%d",&n);
    For(i,1,n) {
      scanf("%d", &lst[i]);
      if(lst[i]==-1) ++nonl;
      else hlmotot += lst[i]-1;
    }
    For(i,1,hlmotot) res *= n-2-i+1;
    For(i,1,n)
      if (lst[i] != -1)
        For(j,2,lst[i]-1)
          res /= j;
    For(i,1,n-2-hlmotot) res *= nonl;
    res.print();
    return 0;
}
