#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

map<string,string> db;

int generatePrime(int n) {
    for(int i=n;i>=2;i--) {
        if(isPrime(i)) {
            return i;
        }
    }
    return 2;
}

int modInverse(int a,int b) {
    int mod = a;
    int t1 = 0;
    int t2 = 1;
    int t = -1;
    while(b) {
        int q = a/b;
        int rem = a%b;
        a = b;
        b = rem;
        t = t1 - (t2*q);

        t1 = t2;
        t2 = rem;
    }
    return (t1 + mod)%mod;
}

int modInverse(int a,int b) {
    int og = a;
    int t1 = 0;
    int t2 = 1;
    int t = -1;
    while(b!=0) {
        int q = a/b;
        int rem = a%b;
        t = t1 - (t2*q);
        t1 = t2;
        t2  = t;
        a = b;
        b = rem;
    }
    return (t1+og)%og;
}

void generateKeys() {
    int p = generatePrime(100);
    int q = generatePrime(150);
    while(p==q) {
        q = generatePrime(p-1);
    }
    int n = p*q;
    int phi_n = (p-1)*(q-1);
    int e = 0;
    for(int i=2;i<=phi_n;i++) {
        if(__gcd(i,phi_n)==1) {
            e = i;
            break;
        }
    }
    d = modInverse(phi_n,e);

}

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(4444);

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    cout << "[TTP] Server running on port 4444\n";

    while (true) {
        int client = accept(server, nullptr, nullptr);

        char buffer[1024] = {0};
        recv(client, buffer, sizeof(buffer), 0);

        string msg(buffer);
        cout << "[TTP] Received: " << msg << endl;

        // REGISTER <name>
        if (msg.rfind("REGISTER ", 0) == 0) {
            string name = msg.substr(9);
            string fakeKey = "KEY_" + name;
            db[name] = fakeKey;

            string reply = "REGISTER_OK";
            send(client, reply.c_str(), reply.size(), 0);
        }

        // GET_KEY <name>
        else if (msg.rfind("GET_KEY ", 0) == 0) {
            string name = msg.substr(8);

            if (db.count(name)) {
                string reply = "KEY " + db[name];
                send(client, reply.c_str(), reply.size(), 0);
            } else {
                string reply = "NOT_FOUND";
                send(client, reply.c_str(), reply.size(), 0);
            }
        }

        // DELETE <name>
        else if (msg.rfind("DELETE ", 0) == 0) {
            string name = msg.substr(7);

            if (db.count(name)) {
                db.erase(name);
                string reply = "DELETED";
                send(client, reply.c_str(), reply.size(), 0);
            } else {
                string reply = "NOT_FOUND";
                send(client, reply.c_str(), reply.size(), 0);
            }
        }
        close(client);
    }
}
