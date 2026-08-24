#include<bits/stdc++.h>
using namespace std;
#define int long long int

void solve() {
	string s;
	cout<<"enter pt"<<endl;
	cin>>s;
	string key;
	cout<<"enter key"<<endl;
	cin>>key;
	string cleanKey;
	vector<int> seen(26,0);
	for(int i=0;i<key.length();i++) {
		char c = key[i];
		if(c=='j') {
			c = 'i';
		}
		if(!seen[c-'a']) {
			seen[c-'a'] = 1;
			cleanKey.push_back(c);
		}
	}
	for(char c='a';c<='z';c++) {
		if(c=='j') {
			continue;
		}
		if(!seen[c-'a']) {
			seen[c-'a'] = 1;
			cleanKey.push_back(c);
		}
	}
	vector<vector<char>> matrix(5,vector<char> (5));
	map<char,pair<int,int>> pos;
	int index = 0;
	for(int i=0;i<5;i++) {
		for(int j=0;j<5;j++) {
			matrix[i][j] = cleanKey[index];
			pos[cleanKey[index]] = {i,j};
			index++;
		}
	}
	string plain;
	for(int i=0;i<s.length();i++) {
		char c = s[i];
		if(c=='j') {
			c = 'i';
		}
		plain.push_back(c);
	}
	string ready;
	int point = 0;
	for(int i=0;i<plain.length();i++) {
		ready.push_back(plain[i]);
		if((i+1)<plain.length() && plain[i]==plain[i+1]) {
			ready.push_back('x');
		} else {
			i++; 
        	if(i < plain.length()) {
        		ready.push_back(plain[i]);
        	}
		}
	}
	if(ready.size()%2) {
		ready.push_back('x');
	}
	string cipher;
	for(int i=0;i<ready.length();i=i+2) {
		char a = ready[i];
		char b = ready[i+1];
		auto l = pos[a];
		auto r = pos[b];
		int r1 = l.first;
		int c1 = l.second;
		int r2 = r.first;
		int c2 = r.second;
		if(r1==r2) {
			cipher.push_back(matrix[r1][(c1+1)%5]);
			cipher.push_back(matrix[r2][(c2+1)%5]);
		} else if(c1==c2) {
			cipher.push_back(matrix[(r1+1)%5][c1]);
			cipher.push_back(matrix[(r2+1)%5][c2]);
		} else {
			cipher.push_back(matrix[r1][c2]);
			cipher.push_back(matrix[r2][c1]);
		}
	}
	cout<<cipher<<" "<<endl;
	string decrypt;
	for(int i=0;i<cipher.length();i=i+2) {
		char a = cipher[i];
		char b = cipher[i+1];
		auto l = pos[a];
		auto r = pos[b];
		int r1 = l.first;
		int c1 = l.second;
		int r2 = r.first;
		int c2 = r.second;
		if(r1==r2) {
			decrypt.push_back(matrix[r1][(c1+4)%5]);
			decrypt.push_back(matrix[r2][(c2+4)%5]);
		} else if(c1==c2) {
			decrypt.push_back(matrix[(r1+4)%5][c1]);
			decrypt.push_back(matrix[(r2+4)%5][c2]);
		} else {
			decrypt.push_back(matrix[r1][c2]);
			decrypt.push_back(matrix[r2][c1]);
		}
	}
	cout<<decrypt<<endl;
}

signed main() {
	solve();
	return 0;
}