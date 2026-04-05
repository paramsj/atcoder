#include <bits/stdc++.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

string myName;

void sendToTTP(string msg, string &reply)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in ttp{};
    ttp.sin_family = AF_INET;
    ttp.sin_port = htons(4444);
    inet_pton(AF_INET, "127.0.0.1", &ttp.sin_addr);

    connect(sock, (sockaddr*)&ttp, sizeof(ttp));
    send(sock, msg.c_str(), msg.size(), 0);

    char buf[1024] = {0};
    recv(sock, buf, sizeof(buf), 0);
    reply = buf;

    close(sock);
}

string getKey(string name)
{
    string res;
    sendToTTP("GET_KEY " + name, res);
    return res;
}

void registerMe()
{
    string reply;
    sendToTTP("REGISTER " + myName, reply);
    cout << "[Sender] " << reply << endl;
}

void deregisterMe()
{
    string reply;
    sendToTTP("DELETE " + myName, reply);
    cout << "[Sender] " << reply << endl;
}

void sendMessage()
{
    cout << "Enter receiver name: ";
    string recvName;
    cin >> recvName;

    // 1. Get key first
    string key = getKey(recvName);
    cout << "[Sender] Received from TTP: " << key << endl;

    // 2. Now send the message
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in recvAddr{};
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(3333);
    inet_pton(AF_INET, "127.0.0.1", &recvAddr.sin_addr);

    connect(sock, (sockaddr*)&recvAddr, sizeof(recvAddr));

    cout << "Enter message: ";
    cin.ignore();
    string msg;
    getline(cin, msg);

    send(sock, msg.c_str(), msg.size(), 0);
    close(sock);
}

int main()
{
    cout<<"What is your name"<<endl;
    cin>>myName;
    while (true) {
        cout << "\n--- Sender Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Send Message\n";   // this includes GET_KEY
        cout << "3. Deregister & Exit\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;

        if (ch == 1) registerMe();
        else if (ch == 2) sendMessage();
        else if (ch == 3) {
            deregisterMe();
            break;
        }
    }

    return 0;
}
