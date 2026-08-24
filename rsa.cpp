#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

int modInverse(int a,int b) {
    int modulo = a;
    int t1 = 0;
    int t2 = 1;
    int t = -1;
    while(b) {
        int q = a/b;
        int rem = a%b;
        t = t1 - (t2*q);

        a = b;
        b = rem;

        t1 = t2;
        t2 = t;
    }
    return (t1+modulo)%modulo;
}

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
int main() {
    int p = 13;
    int q = 19;
    int phi_n = (p-1)*(q-1);
    int n = p*q;
    int e = 0;
    for(int i=2;i<phi_n;i++) {
        if(__gcd(i,phi_n)==1) {
            e = i;
            break;
        }
    }
    // n and e is public
    // n and d is private

    int d = modInverse(phi_n,e);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3000);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock,(sockaddr*)&addr,sizeof(addr));
    listen(sock,5);
    cout << "Server running on 3000...\n";
    int client = accept(sock,nullptr,nullptr);
    string msg = to_string(e) + "," + to_string(n);
    send(client,msg.c_str(),msg.size(),0);
    char buffer[1024] = {0};
    recv(client,buffer,sizeof(buffer),0);
    int cipher = atoll(buffer);
    cout<<cipher<<endl;
    int decrypt = binpower(cipher,d,n);
    cout<<decrypt<<endl;
    return 0;
} 