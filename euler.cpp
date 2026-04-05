#include <bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;
 
vector<int> time_in;
vector<int> time_out;
vector<int> BIT;
int timer = 1;
int n;

void update(int x, int delta) {
    for(; x <= n; x += x&-x)
        BIT[x] += delta;
}
int query(int x) {
    int sum = 0;
    for(; x > 0; x -= x&-x){
        sum += BIT[x];
    }
    return sum;
}
 
void dfs(int u,vector<vector<int>> &g,vector<int> &visited) {
    time_in[u] = timer++;
    visited[u] = 1;
    for(auto v : g[u]) {
        if(!visited[v]) {
            dfs(v,g,visited);
        }
    }
    time_out[u] = timer-1;
}
void solve() {
    int q;
    cin>>n>>q;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    vector<vector<int>> g(n+1);
    for(int i=0;i<n-1;i++) {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    BIT.resize(n+1,0);
    time_in.resize(n+1,0);
    time_out.resize(n+1,0);
    vector<int> visited(n+1,0);
    dfs(1,g,visited);
    vector<int> val(n+1);
    for(int i=1;i<=n;i++) {
        //val[time_in[i]] = a[i];
        update(time_in[i],a[i]);
        update(time_out[i]+1,-a[i]);
    }
    while(q--) {
        int type;
        cin>>type;
        if(type==1) {
            int node,x;
            cin>>node>>x;
            update(time_in[node],-a[node]);
            update(time_out[node]+1,a[node]);
            a[node] = x;
            update(time_in[node],a[node]);
            update(time_out[node]+1,-a[node]);

        } else if(type==2) {
            int node;
            cin>>node;
            cout<<query(time_in[node])<<endl;
        }
    }
}
signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
 