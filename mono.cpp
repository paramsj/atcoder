#include<bits/stdc++.h>
using namespace std;
#define int long long int

void solve() {
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	random_shuffle(alphabet.begin(),alphabet.end());
	string s;
	cin>>s;
	map<char,char> mapping;
	map<char,char> rev;
	for(int i=0;i<26;i++) {
		mapping[i+'a'] = alphabet[i];
		rev[alphabet[i]] = char(i+'a');
	}
	cout<<s<<endl;
	string cipher;
	int n = s.length();
	for(int i=0;i<n;i++) {
		cipher.push_back(mapping[s[i]]);
	}
	for(auto i : mapping) {
		cout<<i.first<<" "<<i.second<<endl;
	}
	cout<<endl;
	cout<<cipher<<endl;
	for(int i=0;i<n;i++) {
		cout<<rev[cipher[i]];
	}
}

signed main() {
	solve();
	return 0;
}