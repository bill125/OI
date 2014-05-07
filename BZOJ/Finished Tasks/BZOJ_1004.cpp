#include<cstdio>
#include<string>

using namespace std;

int i,j,k,n,m,h,s[2500010],c[2500010],cnt[1000010];
long long ans;
bool v[1000010];

int ask(int l,int r)
{
 	int now = 2147483647;
 	int i = l + (1 << h) - 1,j = r + (1 << h) + 1;
 	while (i + 1 < j) {
      if (i % 2 == 0) now = min(now,s[i+1]);
      if (j % 2 == 1) now = min(now,s[j-1]);
      i /= 2;j /= 2;
	}
	return now;
}

void change(int l,int r,int k)
{
 	 int i = l + (1 << h) - 1,j = r + (1 << h) + 1;
 	 while (i + 1 < j) {
       if (i % 2 == 0) c[i+1] = max(c[i+1],k);
       if (j % 2 == 1) c[j-1] = max(c[j-1],k);
       i /= 2;j /= 2;
     }
}

int main()
{
 	freopen("input.txt" , "r" , stdin);
 	freopen("output.txt" , "w" , stdout);
 	
 	memset(c,0,sizeof(c));
 	scanf("%d%d", &n, &m);
 	h = 0;
 	while (1 << h < n+2) ++h;
 	for (i = 1;i <= 1 << (h+1);++i) s[i] = 2147483647;
 	for (i = 1;i <= n;++i) {
	  scanf("%d", &k);
	  s[i+(1 << h)] = k;
	}
	for (i = n+1;i <= 1 << h;++i) s[i+(1 << h)] = 2147483647;
	for (i = (1 << h)-1;i >= 1;--i) 
	  if (s[i*2+1] < s[i*2]) s[i] = s[i*2+1];
	  else s[i] = s[i*2];
 	for (i = m;i <= n;++i) {
	  j = i-m+1;
      k = ask(j,i);
      change(j,i,k);
	}
	for (i = 1;i < 1 << h;++i) {
	  c[i*2] = max(c[i*2],c[i]);
	  c[i*2+1] = max(c[i*2+1],c[i]);
	}
 	for (i = 1;i <= n;++i) ans += s[i+(1 << h)] - c[i+(1 << h)];
	//printf("%lld\n", ans);
	ans = n;cnt[0] = 1;
	memset(v,false,sizeof(v));
	for (i = 1;i <= n;++i) {
	  k = i+(1 << h);
	  if (cnt[c[k]] > 0) {
        --ans;v[i] = true;
	  }
	  else ++cnt[c[k]];
	  if (k >= m && !v[i-m+1]) --cnt[c[k-m+1]];
    } 
    printf("%lld\n", ans);
 	
 	return 0;
}
