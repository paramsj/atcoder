#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;


int dfs(int u,int par,vector<int> &subtree,vector<int> &dist,
    vector<int> &a, vector<vector<int>> &g) {
    subtree[u] = a[u];
    for(auto v : g[u]) {
        if(v!=par) {
            dist[v] = dist[u] + 1;
            subtree[u] = subtree[u] + dfs(v,u,subtree,dist,a,g);
        }
    }
    return subtree[u];
}
void solve() {
    int n;
    cin>>n;
    int sum = 0;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        sum = sum + a[i];
    }
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++) {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> subtree(n+1,0);
    vector<int> dist(n+1,0);

    dfs(1,0,subtree,dist,a,g);

    vector<int> ans(n+1,0);

    for(int i=1;i<=n;i++) {
        // cout<<dist[i]<<" ";
        ans[1] = ans[1] + (a[i]*dist[i]);
    }
    queue<pair<int,int>> q;
    q.push({1,0});
    while(!q.empty()) {
        auto [u,par] = q.front();
        q.pop();
        for(auto v : g[u]) {
            if(v!=par) {
                ans[v] = ans[u] - subtree[v] + (sum - subtree[v]);
                q.push({v,u});
            }
        }
    }
    for(int i=1;i<=n;i++) {
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}
signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}