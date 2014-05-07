/*
  Task: BZOJ_1089
  Created: 2012.07.02
  Author: Zhu Jiahao
  Updated: 2012.07.03
*/
   
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
   
using namespace std;
   
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = a;i != -1;i = E[i].next)
#define sqr(a) ((a)*(a))
#define shl(a,b) ((a) << (b))
#define shr(a,b) ((a) >> (b))
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define fill(a,b) memset(a,b,sizeof(a))
#define abs(x) ((x) > 0 ? (x) : (-(x)))
#define pb push_back
   
const int INF = 2147483647,maxN = 32+10,maxD = 32+10,maxL = 1000+10,P = 10000;
int N,D;
struct LongNum
{
       int A[maxL];
       int L;
}tmp,f[maxD];
int B[5];
   
void setIO(string name)
{
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
}
   
LongNum Multi(LongNum a,LongNum b)
{
        LongNum res;
        res.L = 0,fill(res.A,0);
        ll k = 0;
        rep(i,a.L) {
          rep(j,b.L) {
            k += res.A[i+j]+a.A[i]*b.A[j];
            res.A[i+j] = k % P;
            k /= P;
          }
          int l = i+b.L;
          while (k > 0) {
            k += res.A[l];
            res.A[l] = k % P;
            k /= P,++l;
          }
          if (l > res.L) res.L = l;
        }
        return res;
}
   
LongNum Plus(LongNum a,LongNum b)
{
        int l = max(a.L,b.L),k = 0;
        rep(i,l) {
          k += a.A[i] + b.A[i];
          a.A[i] = k % P;
          k /= P;
        }
        while (k > 0) {
          a.A[l] = k % P;
          k /= P,++l;
        } 
        a.L = l;
        return a;
}
   
LongNum Minus(LongNum a,LongNum b)
{
        int l = max(a.L,b.L),k = 0;
        rep(i,l) {
          k += a.A[i] - b.A[i];
          if (k < 0) a.A[i] = k+P,k = -1;
          else a.A[i] = k,k = 0;
        }
        if (a.A[a.L-1] == 0) --a.L;
        return a;
}
   
int main()
{
    //setIO("test");
       
    scanf("%d %d", &N, &D);
    int l = 0;
    repD(i,6) if (N >= shl(1,i)) {
      B[l] = i,++l,N -= shl(1,i);
    }
    rep(i,D+1) fill(f[i].A,0),f[i].L = 0;
    f[0].L = f[0].A[0] = 1,f[1].L = 1,f[1].A[0] = 2;
    For(i,2,D) {
      f[i] = f[0];tmp = f[i-1];
      int k = 0;
      repD(j,l) {
        while (k < B[j]) {
          tmp = Multi(tmp,tmp);
          ++k;
        }
        f[i] = Multi(f[i],tmp);
      }
      f[i] = Plus(f[i],f[0]);
    }
    f[D] = Minus(f[D],f[D-1]);
    repD(i,f[D].L)
      if (i == f[D].L-1) printf("%d", f[D].A[i]);
      else  printf("%04d", f[D].A[i]);
    printf("\n");
       
    return 0;
}