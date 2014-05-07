/*
  Task: BZOJ_1588
  Created: 2012.03.17
  Author: Zhu Jiahao
*/

#include<cstdio>  
#include<iostream>  

using namespace std;  

#define For(i,a,b) for (i = a;i <= b;++i)

const int maxM = 1000000+10,maxN = 30000+10;  
int L[maxM],R[maxM],S[maxM],V[maxM];  
bool p[maxM];  
int i,x,y,n,a,tt = 0,root = 0,ans = 0;  

void Right_Rotate(int &t)  
{  
    int k = L[t];  
    L[t] = R[k];R[k] = t;S[k] = S[t];  
    S[t] = S[L[t]] + S[R[t]] + 1;  
    t = k;  
}  

void Left_Rotate(int &t)  
{  
    int k = R[t];  
    R[t] = L[k];L[k] = t;S[k] = S[t];  
    S[t] = S[L[t]] + S[R[t]] + 1;  
    t = k;  
}  

void maintain(int &t,bool flag)  
{  
    if (flag)  
      if (S[R[R[t]]] > S[L[t]])  
        Left_Rotate(t);  
      else if(S[L[R[t]]] > S[L[t]])  
        Right_Rotate(R[t]),Left_Rotate(t);  
      else return;  
    else  
      if(S[L[L[t]]] > S[R[t]])  
        Right_Rotate(t);  
      else if (S[R[L[t]]] > S[R[t]])  
        Left_Rotate(L[t]),Right_Rotate(t);  
      else return;  
    maintain(L[t],0);  
    maintain(R[t],1);  
    maintain(t,0);  
    maintain(t,1);  
}  

void Insert(int &t,int v)  
{  
    if (t) {  
      ++S[t];  
      if (v < V[t]) Insert(L[t],v);  
      else Insert(R[t],v);  
      maintain(t,v >= V[t]);  
    }  
    else {  
      V[t = ++tt] = v;  
      S[t] = 1;  
      L[t] = R[t] = 0;  
    }  
}  

int Pred(int t,int v)  
{   
    if (!t) return v;  
    if (v <= V[t]) return Pred(L[t],v);  
    else {  
      int tmp = Pred(R[t],v);  
      return tmp==v?V[t]:tmp;  
    }  
}
  
int Succ(int t,int v)  
{  
    if(!t) return v;  
    if(v >= V[t])return Succ(R[t],v);  
    else {  
      int tmp = Succ(L[t],v);  
      return tmp == v ? V[t] : tmp;  
    }  
}  

int main()  
{  
    scanf("%d %d", &n, &a);  
    p[ans = a] = 1;  
    Insert(root,a);  
    For(i,1,n-1) {  
      if (scanf("%d", &a) == EOF) a = 0;  
      if (!p[a]) {  
        if (!(x = a-Pred(root,a))) x = maxM;  
        if (!(y = Succ(root,a)-a)) y = maxM;  
        ans += min(x,y);  
        Insert(root,a);  
        p[a] = 1;  
      }  
    }  
    printf("%d\n",ans);  
    return 0;  
}  
