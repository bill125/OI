class Priority_Queue {
	private :
		vector<int> q;
	
	public :
		void push(int x) {
			q.pb(x);push_heap(q.begin(),q.end());
		}
		int top() {return q[0];}
		bool empty() {return q.empty();}
		void pop() {
			pop_heap(q.begin(),q.end());q.pop_back();
		}
};
