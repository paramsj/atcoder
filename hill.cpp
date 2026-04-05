#include<bits/stdc++.h>
using namespace std;
#define int long long int

vector<int> matrixMulti(vector<int> temp, vector<vector<int>> &key) {
    vector<int> res(2,0);
    for(int i=0;i<2;i++) {
        int val = 0;
        for(int j=0;j<2;j++) {
            val = (val + (temp[j] * key[i][j]) % 26) % 26;
        }
        res[i] = val;
    }
    return res;
}

// function to find modular inverse mod 26
int modInverse(int a) {
    a = (a % 26 + 26) % 26;
    for(int x = 1; x < 26; x++) {
        if((a * x) % 26 == 1) return x;
    }
    return -1; // no inverse exists
}

void solve() {
    // taking 2x2 key matrix
    vector<vector<int>> key(2,vector<int>(2));
    for(int i=0;i<2;i++) {
        for(int j=0;j<2;j++) {
            cin >> key[i][j];
        }
    }
    
    string s;
    cin >> s;

    // pad 'x' if odd length
    while(s.length() % 2 != 0) {
        s.push_back('x');
    }

    // ENCRYPTION
    string cipher;
    for(int i=0;i<s.length(); i += 2) {
        vector<int> temp;
        temp.push_back(s[i] - 'a');
        temp.push_back(s[i+1] - 'a');

        vector<int> ct = matrixMulti(temp, key);

        cipher.push_back(char(ct[0] + 'a'));
        cipher.push_back(char(ct[1] + 'a'));
    }

    cout << "Cipher: " << cipher << endl;

    // ------------------------------
    // DECRYPTION STARTS HERE
    // ------------------------------

    // determinant
    int det = ((key[0][0]*key[1][1]) - (key[0][1]*key[1][0])) % 26;
    det = (det + 26) % 26;

    // find modular inverse of determinant
    int invDet = modInverse(det);
    if(invDet == -1) {
        cout << "Key is not invertible modulo 26, cannot decrypt!" << endl;
        return;
    }

    // inverse key matrix (adjoint × inverse(det))
    vector<vector<int>> invKey(2,vector<int>(2));
    invKey[0][0] =  (key[1][1] * invDet) % 26;
    invKey[0][1] = ((-key[0][1] + 26) * invDet) % 26;
    invKey[1][0] = ((-key[1][0] + 26) * invDet) % 26;
    invKey[1][1] =  (key[0][0] * invDet) % 26;

    // DECRYPT NOW
    string plain;
    for(int i=0;i<cipher.length(); i += 2) {
        vector<int> temp;
        temp.push_back(cipher[i] - 'a');
        temp.push_back(cipher[i+1] - 'a');

        vector<int> pt = matrixMulti(temp, invKey);

        plain.push_back(char(pt[0] + 'a'));
        plain.push_back(char(pt[1] + 'a'));
    }

    cout << "Decrypted: " << plain << endl;
    
}

signed main() {
    solve();
    return 0;
}
