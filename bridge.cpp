#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

int distinct = 0;
const int N = 4e5;
const int LOG = 22;

vector<vector<int>> g(N);
vector<int> a(N);

int euler[2*N];
int st[N];
int en[N];

int parent[N][LOG+1];
int depth[N];

int freq[N];
int visited[N];
int timer = 0;

struct MoQuery{
    int x,y,idx,lca;
    static const int block_size = 450;

    bool operator<(const MoQuery& rhs) const {
        if(x / block_size != rhs.x / block_size)
        return x / block_size < rhs.x / block_size;
        if(x / block_size & 1) return y < rhs.y;
        return y > rhs.y;
    }
};

void change(int idx) {
    int node = euler[idx];
    if(visited[node]) {
        freq[a[node]]--;

        if(freq[a[node]]==0) {
            distinct--;
        }
    } else {
        freq[a[node]]++;

        if(freq[a[node]]==1) {
            distinct++;
        }
    }
    visited[node] = !visited[node];
}

void dfs(int u,int par) {
    st[u] = timer;
    euler[timer++] = u;
    parent[u][0] = par;
    for(auto v : g[u]) {
        if(v!=par) {
            depth[v] = depth[u] + 1;
            dfs(v,u);
        }
    }

    en[u] = timer;
    euler[timer++] = u;
}

int merge(int u,int v) {
    if(depth[u] < depth[v]) {
        swap(u,v);
    }
    int diff = depth[u] - depth[v];

    for(int i=LOG;i>=0;i--) {
        if(diff&(1LL<<i)) {
            u = parent[u][i];
        }
    }
    if(u==v) {
        return u;
    }

    for(int i=LOG;i>=0;i--) {
        if(parent[u][i]!=parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}
void solve() {
    int n,m;
    cin>>n>>m;

    vector<int> d;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        d.push_back(a[i]);
    }
    sort(d.begin(),d.end());

    d.erase(unique(d.begin(),d.end()),d.end());

    for(int i=1;i<=n;i++) {
        a[i] = lower_bound(d.begin(),d.end(),a[i]) - d.begin();
    }

    for(int i=0;i<n-1;i++) {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(1,1);

    for(int j=1;j<=LOG;j++) {
        for(int i=1;i<=n;i++) {
            parent[i][j] = parent[parent[i][j-1]][j-1];
        }
    }
    vector<MoQuery> query;
    for(int i=0;i<m;i++) {
        int l,r;
        cin>>l>>r;

        if(st[l] > st[r]) {
            swap(l,r);
        }

        int lca = merge(l,r);

        if(lca==l) {
            query.push_back({st[l],st[r],i,-1});
        } else {
            query.push_back({en[l],st[r],i,lca});
        }
    }
    sort(query.begin(),query.end());

    int left = 0;
    int right = -1;

    vector<int> ans(m+1);

    for(auto qi : query) {
        // qi.x--;
        // qi.y--;

        while(left > qi.x) {
            left--;
            change(left);
        }

        while(left < qi.x) {
            change(left);
            left++;
        }

        while(right > qi.y) {
            change(right);
            right--;
        }

        while(right < qi.y) {
            right++;
            change(right);
        }

        if(qi.lca!=-1) {
            int val = a[qi.lca];
            if(visited[qi.lca]) {
                freq[val]--;
                if(freq[val]==0) {
                    distinct--;
                }
            } else {
                freq[val]++;
                if(freq[val]==1) {
                    distinct++;
                }
            }
            visited[qi.lca] = !visited[qi.lca];
        }

        ans[qi.idx] = distinct;

        if(qi.lca!=-1) {
            int val = a[qi.lca];
            if(visited[qi.lca]) {
                freq[val]--;
                if(freq[val]==0) {
                    distinct--;
                }
            } else {
                freq[val]++;
                if(freq[val]==1) {
                    distinct++;
                }
            }
            visited[qi.lca] = !visited[qi.lca];
        }
    }

    for(int i=0;i<m;i++) {
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
    // cin>>t;
    while(t--) {
        solve();
    }
    return 0;
}