int r;
struct Node {
	Node *s[26], *Fail;
	int tot;
	Node () ;
}Tnull, *null=&Tnull, *root=null, *ans[maxn], *q[maxl];
Node::Node() { tot=0, Fail=null; rep(i,26) s[i]=null; }
Node *mk() { return new Node; }

Node* Insert(int l,char c[]) {
	Node *t=root;
	rep(i,l) {
		int k=c[i]-'a';
		if (t->s[k]==null) t->s[k]=mk();
		t=t->s[k];
	}
	return t;
}
void PreWork() {
	r=1;q[0]=root;
	rep(i,r) {
		Node *x=q[i];
		rep(j,26) if (x->s[j]!=null) { 
			Node *t=x->Fail;
			for (; t!=null && t->s[j]==null; t=t->Fail) ;
			x->s[j]->Fail=(t==null)?root:t->s[j];
			q[r++]=x->s[j];
		}
	}
}