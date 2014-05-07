#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <map>
#include <utility>
#include <cstring>

#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define Debug(x) cout<<#x<<"="<<x<<endl;
#define For(i,l,r) for(int i=l;i<=r;i++)
const int inf=~0U>>1,mod=31011,maxn=100,maxm=1000;
using namespace std;
typedef pair<int,int> ii;
struct UF
{
    int F[maxn];
    void clear(){rep(i,maxn)F[i]=i;}
    int find(int x)
    {
        if(F[x]==x)return x;
        return F[x]=find(F[x]);
    }
    bool Union(int i,int j)
    {
        i=find(i);j=find(j);
        return F[i]=j,i!=j;
    }
    UF& operator=(const UF&u)
    {
        memcpy(F,u.F,sizeof(F));
        return *this;
    }
};
int n,m,ans=1,get,ret;
typedef map<int,vector<ii> >::iterator mit;
map<int,vector<ii> > M;
UF All,Link;
vector<ii> now;
void Dfs(int p,int c)
{
    if(p==now.size())
    {
        if(c==get)ret++;
        return;
    }
    ii t=now[p];UF tmp=Link;
    if(Link.Union(t.first,t.second))Dfs(p+1,c+1);
    Link=tmp;
    Dfs(p+1,c);
}
int main()
{
    //freopen("in","r",stdin);
    cin>>n>>m;int s,t,c;
    rep(i,m)  {
        cin>>s>>t>>c;s--;t--;
        M[c].pb(ii(s,t));
    }
    All.clear();s=0;
    for(mit i=M.begin();i!=M.end();i++)
    {
        now=i->second;Link=All;get=0;ret=0;
        rep(j,now.size())get+=All.Union(now[j].first,now[j].second);
        Dfs(0,0);ans*=ret;ans%=mod;s+=get;
    }
    if(s<n-1)cout<<0<<endl;
    else cout<<ans<<endl;
}
