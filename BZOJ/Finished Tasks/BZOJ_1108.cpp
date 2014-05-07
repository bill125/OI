#include<cstdio>
typedef long long ll;
inline ll gI() {char c=getchar();while (c<'0' || c>'9') c=getchar();ll p=0;while (c>='0'&&c<='9') p=p*10+(c-'0'),c=getchar();return p;}
int main() {
	ll n=gI(),x,y,ans=0;
	for(int i=0;i<n;++i)x=gI(),y=gI(),ans+=-x+y;
	for(;n--;)x=gI(),y=gI(),ans+=x-y;
	printf("%lld\n",ans);
	return 0;   
}
