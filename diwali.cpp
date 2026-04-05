#include <bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

struct trie{
	int val;
	trie* arr[2];
	trie() {
		arr[0] = NULL;
		arr[1] = NULL;
	}
};

void insert(trie* root,int value) {
	trie* temp = root;
	bool x;
	for(int i=32;i>=0;i--) {
		x = value&(1LL<<i);
		if(temp->arr[x]!=NULL) {
			temp = temp->arr[x];
		} else {
			temp->arr[x] = new trie();
			temp = temp->arr[x];
		}
	}
	temp->val = value;
}

int query(trie* root,int zor) {
	trie* temp = root;
	bool x;
	for(int i=32;i>=0;i--) {
		x = zor&(1LL<<i);
		if(temp->arr[!x]!=NULL) {
			temp = temp->arr[!x];
		} else if(temp->arr[x]!=NULL){
			temp = temp->arr[x];
		}
	}
	return zor^temp->val;
}
const int LOG = 22;
const int N = 200005;

int parent[N+1][LOG+1];
void dfs(int u,int par,vector<vector<int>> &g,vector<int> &depth) {
	parent[u][0] = par;
	for(auto v : g[u]) {
		if(v!=par) {
			depth[v] = depth[u] + 1;
			dfs(v,u,g,depth);
		}
	}
}

int merge(int a,int b,vector<int> &depth) {
	if(depth[a]<depth[b]) {
		swap(a,b);
	}
	int k = depth[a] - depth[b];
	for(int i=0;i<=LOG;i++) {
		if(k&(1LL<<i)) {
			a = parent[a][i];
		}
	}
	if(a==b) {
		return a;
	}
	for(int i=LOG;i>=0;i--) {
		if(parent[a][i]!=parent[b][i]) {
			a = parent[a][i];
			b = parent[b][i];
		}
	}
	return parent[a][0];
}
void solve() {
	int n,k;
	cin>>n>>k;
	vector<int> a(n);
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	map<int,int> b;
	int ans = 0;
	int j = 0;
	for(int i=0;i<n;i++) {
		b[a[i]]++;
		while(j<n && b.size()==(k+1)) {
			b[a[j]]--;
			if(b[a[j]]==0) {
				b.erase(a[j]);
			}
			j++;
		}
		ans = ans + (i-j+1);
	}
	cout<<ans<<endl;
}
signed main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
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