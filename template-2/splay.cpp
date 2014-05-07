struct Node {
	Node *s[2], *p;
	int val, sz;
	int d() { return p->s[1]==this; }
	void sets(Node *t, int d) { t->p=this, s[d]=t; }
	Node ();
	void relax();
	void ref(); 
}mem[maxp], *C=mem, Tnull, *null=&Tnull, *root;
Node::Node () {
	s[0]=s[1]=p=null;
	sz=0;
}
Node *mk(int k) {
	C->val=k;
	C->ref();
	return C++; 
}
void rot(Node *t) {
	Node *p=t->p;
	p->relax();
	t->relax();
	int d=t->d();
	p->p->sets(t, p->d());
	p->sets(t->s[d^1], d);
	t->sets(p, d^1);
	if (root==p) root=t;
	p->ref();
}
void Node::ref() {
	sz=s[0]->sz+1+s[1]->sz;
}
void Node::relax() {
	rep(i,2) if (s[i]!=null) {
	}
}
void splay(Node *t, Node *top=null) {
	t->relax();
	while (t->p!=top) 
		if (t->p->p==top) rot(t); 
		else {
			(t->p->d()==t->d())?(rot(t->p)):(rot(t));
			rot(t);
		}
	t->ref();
}
Node *select(int k) {
	for (Node *t=root;;) {
		t->relax();
		int c=t->s[0]->sz+1;
		if (c==k) return t;
		else if (c<k) k-=c, t=t->s[1];
		else t=t->s[0];
	}
}
Node *build(int l,int r) {
	if (l==r) return null;
	if (l+1==r) {
		Node *now=mk((c[l]=='(')?(-1):1);
		return now;
	}
	int m=(l+r)>>1;
	Node *now=mk((c[m]=='(')?(-1):1);
	now->sets(build(l,m), 0);
	now->sets(build(m+1,r), 1);
	now->ref();
	return now;
}
Node *get(int l,int r) {
	if (l==1 && r==n) return root;
	else if (l==1) {
		Node *t=select(r+1);
		splay(t);
		return t->s[0]; 
	}
	else if (r==n) {
		Node *t=select(l-1);
		splay(t);
		return t->s[1];
	}
	else {
		Node *L=select(l-1), *R=select(r+1);
		splay(L), splay(R,L);
		return R->s[0];
	}
}