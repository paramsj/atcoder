#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define int long long int
const int MOD = 1000000007;

template<typename T>
using ordered_set = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

int binpower(int a,int b,int MOD) {
    int res = 1;
    while(b) {
        if(b%2) {
            res = (res*a)%MOD;
        }
        a = (a*a)%MOD;
        b = b/2;
    }
    return res;
}
void solve() {
    cout<<1<<endl;
    int n = 3e5;
    cout<<n<<endl;
    for(int i=1;i<=n;i++) {
        if(i==n) {
            cout<<n;
        } else {
            cout<<n<<" ";
        }
    }
    cout<<endl;
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