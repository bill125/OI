#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <climits>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <tr1/unordered_map>

#define FOR(i,x) for (__typeof (x.begin ()) i = x.begin (); i != x.end (); ++i)

#define all(x) x.begin (), x.end ()
#define size(x) (int)x.size ()

#define PB push_back
#define MP make_pair

#define sqr(x) ((x) * (x))
#define abs(x) (((x) > 0) ? (x) : (-(x))) 
#define lowbit(x) ((x) & (-(x)))

using namespace std;
using namespace std::tr1;

typedef long long i64;
typedef unsigned long long u64;
typedef double dbl;

namespace Basic {
	template<class T>
	inline T Get () {
		char C; while (C = getchar (), ('0' > C || C > '9') && C != '-');
		
		if (C != '-') {
			T res = C - '0';
			while (C = getchar (), '0' <= C && C <= '9')
				res = res * 10 + C - '0';
			return res;
		} else {
			T res = 0;
			while (C = getchar (), '0' <= C && C <= '9')
				res = res * 10 + C - '0';
			return -res;
		}
	}
	
	inline u64 Random () {
		u64 res = rand (); res <<= 15; res |= rand ();
		return res;
	}
}

using namespace Basic;

int main () {
	#ifndef ONLINE_JUDGE
	freopen (".in", "r", stdin);
	freopen (".out", "w", stdout);
	#endif
	
	
	
	fclose (stdin);
	fclose (stdout);
	return 0;
}
