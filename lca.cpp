#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
#define int long long int

int rec(int i,int j,vector<vector<int>> &dp,vector<int> &a) {
    if(i==j) {
        return 0;
    }
    if(dp[i][j]!=-1) {
        return dp[i][j];
    }
    int ans = 1e18;
    for(int k=i;k<j;k++) {
        ans = min(ans,rec(i,k,dp,a) + rec(k+1,j,dp,a) + (a[i-1]*a[j]*a[k]));
    }
    return ans;
}
void solve() {
    int n;
    cin>>n;
    vector<int> a(n);#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
#define int long long int

void solve() {
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vector<int> pre(n+1,0);
    for(int i=0;i<n;i++) pre[i+1] = pre[i] + (abs(a[i])==2);
    vector<int> negPref(n+1,0);
    for(int i=0;i<n;i++) negPref[i+1] = negPref[i] + (a[i]<0);
    int best = -1;
    pair<int,int> ans = {n,0};
    int i = 0;
    while(i < n) {
        while(i < n && a[i] == 0) i++;
        if(i >= n) break;
        int L = i;
        int r = i;
        while(r < n && a[r] != 0) r++;
        int R = r; // segment [L, R)
        int lastPos[2] = {-1, -1};
        for(int k = L; k < R; k++) {
            int parity = negPref[k+1] % 2;
            lastPos[parity] = k;
        }
        for(int j = L; j < R; j++) {
            int startParity = negPref[j] % 2;
            int end = lastPos[startParity];
            if(end >= j) {
                int cnt = pre[end+1] - pre[j];
                if(cnt > best) {
                    best = cnt;
                    ans.first = j;
                    ans.second = n - (end + 1);
                }
            }
        }
        i = R;
    }
    if(best == -1) cout<<n<<" "<<0<<"\n";
    else cout<<ans.first<<" "<<ans.second<<"\n";
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
then why and hoe does this wrok

i am trying to do this only
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    vector<vector<int>> dp(n+1,vector<int> (n+1,-1));
    int ans = rec(1,n-1,dp,a);
    cout<<ans<<endl;
}
signed main() {
 #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}