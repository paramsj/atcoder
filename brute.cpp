#include <bits/stdc++.h>
using namespace std;
#define int long long int

struct Stack {
    stack<pair<int,int>> s;

    void push(int x) {
        int mini = x;
        if(!s.empty()) {
            mini = min(mini,s.top().second);
        }
        s.push({x,mini});
    }
    void pop() {
        s.pop();
    }
    int gg() {
        return s.top().second;
    }
};

struct Q {
    Stack in,out;

    void push(int x) {
        in.push(x);
    }

    void pop() {
        if(out.s.empty()) {
            while(!in.s.empty()) {
                int v = in.s.top().first;
                in.pop();
                out.push(v);
            }
        }
        out.pop();
    }

    int query() {
        if(in.s.empty()) {
            return out.gg();
        }
        if(out.s.empty()) {
            return in.gg();
        }
        return min(in.gg(),out.gg());
    }
};
void solve() {
    int n,k;
    cin>>n>>k;
    vector<int> arr(n);
    int x,a,b,c;
    cin>>x>>a>>b>>c;
    arr[0] = x;
    for(int i=1;i<n;i++) {
        arr[i] = (a*arr[i-1] + b)%c;
    }
    Q mq;
    int ans = 0;
    for(int i=0;i<k;i++) {
        mq.push(arr[i]);
    }
    ans = ans^(mq.query());
    for(int i=k;i<n;i++) {
        mq.push(arr[i]);
        mq.pop();
        ans = ans^(mq.query());
    }
    cout<<ans<<endl;
}
signed main() {
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
