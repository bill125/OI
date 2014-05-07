#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <queue>
 
using namespace std;
 
typedef long long ll;
typedef double db;
#define rep(i,n) for (int i = 0;i < n;++i)
#define repD(i,n) for (int i = n-1;i >= 0;--i)
#define For(i,a,b) for (int i = a;i <= b;++i)
#define ForD(i,a,b) for (int i = a;i >= b;--i)
#define ForE(i,a) for (int i = h[a];i != -1;i = E[i].next)
#define formap(i,e) for (map<int,int>::const_iterator i = e.begin();i != e.end();++i)
#define fill(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define gi gI()

const int inf = ~0U>>1,maxe = 4000000+10,maxn = 100000+10;
int n,m,tot = -1,cnt,ansl = 0;
int h[maxn],q[maxn],d[maxn],ans[maxn];
struct Edge {
	int next,to;
}E[maxe];
struct Node {
	Node *next;
	Node (int);
	int i;
}*head,*null;

Node::Node(int i) : next(null),i(i) {}

void setIO(string name)
{
    #ifndef ONLINE_JUDGE
    string in = name + ".in";
    string out = name + ".out";
    freopen(in.c_str() , "r" , stdin);
    freopen(out.c_str() , "w" , stdout);
	#endif
}

int gI()
{
	char c = getchar();
	while ((c < '0' || c > '9') && c != '-') c = getchar();
	int p = 0,flag = 1;
	if (c == '-') flag = -1,c = getchar();
	while (c >= '0' && c <= '9') p = p*10 + c-'0',c = getchar();
	return p*flag;
}

void addedge(int a,int b) {
	++tot;
	E[tot].to = b,E[tot].next = h[a],h[a] = tot;
}

void del(Node *t) {
	t->next = t->next->next;
}

int main()
{
	setIO("test"); 
	
	n = gi,m = gi;
	rep(i,n) h[i] = -1;
	rep(i,m) {
		int a = gi-1,b = gi-1;
		addedge(a,b),addedge(b,a);
	}
	//init
	null = new Node(-1);
	head = null;head->next = null;
	//Build_List
	rep(i,n) {
		Node *t = new Node(i);
		t->next = head->next,head->next = t;
	}
	//Run
	fill(d,0),cnt = 0;
	while (head->next!=null) {
		int l = 0,r = 1;++ansl;
		q[1] = head->next->i;
		del(head);
		while (l^r) {
			cnt += r-l;
			while (l^r) {
				++l;
				ForE(i,q[l]) ++ d[E[i].to];
			}
			Node *t = head;
			while (t->next != null) 
				if (d[t->next->i] != cnt) {
					q[++r] = t->next->i;
					del(t);
				}
				else t = t->next;
		}
		ans[ansl-1] = r;
	}
	
	printf("%d\n", ansl);
	sort(ans,ans + ansl);
	rep(i,ansl) printf("%d ", ans[i]);
	puts("");
		
	return 0;
}
