#include <bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 998244353;

void caesarCipher() {
    cout << "Enter the plaintext: ";
    string s;
    cin.ignore();
    getline(cin, s);

    int key;
    cout << "Enter how much you want to shift the letters by? ";
    cin >> key;

    string cipher = s;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            int place = (s[i] - 'a' + key) % 26;
            cipher[i] = char('a' + place);
        }
    }
    cout << "Ciphertext: " << cipher << endl;
}

void monoAlphabetic() {
    cout << "Enter the plaintext: ";
    cin.ignore();
    string s;
    getline(cin, s);

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    random_shuffle(alphabet.begin(), alphabet.end());
    map<char, char> mapping;
    string ans = s;
    int j = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            if (!mapping.count(s[i])) {
                mapping[s[i]] = alphabet[j++];
            }
            ans[i] = mapping[s[i]];
        }
    }
    cout << "Ciphertext: " << ans << endl;
}

void playFair() {
    cout << "Enter the plaintext: ";
    cin.ignore();
    string s;
    getline(cin, s);

    string key;
    cout << "Enter key for Playfair: ";
    cin >> key;

    string cleanKey;
    vector<bool> seen(26, false);
    for (char c : key) {
        if (c == ' ') continue;
        c = tolower(c);
        if (c == 'j') c = 'i';
        if (!seen[c - 'a']) {
            seen[c - 'a'] = true;
            cleanKey.push_back(c);
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue;
        if (!seen[c - 'a']) {
            seen[c - 'a'] = true;
            cleanKey.push_back(c);
        }
    }

    vector<vector<char>> matrix(5, vector<char>(5));
    map<char, pair<int, int>> pos;
    int idx = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = cleanKey[idx];
            pos[cleanKey[idx]] = {i, j};
            idx++;
        }
    }

    string plain;
    for (char c : s) {
        if (c == ' ') continue;
        c = tolower(c);
        if (c == 'j') c = 'i';
        plain.push_back(c);
    }

    string prepared;
    for (int i = 0; i < plain.size(); i++) {
        prepared.push_back(plain[i]);
        if (i + 1 < plain.size() && plain[i] == plain[i + 1]) {
            prepared.push_back('x');
        }
    }
    if (prepared.size() % 2) prepared.push_back('x');

    string cipher;
    for (int i = 0; i < prepared.size(); i += 2) {
        char a = prepared[i], b = prepared[i + 1];
        auto [r1, c1] = pos[a];
        auto [r2, c2] = pos[b];

        if (r1 == r2) {
            cipher.push_back(matrix[r1][(c1 + 1) % 5]);
            cipher.push_back(matrix[r2][(c2 + 1) % 5]);
        } else if (c1 == c2) {
            cipher.push_back(matrix[(r1 + 1) % 5][c1]);
            cipher.push_back(matrix[(r2 + 1) % 5][c2]);
        } else {
            cipher.push_back(matrix[r1][c2]);
            cipher.push_back(matrix[r2][c1]);
        }
    }

    cout << "Ciphertext: " << cipher << endl;
}

vector<int> matrixMulti(vector<int> &a, vector<vector<int>> &key) {
    vector<int> res(3, 0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[i] = (res[i] + a[j] * key[i][j]) % 26; 
        }
    }
    return res;
}

void hillCipher() {
    cout << "Enter the plaintext: ";
    cin.ignore();
    string s;
    getline(cin, s);

    vector<vector<int>> key(3, vector<int>(3));
    cout << "Enter 3x3 key matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> key[i][j];
        }
    }

    string clean;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            clean.push_back(s[i]);
        }
    }
    while ((clean.length() % 3) != 0) {
        clean.push_back('x');
    }

    for (int i = 0; i < clean.length(); i += 3) {
        vector<int> temp;
        for (int j = 0; j < 3; j++) {
            temp.push_back(clean[i + j] - 'a');
        }
        vector<int> cipher = matrixMulti(temp, key);
        for (int j = 0; j < 3; j++) {
            clean[i + j] = char(cipher[j] + 'a');
        }
    }
    cout << "Ciphertext: " << clean << endl;
}

void polyAlphabetic() {
    cout << "Enter the plaintext: ";
    cin.ignore();
    string s;
    getline(cin, s);

    string key;
    cout << "Enter key: ";
    cin >> key;

    string clean;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ') {
            clean.push_back(s[i]);
        }
    }

    string fullKey = key;
    int j = 0;
    while (fullKey.size() < clean.size()) {
        fullKey.push_back(key[j]);
        j = (j + 1) % key.size();
    }

    string cipher = clean;
    for (int i = 0; i < clean.length(); i++) {
        cipher[i] = char(((clean[i] - 'a') + (fullKey[i] - 'a')) % 26 + 'a');
    }
    cout << "Ciphertext: " << cipher << endl;
}

signed main() {
    while (true) {

        cout << "1. Caesar Cipher" <<endl;
        cout << "2. Monoalphabetic Cipher" <<endl;
        cout << "3. Playfair Cipher" <<endl;
        cout << "4. Hill Cipher" <<endl;
        cout << "5. Polyalphabetic Cipher" <<endl;
        cout << "6. Quit" <<endl;
        cout << "Choose an option: " <<endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            caesarCipher();
        } else if (choice == 2) {
            monoAlphabetic();
            cout<<endl;
        } else if (choice == 3) {
            playFair();
            cout<<endl;
        } else if (choice == 4) {
            hillCipher();
            cout<<endl;
        } else if (choice == 5) {
            polyAlphabetic();
            cout<<endl;
        } else if (choice == 6) {
            cout << "Done! Bye Bye!"<<endl;
            break;
        } else {
            cout << "Invalid choice, try again!"<<endl;
            cout<<endl;
        }
    }
    return 0;
}
