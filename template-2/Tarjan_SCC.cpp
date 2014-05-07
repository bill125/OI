namespace Tarjan {
    int n,Index,Top,Color;
    int DFN[maxn],Low[maxn],Tag[maxn];
    bool InStack[maxn];
    vector<int> Stack;
    void init(const int & _n) {
        n = _n;
        Index = Top = Color = 0;
        fill(DFN,-1),fill(Low,-1),fill(InStack,1);
    }
    void DFS(int x) {
        Stack.pb(x);
        DFN[x] = Low[x] = Index ++;
        ForV(i,e[x]) {
            if (DFN[e[x][i]] < 0) {
                DFS(e[x][i]);
                Low[x] = min(Low[x],Low[e[x][i]]);
            }
            else
                if (InStack[e[x][i]])
                    Low[x] = min(Low[x],DFN[e[x][i]]);
        }
        if (DFN[x] == Low[x]) {
            int now;
            do {
                now = Stack.back();
                Tag[now] = Color,InStack[now] = 0;
                Stack.pop_back();
            } while (now != x);
            ++Color;
        }
    }
    int Run(vector<int> &C) {
        rep(i,n) if (DFN[i] < 0) DFS(i);
        rep(i,n) C.pb(Tag[i]);
        return Color;
    }
}