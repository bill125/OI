template<int N, typename T>
class HashTable {
	public :
		vector<T> A [N];
		
		inline void insert (int idx, const T& key) {
			if (exist (idx, key))
				return;
			
			A [idx].PB (key);
		}
		
		inline void erase (int idx, const T& key) {
			if (!exist (idx, key))
				return;
			
			FOR (i, A [idx])
				if ((*i) == key) {
					A [idx].erase (i);
					return;
				}
		}
		
		inline bool exist (int idx, const T& key) {
			for (int i = 0; i < size (A [idx]); ++i)
				if (A [idx][i] == key)
					return true;
			
			return false;
		}
		
		inline void clear () {
			for (int i = 0; i < N; ++i)
				A [i].clear ();
		}
};
