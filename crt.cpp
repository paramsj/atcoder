#include<bits/stdc++.h>
using namespace std;
#define int long long int


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
	vector<int> primes = {19,23,31};
	int n = 3;
	while(true) {
		cout<<"1. For Addition"<<endl;
		cout<<"2. For Subtraction"<<endl;
		cout<<"3. For Multiplication"<<endl;
		cout<<"4. For Division"<<endl;
		int choice;
		cin>>choice;
		vector<int> a,b;
		vector<int> c;
		int problem = 0;
		if(choice==1) {
			int x,y;
			cin>>x>>y;
			for(int i=0;i<3;i++) {
				a.push_back(x%primes[i]);
				b.push_back(y%primes[i]);
			}
			for(int i=0;i<n;i++) {
				c.push_back((a[i]+b[i])%primes[i]);
			}
		} else if(choice==2) {
			int x,y;
			cin>>x>>y;
			for(int i=0;i<3;i++) {
				a.push_back(x%primes[i]);
				b.push_back(y%primes[i]);
			}
			for(int i=0;i<n;i++) {
				c.push_back((a[i]-b[i]+primes[i])%primes[i]);
			}
		} else if(choice==3) {
			int x,y;
			cin>>x>>y;
			for(int i=0;i<3;i++) {
				a.push_back(x%primes[i]);
				b.push_back(y%primes[i]);
			}
			for(int i=0;i<n;i++) {
				c.push_back((a[i]*b[i])%primes[i]);
			}
		} else if(choice==4) {
			int x,y;
			cin>>x>>y;
			for(int i=0;i<3;i++) {
				a.push_back(x%primes[i]);
				b.push_back(y%primes[i]);
			}
			for(int i=0;i<n;i++) {
				int val = b[i];
				if(__gcd(b[i],primes[i])!=1) {
					cout<<"NOT POSSIBLE"<<endl;
					problem = 1;
					break;
				}
				val = binpower(b[i],primes[i]-2,primes[i]);
				c.push_back((a[i]*val)%primes[i]);
			}
		} else if(choice==5) {
			cout<<"Exiting"<<endl;
			break;
		} else {
			cout<<"Invalid Option Try Again"<<endl;
		}
		if(problem==1) {
			continue;
		}
		int M = 1;
		for(int i=0;i<n;i++) {
			M = M*primes[i];
		}
		int ans = 0;
		for(int i=0;i<n;i++) {
			int m = M/primes[i];
			ans = (ans + (c[i]*m*binpower(m%primes[i],primes[i]-2,primes[i]))%M)%M;
		}
		cout<<ans<<endl;
	}
}
signed main() {
	solve();
	return 0;
}