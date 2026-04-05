#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

void solve() {
	int n,v;
	cin>>n>>v;

	vector<int> d(n+1);
	vector<int> a(n+1);
	for(int i=1;i<n;i++) {
		cin>>d[i];
	}

	for(int i=2;i<=n;i++) {
		cin>>a[i];
	}

	vector<int> ans;
	int dist = 0;
	for(int i=2;i<=n;i++) {
		dist = dist + d[i-1];
		int t = a[i] * v;
		if((dist/v) < a[i]) {
			ans.push_back(i);
		}
	}

	if(!ans.empty()) {
		// cout<<ans.size()<<endl;
		for(auto v : ans) {
			cout<<v<<" "; 
		}
	} else {
		cout<<-1<<endl;
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