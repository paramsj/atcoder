#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;
#define int long long int

int binpower(int a,int b,int MOD) {
    int res = 1;
    while(b) {
        if(b%2) {
            res = (res*a)%MOD;
        }
        b = b/2;
        a = (a*a)%MOD;
    }
    return res;
}

signed main() {
	int b = 3;
	int sock = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4000);
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	connect(sock,(sockaddr*)&addr,sizeof(addr));

	char buffer[1024] = {0};
	int p,g,A;
	recv(sock,buffer,sizeof(buffer),0);
	sscanf(buffer,"%lld,%lld,%lld",&p,&g,&A);
	cout << "[Client] Received: p=" << p << ", g=" << g << ", A=" << A << endl;

	int B = binpower(g,b,p);
	string msg = to_string(B);
	send(sock,msg.c_str(),msg.size(),0);

	long long shared_secret = binpower(A, b, p);
    cout << "[Server] Shared Secret = " << shared_secret << endl;
	return 0;
}


bool check(vector<int> &a,vector<int> &b,int n,int m,int mid,vector<int> &c,priority_queue<pair<int,int>> pq) {
    int number = n - mid;
    vector<int> given(n+1,0);
    for(int i=n-1;i>=(n-mid);i--) {
        int people = (c[i])*(mid);
        while(!pq.empty() && people>0) {
            auto [qty,type] = pq.top();
            pq.pop();
            if(people>=qty) {
                people = people - qty;
            } else {
                int diff = qty - people;
                people = 0;
                pq.push({diff,type});
            }
        }
        mid--;
        if(people==0) {
            continue;
        }
        if(people>0) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n,m;
    cin>>n>>m;
    vector<int> a(n);
    vector<int> b(m);
    map<int,int> cnt;
    map<int,int> type;
    int largest = 0;
    for(int i=0;i<n;i++) {
        cin>>a[i];
        largest = max(a[i],largest);
        cnt[a[i]]++;
    }
    set<int> s(a.begin(),a.end());
    map<int,int> compress;
    int val = 0;
    for(auto i : s) {
        compress[i] = val++;
    }
    vector<int> temp(n);
    for(int i=0;i<n;i++) {
        temp[i] = compress[a[i]];
    }
    for(int i=0;i<m;i++) {
        cin>>b[i];
        type[i] = type[i] + b[i];
    }
    int ans = -1;
    int l = 0;
    int r = val;
    //cout<<val<<" ";
    priority_queue<pair<int,int>> pq;
    for(auto i : type) {
        pq.push({i.second,i.first});
    }
    vector<int> people(val,0);
    for(int i : temp) {
        people[i]++;
    }
    vector<int> pre(val+1, 0);
    for (int i=val-1;i>= 0;i--) {
        pre[i] = pre[i+1] + people[i];
    }
    while(l<=r) {
        int mid = (l+r)/2;
        if(check(a,b,val,m,mid,people,pq)) {
            ans = pre[val-mid];
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("Case #%lld: %lld\n",test,max(0LL,ans));
}
