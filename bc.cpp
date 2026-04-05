#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;
    if(n==1) {
        if(s=="a") {
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;   
        }
        return;
    }
    if(n%2==0) {
        int prob = 0;
        int a = 0;
        int b = 0;
        int limit = (n/2) - 1;
        for(int i=0;i<n;i++) {
            if(s[i]=='a') {
                a++;
            } else if(s[i]=='b') {
                b++;
            } else {
                prob++;
            }
            if(i<n-2) {
                if(a>limit || b>limit) {
                    cout<<"NO"<<endl;
                    return;
                }
            }
            if(a>((i+1)/2) || b>(i+1)/2) {
                cout<<"NO"<<endl;
                return;
            }
        }

        if(a>n/2 || b>n/2) {
            cout<<"NO"<<endl;
            return;
        }

        if(s[n-1]==s[n-2] && s[n-2]=='a') {
            cout<<"NO"<<endl;
            return;
        }
        if(s[n-1]==s[n-2] && s[n-2]=='b') {
            cout<<"NO"<<endl;
            return;
        }

        if(s[0]=='a' && s[1]=='a') {
            // cout<<"hree"<<endl;
            cout<<"NO"<<endl;
            return;
        }
        if(s[0]=='b' && s[1]=='b') {
            cout<<"NO"<<endl;
            return;
        }
        for(int i=0;i<n;i++) {
            if(i+1<n && i+2<n) {
                if(s[i]==s[i+1]==s[i+2]=='a') {
                    cout<<"NO"<<endl;
                    return;
                }
                if(s[i]==s[i+1]==s[i+2]=='b') {
                    cout<<"NO"<<endl;
                    return;
                }
            } 
        }


    } else {
        int prob = 0;
        int a = 0;
        int b = 0;
        int limit = (n+1)/2;
        for(int i=0;i<n;i++) {
            if(s[i]=='a') {
                a++;
            } else if(s[i]=='b') {
                b++;
            } else {
                prob++;
            }

            if(a>(i+1)) {
                cout<<"NO"<<endl;
                return;
            }

            if(i<n-2) {
                if(a>=limit || b>=(limit-1)) {
                    cout<<"NO"<<endl;
                    return;
                }
            }

        }

    
        if(a>(n+1)/2 || b>n/2) {
            cout<<"NO"<<endl;
            return;
        }
        

        if(s[0]=='b') {
            cout<<"NO"<<endl;
            return;
        }
        if(s[n-1]==s[n-2] && s[n-2]=='a') {
            cout<<"NO"<<endl;
            return;
        }
        if(s[n-1]==s[n-2] && s[n-2]=='b') {
            cout<<"NO"<<endl;
            return;
        }


        for(int i=0;i<n;i++) {
            if(i+1<n && i+2<n) {
                if(s[i]==s[i+1]==s[i+2]=='a') {
                    cout<<"NO"<<endl;
                    return;
                }
                if(s[i]==s[i+1]==s[i+2]=='b') {
                    cout<<"NO"<<endl;
                    return;
                }
            }
        }
    }


    cout<<"YES"<<endl;
}
signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}