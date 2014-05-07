/*
  Task: BZOJ_1065
  Created: 2012.06.20
  Author: Zhu Jiahao
*/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>

const int maxN = 80;
double f[maxN][maxN][maxN],g[maxN][maxN][maxN];
double C[maxN],F[maxN],K[maxN],ans;
int pre[maxN],n,m;

void Dp(int u, int d)
{
    for (int v = 2; v < n + 1; ++v) if (pre[v] == u) Dp(v, d + 1);
    for (int _d = std::min(2, d); _d < d + 1; ++_d) 
        for (int j = 0; j < m + 1; ++j) F[j] = 0;
        for (int v = 2; v < n + 1; ++v) 
          if (pre[v] == u)
            for (int j = m; j > -1; --j)
              for (int k = j; k > -1; --k) F[j] = std::max(F[j], F[k] + g[v][j - k][_d]);
        for (int j = 0; j < m + 1; ++j) [u][j][_d] = F[j] + C[u] * K[_d];
    }
    if (d > 1) {
        for (int j = 0; j < m + 1; ++j) F[j] = 0;
        for (int v = 2; v < n + 1; ++v) if (pre[v] == u)
        for (int j = m; j > -1; --j)
        for (int k = j; k > -1; --k) F[j] = std::max(F[j], F[k] + g[v][j - k][1]);
        for (int j = 1; j < m + 1; ++j) f[u][j][1] = F[j - 1] + C[u] * K[1];
    }
    for (int j = 0; j < m + 1; ++j)
    for (int _d = 0; _d < d; ++_d)g[u][j][_d] = std::max(f[u][j][_d + 1], f[u][j][1]);
    return;
}

int main()
{    
    scanf("%d%d%lf", &n, &m, K + 1);
    
    for (int i = 2; i < n + 1; ++i) K[i] = K[i - 1] * K[1];
    for (int i = 1; i < n + 1; ++i) scanf("%d", pre + i);
    for (int i = 1; i < n + 1; ++i) scanf("%lf", C + i);
    for (int ths = pre[1], len = 2; ths - 1; ths = pre[ths], ++len) {
        for (int i = 1; i < n + 1; ++i)
        for (int j = 0; j < m + 1; ++j)
        for (int k = 0; k < n + 1; ++k) f[i][j][k] = g[i][j][k] = 0;
        int tmp = pre[ths]; double Now = 0;
        pre[ths] = 1;
        for (int v = 2; v < n + 1; ++v) if (pre[v] == 1) Dp(v, 1);
        for (int j = 0; j < m + 1; ++j) F[j] = 0;
        for (int v = 2; v < n + 1; ++v) if (pre[v] == 1)
        for (int j = m; j > -1; --j)
        for (int k = j; k > -1; --k) F[j] = std::max(F[j], F[k] + f[v][j - k][1]);
        for (int j = 0; j < m; ++j) Now = std::max(Now, F[j]);
        if (tmp == 1) Now = std::max(Now, F[m]);
        ans = std::max(ans, (Now + C[1]) / (1 - K[len]));
        pre[ths] = tmp;
    }
    printf("%.2lf\n", ans);
    return 0;
}
