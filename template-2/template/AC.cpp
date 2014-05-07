struct Trie {
	Trie *s[maxc],*Fail;
	int End;bool v;
	Trie () {
		fill(s,0);Fail = 0;
		v = 0,End = 0;
	}
}*root;

namespace AC {
	void AddEntry(char c[]) {
		int l = strlen(c);
		Trie *x = root;
		rep(i,l) {
			int t = c[i] - 'a';
			if (!x->s[t]) x->s[t] = new Trie;
			x = x->s[t];
		}
		++x->End;
	}
	void AddFail() {
		Trie* q[maxn];root->Fail = root;
		int l = -1,r = 0;q[0] = root;
		while (l < r) {
			Trie *x = q[++l];
			rep(i,maxc) if (x->s[i]) {
				Trie *t = x->Fail;
				for (;t != root && !t->s[i];t = t->Fail) ;
				x->s[i]->Fail = (t->s[i] && x != root) ? t->s[i] : root;
				q[++r] = x->s[i];
			}
		}
	}
}