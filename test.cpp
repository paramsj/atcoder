#include <bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 1000000007;

void solve() {
 unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 g(seed);

    int T = 1; // number of random testcases
    cout << T << "\n";

    for (int t = 0; t < T; ++t) {
        uniform_int_distribution<int> n_dist(5000, 5000);
        int N = n_dist(g);

        uniform_int_distribution<int> D_dist(1, max(1ll, N / 10));
        int D = D_dist(g);

        uniform_int_distribution<int> R_dist(max(1ll, N / 10), max(2ll, N / 3));
        int R = min(N, R_dist(g));

        // Create permutation with local structure (not purely random)
        vector<int> A(N);
        iota(A.begin(), A.end(), 1);

        // Divide into random-sized chunks and shuffle locally
        int idx = 0;
        while (idx < N) {
            int chunk = uniform_int_distribution<int>(5, max(5ll, N / 10))(g);
            int end = min(N, idx + chunk);
            shuffle(A.begin() + idx, A.begin() + end, g);
            idx = end;
        }

        // Occasionally reverse or rotate sections to create irregularity
        if (uniform_int_distribution<int>(0, 1)(g)) {
            reverse(A.begin() + N / 4, A.end());
        }
        if (uniform_int_distribution<int>(0, 1)(g)) {
            rotate(A.begin(), A.begin() + (N / 3), A.end());
        }

        cout << N << " " << D << " " << R << "\n";
        for (int i = 0; i < N; ++i)
            cout << A[i] << (i + 1 == N ? '\n' : ' ');
    }

}
signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}