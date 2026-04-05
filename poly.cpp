#include<bits/stdc++.h>
using namespace std;
#define int long long int

void solve() {
	string s;
	cin>>s;
	string key;
	cin>>key;
	int j = 0;
	while(key.length()!=s.length()) {
		key.push_back(s[j]);
		j++;
	}
	cout<<s<<" "<<key<<endl;
	string cipher;
	for(int i=0;i<s.length();i++) {
		cipher.push_back(char((s[i]-'a' + key[i]-'a')%26 + 'a'));
	}
	cout<<cipher<<endl;
	string decrypt;
	for(int i=0;i<cipher.length();i++) {
		decrypt.push_back(char((cipher[i]-'a' - (key[i]-'a') + 26)%26 + 'a'));
	}
	cout<<decrypt<<endl;
}
signed main() {
    solve();
    return 0;
}
