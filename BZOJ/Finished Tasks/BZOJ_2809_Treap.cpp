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
using std::make_pair;
 
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

const int inf = ~0U>>1,maxn = 100000+10;
int n,m;
int f[maxn],d[maxn],q[maxn];
bool v[maxn];
ll L[maxn];

bool random(db p) {return (db) rand()/RAND_MAX < p;}
struct Node;
typedef std::pair <Node*, Node*> Pair;
struct Node {
	ll key,size,sum;
	Node *left, *right;
	Node (ll);
	int getpos(ll);
	Pair split(ll);
	Node* update() {
		size = left->size + right->size + 1;
		sum = left->sum + right->sum + key;
		return this;
	}
	int Max(ll);
	void print();
};

Node *null,*p[maxn];
Node::Node(ll key) : key(key),size(1),sum(key),left(null),right(null) {}

void Node::print() {
	if (this == null) return;
	left->print();
	printf("%lld ", key);
	right->print();
}

Node* merge(Node* p,Node* q) {
	if (p == null) return q;
	if (q == null) return p;
	if (random((db)p->size/(p->size+q->size))) {
		p->right = merge(p->right,q);
		return p->update();
	}
	else {
		q->left = merge(p,q->left);
		return q->update();
	}
}

Pair Node::split(ll k) {
	if (this == null) return make_pair(null,null);
	if (k<=left->size) {
		Pair t = left->split(k);
		left = null;
		this->update();
		return make_pair(t.first,merge(t.second,this));
	}
	else {
		Pair t= right->split(k-left->size-1);
		right = null;
		this->update();
		return make_pair(merge(this,t.first),t.second);
	}
}

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

void init() {
	null = new Node(0);
	null->left = null->right = null;
	null->size = 0;
}

int Node::getpos(ll k) {
	if (this == null) return 0;
	if (k < key) return left->getpos(k);
	if (k == key) return left->size+1;
	return left->size+1+right->getpos(k);
}

Node *Insert(Node *p, ll k) {

	int t = p->getpos(k);
	Pair res = p->split(t);
	Node *New = new Node(k);
	return merge(merge(res.first,New),res.second);
}

int Node::Max(ll k) {
	if (this == null) return 0;
	if (k < left->sum+key) return left->Max(k);
	k -= left->sum + key;
	if (k <= 0) return left->size+1;
	else return left->size+1+right->Max(k);
}

Node* Merge(Node* p,Node* q) {
	if (p==null) return q;
	q = Merge(p->left,q);
	q = Merge(p->right,q);
	return Insert(q,p->key);
}

int main()
{
	setIO("test"); 
	
	cin >> n >> m;
	init();
	rep(i,n) {
		f[i] = gi-1;
		if (f[i] != -1) ++d[f[i]];
		p[i] = new Node((ll)gi);
		L[i] = (ll)gi;
	}
	int r = 0;
	rep(i,n) if (!d[i]) q[r++] = i;
	rep(i,n) if (f[q[i]]>=0 && --d[f[q[i]]] == 0) q[r++] = f[q[i]];
	ll ans = 0;
	rep(i,n) {
		int k = q[i];
		ll t = (ll)p[k]->Max(m)*L[k];
		ans = max(ans,t);
		Node *a = p[k],*b = p[f[k]];
		if (f[k] == -1) continue;
		if (a->size > b->size) swap(a,b);
		p[f[k]] = Merge(a,b);
	}
	cout << ans << endl;
	
	return 0;
}
