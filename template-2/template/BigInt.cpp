struct BigInt {
	int a[maxl];
	int l;
	BigInt () {}
	BigInt (ll p) {
		fill(a,0);
		for (l=0;p>0;p/=X) a[l++]=p%X;
	}
	BigInt (char c[]) {
		fill(a,0);
		l=0;
		ll k=1;
		repD(i,strlen(c)) { 
			a[l]+=k*(c[i]-'0');
			if ((k*=10)==X) 
				k=1, ++l;
		}
		if (a[l]>0) ++l;
	}
	bool operator< (const BigInt&A) {
		if (l<A.l) return true;
		if (l>A.l) return false;
		repD(i,l) {
			if (a[i]<A.a[i]) return true;
			if (a[i]>A.a[i]) return false;
		}
		return false;
	}
	bool operator== (const BigInt&A) {
		if (l!=A.l) return false;
		rep(i,l) if (a[i]!=A.a[i]) return false;
		return true;
	}
	BigInt operator+ (const BigInt&A) {
		BigInt t(0LL);
		t.l=max(l,A.l);
		ll k=0;
		rep(i,t.l) {
			k+=a[i]+A.a[i];
			t.a[i]=k%X;
			k/=X;
		}
		while (k) t.a[t.l++]=k%X,k/=X;
		return t;
	}
	BigInt operator*(const BigInt&A) {
		BigInt t(0LL);
		rep(i,l) {
			ll k=0;
			t.l=i;
			rep(j,A.l) {
				k+=a[i]*A.a[j]+t.a[t.l];
				t.a[t.l++]=k%X;
				k/=X;
			}
			while (k>0) {
				k+=t.a[t.l];
				t.a[t.l++]=k%X;
				k/=X;
			}
		}
		return t;
	}
	BigInt operator/(const ll&A) {
		BigInt t(0LL);
		ll k=0;
		repD(i,l) {
			k=k*X+a[i];
			t.a[i]=k/A;
			k%=A;
		}
		t.l=0;
		repD(i,l) if (t.a[i]!=0) {
			t.l=i+1;
			break;
		}
		return t;
	}
	void print() {
		if (l==0) {printf("0");return;}
		printf("%d", a[l-1]);
		repD(i,l-1) {
			for (int t=a[i]|1;t*10<X;t*=10) printf("0");
			printf("%d", a[i]);
		}
	}
};
