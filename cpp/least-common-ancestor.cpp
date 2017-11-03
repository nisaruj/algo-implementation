//LCA
//Shortest dist on tree
#include <stdio.h>
#include <vector>
#define MAXN 100000
#define LN 25
using namespace std;

int parent[LN][MAXN],depth[MAXN];
vector <int> adj[MAXN];

int dfs(int node,int from,int d) {
    parent[0][node] = from;
    depth[node] = d;
    for(int i=0;i<adj[node].size();i++) {
        if (adj[node][i] != from) dfs(adj[node][i],node,d+1);
    }
}

int build(int n) {
    for(int i=1;i<LN;i++) {
        for(int j=1;j<=n;j++) {
            if (parent[i-1][j] != -1)
                parent[i][j] = parent[i-1][parent[i-1][j]];
        }
    }
}

int lca(int a,int b) {
    if (depth[b] > depth[a]) return lca(b,a);

    //Binary rise until a nad b have same depth
    int diff = depth[a] - depth[b];
    for(int i=0;i<LN;i++) {
        if((1<<i)&diff) {
            a = parent[i][a];
        }
    }

    if (a == b) return a;

    for(int i=LN-1;i>=0;i--) {
        if (parent[i][a] != parent[i][b]) {
            a = parent[i][a];
            b = parent[i][b];
        }
    }
    return parent[0][a];
}

int query(int a,int b) {
    //Shortest dist between a and b
    return depth[a]+depth[b]-2*depth[lca(a,b)];
}

int main() {
    int from,to,n;
    scanf("%d",&n); //Tree size
    for(int i=0;i<n-1;i++) {
        scanf("%d%d",&from,&to);
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    //Initialize
    for(int i=0;i<LN;i++) {
        for(int j=0;j<MAXN;j++) parent[i][j] = -1;
    }
    dfs(1,-1,0);
    build(n);
    scanf("%d%d",&from,&to);
    printf("%d",query(from,to));
}
