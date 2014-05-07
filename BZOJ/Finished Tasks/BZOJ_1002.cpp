#include<cstdio>
#include<cstring>

using namespace std;

#define P 100000
#define For(i,a,b) for (i = a;i <= b;++i)
#define ForDown(i,a,b) for (i = a;i >= b;--i) 
#define fill(a,b) memset(a,b,sizeof(a))

int i,j,k,n,ans[200],f[110][200],t[200],temp[200],t2[200],c;

void minus(int a[],int b[])
{
 	 int k = 0;
 	 fill(temp,0);
 	 printf("*%d", temp[1]);
 	 int i,j;
 	 For(i,1,199) {
	   k += a[i] - b[i];
	   if (k > 0) {
  	     temp[i] = k;k = 0;
       }
       else {
	     temp[i] = k+P;k = -1; 
       } 
	 }
}

void multiply(int a[],int b[])
{
 	 unsigned long long k = 0;
 	 
 	 int i,j;
     fill(temp,0);
 	 For(i,1,100) For(j,1,100) {
       k += temp[i+j-1]+a[i]*b[j];
       temp[i+j-1] = k % P;
       k /= P;
     }
}

int Pop(int a[])
{
 	int i;
 	ForDown(i,199,1) if (a[i] != 0) return i;
}

int GetDigit(int x)
{
 	int k = 1,sum = 0;
 	while (k < x) {
      ++sum;k *= 10;
    }
    return sum;
}

int main()
{
 	freopen("input.txt" , "r" , stdin);
 	freopen("output.txt" , "w" , stdout);
 	
 	fill(ans,0);fill(f,0);fill(t,0);
 	scanf("%d", &n);
 	f[1][1] = 1;f[2][1] = 1;f[3][1] = 4;f[4][1] = 3;t[1] = 3;
 	For(i,5,n) {
      multiply(f[i-2],t);
      
	  minus(t2,f[i-4]);
	  For(j,1,199) f[i][j] = temp[j];  
    }
    
    t[1] = 5;
    printf("%d\n", f[n][1]);
    multiply(f[n],f[n]);
    For(j,1,199) t2[j] = temp[j];
  //  For (i,1,2) printf("%d\n", temp[i]);
    if (n % 2 == 0) multiply(t2,t);
    //For (i,1,2) printf("%d\n", temp[i]);
 	For(j,1,199) ans[j] = temp[j];
 	
    //For(i,1,n) printf("%d\n", ans[i]);
    //printf("%d\n", ans[1]);
	k = Pop(ans); 
	printf("%d\n", k);
	printf("%d", ans[k]);
	ForDown(i,k-1,1){
      j = GetDigit(ans[i]);
      For(j,j,4) printf("0");
	  printf("%d", ans[i]); 
	}
	printf("\n"); 
 	return 0;
}
