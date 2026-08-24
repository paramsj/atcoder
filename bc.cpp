#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int v) {
        data = v;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node *root,int value) {
    if(root==nullptr) {
        return new Node(value);
    }
    if(root->data < value) {
        root->right = insert(root->right,value);
    } else {
        root->left = insert(root->left,value);
    }
    return root;
}

Node *search(Node *root,int value) {
    if(root == nullptr) {
        return false;
    }
    if(root->data == value) {
        return true;
    }
    if(root->data < value) {
        return search(root->right,value);
    }
    return search(root->left,value);
}

Node* getInorderSuccessor(Node *root) {
    while(root->left!=nullptr) {
        root = root->left;
    }
    return root;
}
Node *del(Node *root,int value) {
    if(root == nullptr) {
        return root;
    }
    if(root->data < value) {
        root->right = del(root->right,value);
    } else if(root->data > value) {
        root->left = del(root->left,value);
    } else {
        if(root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        if(root->left==nullptr) {
            Node *temp = root;
            root = root->right;
            delete temp;
            return root   
        }

        if(root->right==nullptr) {
            Node *temp = root;
            root = root->left;
            delete temp;
            return root   
        }

        Node *temp = getInorderSuccessor(root->right);
        root->data = temp->data;
        root->right = delete(root->right,temp->data);

    }
    return search(root->left,value);
}

void solve() {


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