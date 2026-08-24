#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> 
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

int main() {
	int sock = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3000);
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	//inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	connect(sock,(sockaddr*)&addr,sizeof(addr));
	char buffer[1024] = {0};
	recv(sock,buffer,sizeof(buffer),0);
	int e,n;
	sscanf(buffer,"%lld,%lld",&e,&n);
    cout << "[Client] Server public key received: (" << e << ", " << n << ")\n";
    int msg = 9;
    int cipher = binpower(msg,e,n);
    string message = to_string(cipher);
    send(sock,message.c_str(),message.size(),0);
    close(sock);
	return 0;
}