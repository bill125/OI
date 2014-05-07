template <class T>
struct Heap {
	int sz;
	vector<T> A;
	Heap(): sz(0) {} 
	void clear() {
		A.clear();
	}
	T top() {
		return A.begin();
	}
	void up(int x) {
		while (x) {
			if (A[x>>1]<A[x]) return ;
			swap(A[x],A[x>>=1]); 
		}
	}
	void down(int x) {
		while (x < sz) {
			int y = (1+(x<<1) < sz && A[(x<<1)+1] > A[(x<<1)]) ? (x<<1)+1 : (x<<1);
			if (A[y]<A[x]) return ; 
			swap(A[x],A[x=y]);
		}
	}
	void push(const T &t) {
		A.pb(t);
		up(sz++);
	}
	void pop() {
		swap(A[0],A[sz--]);
		down(0);
		A.pop_back;
	}
};
