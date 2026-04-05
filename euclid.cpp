#include<bits/stdc++.h>
using namespace std;
#define int long long int

void euclid(int a,int b) {
	int t1 = 0;
	int t2 = 1;
	int t = -1;
	int s1 = 1;
	int s2 = 0;
	int s = -1;
	cout<<"Q"<<setw(8)<<"A"<<setw(8)<<"B"<<setw(8)<<"R"<<setw(8)<<"T1"<<setw(8)<<"T2"<<setw(8)<<"T"<<setw(8)<<"S1"<<setw(8)<<"S2"<<setw(8)<<"S"<<endl;
	while(b) {
		int q = a/b;
		int rem = a%b;
		t = t1 - t2*q;
		s = s1 - s2*q;
		cout<<q<<setw(8)<<a<<setw(8)<<b<<setw(8)<<rem<<setw(8)<<t1<<setw(8)<<t2<<setw(8)<<t<<setw(8)<<s1<<setw(8)<<s2<<setw(8)<<s<<endl;

		a = b;
		b = rem;

		t1 = t2;
		t2 = t;

		s1 = s2;
		s2 = s;
	}
	cout<<" "<<setw(8)<<a<<setw(8)<<b<<setw(8)<<" "<<setw(8)<<t1<<setw(8)<<t2<<setw(8)<<t<<setw(8)<<s1<<setw(8)<<s2<<setw(8)<<s<<endl;
}

void solve() {
	int x,y;
	cin>>x>>y;
	euclid(x,y);
}

signed main() {
	solve();
	return 0;
}