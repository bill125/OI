struct SegTree {
    int h;
    int a[maxT], add[maxT];
    void init(int n) { for (h=1; (1<<h)<n+2; ++h) ; fill(a,0), fill(add,0); }
    void upd(int x) { a[x]=a[x<<1]+a[(x<<1)+1]; }
    void addIt(int x,int c) { add[x]+=c, a[x]+=c; }
    void relax(int x) {
        if (add[x]) {
            addIt(x<<1,add[x]>>1);
            addIt((x<<1)+1, add[x]>>1);
            add[x]=0;
        }
    }
    void pass(int x) { repD(i,h) relax(x>>(i+1)); }
    void ref(int x) { for (x>>=1; x; x>>=1) upd(x); }
    void Add(int x,int y,int c) {
        int l=x+(1<<h)-1, r=y+(1<<h)+1;
        pass(l), pass(r);
        while (l+1<r) {
            if (!(l&1)) addIt(l^1,c);
            if (r&1) addIt(r^1,c);
            l>>=1, r>>=1, c<<=1;
        }
        l=x+(1<<h)-1, r=y+(1<<h)+1;
        ref(l), ref(r);
    }
    int Sum(int x,int y) {
        int l=x+(1<<h)-1, r=y+(1<<h)+1, res=0;
        pass(l), pass(r);
        while (l+1<r) {
            if (!(l&1)) res+=a[l^1];
            if (r&1) res+=a[r^1];
            l>>=1, r>>=1;
        }
        return res;
    }
}T;
