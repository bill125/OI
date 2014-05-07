/*
  Task: BZOJ_1024
  Created: 2012.03.11
  Author: Zhu Jiahao
*/

#include<cstdio>

using namespace std;

#define For(i,a,b) for (i = a;i <= b;++i)

int i,j,k,N;
double X,Y;

double max(double a,double b) 
{
     if (a < b) return b;
     else return a;
}

double min(double a,double b)
{
     if (a < b) return a;
     else return b;
}

double solve(double w,double h,int step)
{
     if (step == 1) return max(w/h,h/w);
     double res = 10000+10; 
     int i;double t1,t2,t3,t4;
     For(i,1,step-1) {
       t1 = solve(w/(double)step*(double)i,h,i);
       t2 = solve(w/(double)step*(double)(step-i),h,step-i);
       t3 = solve(w,h/(double)step*(double)i,i);
       t4 = solve(w,h/(double)step*(double)(step-i),step-i);
       res = min(res,min(max(t1,t2),max(t3,t4)));
     }
     return res;
}

int main()
{
 	scanf("%lf %lf %d", &X, &Y, &N);
 	printf("%.6lf\n", solve(X,Y,N));
 	
 	return 0;
}
