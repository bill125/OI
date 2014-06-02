struct State {
	State *go[C], *parent;
	int length;
	State () { fill(go, NULL), parent = NULL; }
	State* extend(State *, int token) ;
}memS[maxn << 1], *S = memS;

State* mk(int length) {
	S->length = length;
	return S ++;
}

State* State::extend(State* Start, int token) {
	State *p = this, *np = mk(p->length + 1);

	while (p && !p->go[token]) p->go[token] = np, p = p->parent;

	if (!p) np->parent = Start;
	else {
		State *q = p->go[token];
		if (q->length == p->length + 1) np->parent = q;
		else {
			State *nq = mk(q->length + 1);
			memcpy(nq->go, q->go, sizeof(q->go));
			nq->parent = q->parent;
			np->parent = q->parent = nq;
			while (p && p->go[token] == q) p->go[token] = nq, p = p->parent;
		}
	}
	return np;
}