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

void registerMe()
{
    string reply;
    sendToTTP("REGISTER " + myName, reply);
    cout << "[Receiver] " << reply << endl;
}

void deregisterMe()
{
    string reply;
    sendToTTP("DELETE " + myName, reply);
    cout << "[Receiver] " << reply << endl;
}

void waitForSender()
{
    int server = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(3333);

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    cout << "[Receiver] Waiting on port 3333...\n";

    int client = accept(server, nullptr, nullptr);

    char buf[1024] = {0};
    recv(client, buf, sizeof(buf), 0);
    cout << "[Receiver] Message: " << buf << endl;
}

int main()
{
	cout<<"What is your name"<<endl;
	cin>>myName;
    while (true) {
        cout << "\n--- Receiver Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Wait For Message\n";
        cout << "3. Deregister & Exit\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;

        if (ch == 1) registerMe();
        else if (ch == 2) waitForSender();
        else if (ch == 3) {
            deregisterMe();
            break;
        }
    }

    return 0;
}
