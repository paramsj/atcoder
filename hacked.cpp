#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
#define int long long int

int cs;
int ce;
 
bool dfs(int u,int par,vector<vector<int>> &g,vector<int> &visited,vector<int> &parent,vector<int> &colour) {
    visited[u] = 1;
    for(auto v : g[u]) {
        if(v!=par) {
            if(visited[v] && (colour[u]==colour[v])) {
                cs = v;
                ce = u;
                return true;
            } else if(!visited[v])  {
                colour[v] = !colour[u];
                parent[v] = u;
                if(dfs(v,u,g,visited,parent,colour)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void solve() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> g(n+1);
    map<pair<int,int>,int> b;

    for(int i=0;i<m;i++) {
        int x,y;
        cin>>x>>y;

        int u = min(x,y);
        int v = max(x,y);

        b[{u,v}]++;
    }
    cs = -1;
    ce = -1;

    int check = -1;
    for(auto i : b) {
        // cout<<i.first.first<<" "<<i.first.second<<" "<<i.second<<endl;
        int u = i.first.first;
        int v = i.first.second;
        int cnt = i.second;

        if(cnt%2==1) {
            check = u;
            g[u].push_back(v);
            g[v].push_back(u);
            // cout<<u<<" "<<v<<endl;
        }
    }
    if(check==-1) {
        cout<<-1<<endl;
        return;
    }
    vector<int> colour(n+1,0);
    vector<int> parent(n+1,0);
    vector<int> visited(n+1,0);

    for(int i=1;i<=n;i++) {
        if(!visited[i]) {
            colour[i] = 0;
            if(dfs(i,0,g,visited,parent,colour)) {
                break;
            }
        }
    }

    // cout<<cs<<" "<<ce<<endl;
    if(cs==-1 || ce==-1) {
        cout<<-1<<endl;
        return;
    }
    vector<int> cycle;
    cycle.push_back(cs);
    for(int v = ce; v!=cs ; v = parent[v]) {
        cycle.push_back(v);
    }
    int gg = cycle.size();
    if(gg%2==0) {
        cout<<-1<<endl;
        return;
    }
    cout<<cycle.size()<<endl;
    // cycle.push_back(cs);
    for(auto v : cycle) {
        cout<<v<<" ";
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