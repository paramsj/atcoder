#include<bits/stdc++.h>
using namespace std;
#define int long long int

const int N = 1e5 + 5;
const int LOG = 20;

int parent[N][LOG+1];
vector<int> query[N][LOG+1];


void dfs(int u,int par,vector<vector<int>> &g,vector<int> &a,vector<int> &depth) {
    parent[u][0] = par;
    // query[u][0] = a[u];
    for(auto v : g[u]) {
        if(v!=par) {
            depth[v] = depth[u] + 1;
            dfs(v,u,g,a,depth);
        }
    }
}

vector<int> combine(vector<int> &l,vector<int> &r) {
    vector<int> ans;
    int i = 0;
    int j = 0;
    while(ans.size()<10 && (i<l.size() || j<r.size())) {
        int put = 0;

        ifl([i] < r[j]) {
            put = l[i];
            i++;
        } else {
            put = r[j];
            j++;
        }

        if(ans.empty() || (ans.back()!=put)) {
            ans.push_back(put);
        }
    }
    return ans;
}


vector<int> merge(int u,int v,int a,vector<int> &depth) {
    if(depth[u] < depth[v]) {
        swap(u,v);
    }
    int k = depth[u] - depth[v];
    vector<int> ans;
    for(int i=0;i<LOG;i++) {
        if(k&(1LL<<i)) {
            ans = combine(ans,query[u][i]);
            u = parent[u][i];
        }
    }
    if(u==v) {
        return combine(ans,query[u][0]);
    }
    for(int i=LOG;i>=0;i--) {
        if(parent[u][i]!=parent[v][i]) {
            ans = combine(ans,query[u][i]);
            ans = combine(ans,query[v][i]);
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    ans = combine(ans, query[u][0]);
    ans = combine(ans, query[v][0]);
    ans = combine(ans, query[parent[u][0]][0]);
    return ans;
}
void solve() {
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++) {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    vector<int> c(m+1,1e18);
    for(int i=1;i<=m;i++) {
        int x;
        cin>>x;
        query[i][0].push_back(x);
    }
    for(int i=1;i<=n;i++) {
        if(!query[i][0].empty()) {
            sort(query[i][0].begin(),query[i][0].end());
        }
    }
    vector<int> depth(n+1,0);
    dfs(1,0,g,c,depth);
    for(int i=1;i<=LOG;i++) {
        for(int j=1;j<=n;j++) {
            parent[j][i] = parent[parent[j][i-1]][i-1];
            query[j][i] = combine(query[j][i-1],query[parent[j][i-1]][i-1]);
        }
    }

    while(q--) {
        int u,v,a;
        cin>>u>>v>>a;
        vector<int> ans = merge(u,v,a,depth);

        int res = ans.size();
        cout<<min(a,res)<<" ";
        for(int i=0;i<min(a,res);i++) {
            cout<<ans[i]<<" ";
        }
        cout<<endl;
    }
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}