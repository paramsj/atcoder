#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#define int long long int
using namespace std;

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
	int p = 23;
	int g = 5;
	int a = 4; // let other one take 3
	int public_key = binpower(g,a,p);
	int sock = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4000);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock,(sockaddr*)&addr,sizeof(addr));
	listen(sock,5);
	int client = accept(sock,nullptr,nullptr);

	string msg = to_string(p) + "," + to_string(g) + "," + to_string(public_key);
	send(client,msg.c_str(),msg.size(),0);

	char buffer[1024] = {0};
	recv(client,buffer,sizeof(buffer),0);
	int B = atoll(buffer);	

	cout << "[Server] Client public key B = " << B << endl;
	long long shared_secret = binpower(B, a, p);
    cout << "[Server] Shared Secret = " << shared_secret << endl;
	return 0;
}