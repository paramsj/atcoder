#include <bits/stdc++.h>
using namespace std;

// mex of a[l..r], 0-based indices
int mex_of(const vector<int>& a, int l, int r) {
    int n = a.size();
    vector<char> seen(n + 2, 0); // we only need to check 0..n
    for (int i = l; i <= r; ++i) {
        if (0 <= a[i] && a[i] <= n) seen[a[i]] = 1;
    }
    for (int x = 0; x <= n; ++x) if (!seen[x]) return x;
    return n + 1; // theoretically won't reach for permutations but kept for safety
}

// check exact interval-wise equality of mex values
bool similar(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            if (mex_of(a, l, r) != mex_of(b, l, r)) return false;
        }
    }
    return true;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // We'll permute the values themselves (handles duplicates correctly).
    vector<int> p = a;
    sort(p.begin(), p.end());

    do {
        if (similar(a, p)) {
            // print permutation (the array b)
            for (int i = 0; i < n; ++i) {
                if (i) cout << ' ';
                cout << p[i];
            }
            cout << '\n';
        }
    } while (next_permutation(p.begin(), p.end()));

    return 0;
}
