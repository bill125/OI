struct Node {
	Node *s[2], *p;
	int sz,v;
	Node () ;
	int d() {
		return p->s[1] == this;
	}
	void sets(Node *t,int d) {
		t->p = this;
		s[d] = t;
	}
	void relax() ;
	void upd() ;

}Tnull,*null = &Tnull, *root;
Node::Node () {
	s[0] = s[1] = p = null;
	sz = v = 0;
};
void Node::upd() {
	sz = s[0]->sz + 1 + s[1]->sz;
}
void Node::relax() {
}

Node* mk(int k) {
	Node* C = new Node;
	C->v = k;
	C->sz = 1;
	return C;
}

void rotate(Node *t) {
	Node *p = t->p;
	p->relax();
	t->relax();
	int d = t->d();
	p->p->sets(t,p->d());
	p->sets(t->s[d^1],d);
	t->sets(p,d^1);
	p->upd();
	if (root == p) root = t;
}

void splay(Node *t,Node *top = null) {
	while (t->p != top) 
		if (t->p->p == top)
			rotate(t);
		else {
			(t->d() == t->p->d()) ? rotate(t->p) : rotate(t);
			rotate(t);
		}
	t->upd();
}

Node* build(int l,int r,int *A) {
	if (l >= r) return null;
	int m = (l + r) >> 1;
	Node *t = mk(A[m]);
	t->sets(build(l,m,A),0);
	t->sets(build(m+1,r,A),1);
	t->upd();
	return t;
}

Node* select(int k) {
	for (Node *t = root;;) {
		t->relax();
		int c = t->s[0]->sz + 1;
		if (k == c)
			return t;
		else
			if (k > c) 
				k -= c,t = t->s[1];
			else
				t = t->s[0];
	}
}

Node *get(int l,int r) {
	Node *L = select(l);
	Node *R = select(r+2);
	splay(L),splay(R,L);
	return R->s[0];
}
