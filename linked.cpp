#include<bits/stdc++.h>
using namespace std;
#define int long long int

struct Node {
	int data;
	Node* next;

	Node(int value) {
		data = value;
		next = nullptr;
	}
};

Node* reverseList(Node* head) {
	Node* curr = head;
	Node* prev = nullptr;
	while(curr!=NULL) {
		Node* temp = new Node(curr->data);
		temp->next = prev;
		prev = temp;
		curr = curr->next;
	}
	Node* gg = prev;
	while(gg!=NULL) {
		cout<<(gg->data)<<" ";
		gg = gg->next;
	}
	return prev;
}
void solve() {
	Node* a = new Node(10);
	Node* b = new Node(20);
	Node* c = new Node(30);
	a->next = b;
	b->next = c;
	Node* temp = a;
	while(temp!=NULL) {
		cout<<(temp->data)<<" ";
		temp = temp->next;
	}
	reverseList(a);
}
signed main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	solve();
	return 0;
}