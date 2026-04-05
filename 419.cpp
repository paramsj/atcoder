#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

void solve() {
    long long n,m;
    scanf("%lld",&n);
    scanf("%lld",&m);
    vector<vector<pair<long long,long long>>> g(n+1);
    vector<long long> b(n+1);
    long long edge = 0;
    for(long long i=1;i<=n;i++) {
        scanf("%lld",&b[i]);
    }
    for(long long i=0;i<m;i++) {
        long long x,y,w;
        scanf("%lld %lld %lld",&x,&y,&w);
        g[x].push_back({y,w});
        edge = max(edge,w);
    }
    long long l = 1;
    long long r = edge+5;
    long long ans = -1;
    while(l<=r) {
        long long mid = (l+r)/2;
        priority_queue<pair<long long,long long>> q;
        q.push({min(mid,b[1]),1});
        vector<long long> dist(n+1,-1e18);
        dist[1] = min(b[1],mid);
        //cout<<dist[1]<<" ";
        long long done = 0;
        while(!q.empty()) {
            auto [battery,node] = q.top();
            q.pop();
            if(done==1) {
                break;
            }
            if(node==n) {
                done = 1;
                break;
            }
            long long temp = battery;
            // if(temp<mid) {
            //     temp = min(mid,temp+b[node]);
            // }
            if(dist[node]>temp) {
                continue;
            }
            for(auto [v,w] : g[node]) {
                if(w<=temp) {
                    if(v==n) {
                        done = 1;
                        break;
                    }
                    long long change = min(mid,temp+b[v]);
                    if(change>dist[v]) {
                        dist[v] = change;
                        q.push({change,v});
                    }
                }
            }
        }
        if(done>=1) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%lld\n",ans);
}
signed main() {
cin.exceptions(cin.failbit);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}