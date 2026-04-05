#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 998244353;

void solve() {
    int n;
    cin>>n;
    vector<int> a(n);
    priority_queue<int> pq;
    int res = 0;
    for(int i=0;i<n;i++) {
        cin>>a[i];
        res = res^a[i];
        pq.push(a[i]);
    }
    sort(a.begin(),a.end());
    cout<<res<<" ";
    cout<<a[0]<<" ";
    int ans = 0;
    while(!pq.empty()) {
        int temp = pq.top();
        pq.pop();
        ans = temp;
        int sz = pq.size();

        vector<int> t;
        while(!pq.empty()) {
            int val = pq.top();
            pq.pop();
            t.push_back(val^temp);
        }

        for(auto v : t) {
            pq.push(v);
        }
    }
    cout<<ans<<endl;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    cin>>t;
    while(t--) {
        solve();
    }
    return 0;
}