#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

struct Node {
	int sum;
	int lazy_add;
	Node(int sum,int lazy_add) : sum(sum),lazy_add(lazy_add)  {}
	Node() : sum(0),lazy_add(0) {}
};


Node merge(Node a,Node b) {
	return Node(a.sum + b.sum,0);
}

vector<Node> tree;

void apply_add(int idx,int l,int r,int val) {
	tree[idx].sum += (r-l+1)*val;
	tree[idx].lazy_add += val;
}
void push(int idx,int l,int r) {
	if(l==r) {
		return;
	}
	int mid = (l+r)/2;
	if(tree[idx].lazy_add!=0) {
		apply_add(2*idx,l,mid,tree[idx].lazy_add);
		apply_add((2*idx) + 1,mid + 1,r,tree[idx].lazy_add);
		tree[idx].lazy_add = 0;
	}
}
 
void build(int idx,int l,int r,vector<int> &a) {
	if(l==r) {
		tree[idx] = {a[l],0};
		return;
	}
	int mid = (l+r)/2;
	build(2*idx,l,mid,a);
	build(2*idx + 1,mid + 1,r,a);
	tree[idx] = merge(tree[2*idx],tree[(2*idx)+ 1]);
}

Node query(int idx,int tl,int th,int ql,int qh) {
	if(ql<=tl && th<=qh) {
		return tree[idx];
	}
	if(ql>th || qh<tl) {
		return Node();
	}
	int mid = (tl+th)/2;
	push(idx,tl,th);
	return merge(query(2*idx,tl,mid,ql,qh),query(2*idx + 1,mid+1,th,ql,qh));
}
 
void update(int idx,int tl,int th,int ql,int qh,int val) {
	if(ql>th || qh<tl) {
		return;
	}
 
	if(ql<=tl && th<=qh) {
		apply_add(idx,tl,th,val);
		return;
	}
	int mid = (tl+th)/2;
	push(idx,tl,th);
	update(2*idx,tl,mid,ql,qh,val);
	update(2*idx + 1,mid + 1,th,ql,qh,val);
	tree[idx] = merge(tree[2*idx],tree[2*idx + 1]);
}


void solve() {
	int g,m,d,k,v;
	cin>>g>>m>>d>>k>>v;


	int train_dist = m - g;

	
}

signed main() {
ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
cin.exceptions(cin.failbit);
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



#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

void solve() {
    int n,k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0;i<n;i++) {
        cin>>a[i];
    }
    deque<int> mini;
    deque<int> maxi;
    int ans = 0;
    int j = 0;
    for(int i=0;i<n;i++) {
        while(!mini.empty() && a[mini.back()]>a[i]) {
            mini.pop_back();
        }
        while(!maxi.empty() && a[maxi.back()]<a[i]) {
            maxi.pop_back();
        }
        mini.push_back(i);
        maxi.push_back(i);

        while(!mini.empty() && !maxi.empty() && a[maxi.front()]-a[mini.front()]>k) {
            if(!mini.empty() && mini.front()==j) {
                mini.pop_front();
            }
            if(!maxi.empty() && maxi.front()==j) {
                maxi.pop_front();
            }
            j++;
        }
        ans = ans + i - j + 1;
    }
    cout<<ans<<endl;
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