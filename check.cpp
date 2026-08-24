#include<bits/stdc++.h>
using namespace std;
#define int long long int

bool check(int mid,int n,int m,vector<int> &a,vector<int> &b,int k) {
    int rank = 0;
    int j = 1;
    // cout<<mid<<" "<<endl;
    for(int i=n;i>=1;i--) {
        while(j<=m && (a[i]*b[j])<mid) {
            j++;
        }
        if(j==(m+1)) {
            break;
        }
        if((a[i]*b[j])>=mid) {
            rank = rank + (m - j + 1);
            // cout<<i<<" "<<j<<" "<<mid<<endl;
        }
    }
    // cout<<endl;
    if(rank>=k) {
        return true;
    }
    return false;
}
void solve() {
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> a(n+1,0);
    vector<int> b(m+1,0);
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    for(int i=1;i<=m;i++) {
        cin>>b[i];
    }
    vector<int> temp;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            temp.push_back(a[i]*b[j]);
        }
    }
    sort(temp.rbegin(),temp.rend());
    for(auto v : temp) {
        // cout<<v<<" ";
    }
    // cout<<endl;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int l = 1;
    int r = 1e18;
    int ans = 0;
    while(l<=r) {
        // ill try to find the kth multiplciation first
        int mid = (l+r)/2;
        if(check(mid,n,m,a,b,k)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    int sum = 0;
    int j = 1;
    vector<int> pre(m+5,0);
    for(int i=1;i<=m;i++) {
        pre[i] = pre[i-1] + b[i];
    }
    int rem = k;
    for(int i=n;i>=1;i--) {
        while(j<=m && a[i]*b[j]<=ans) {
            j++;
        }
        sum = sum + a[i]*(pre[m]-pre[j-1]);
        rem = rem - (m-j+1);
    }
    sum = sum + rem*ans;
    // cout<<rem<<" ";
    // cout<<ans<<endl;
    cout<<sum<<endl;
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