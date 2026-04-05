#include <bits/stdc++.h>
using namespace std;
#define int long long int
const int MOD = 998244353;

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
int test = 1;

bool dfs(int n, int pos, vector<bool>& vis, vector<int>& path) {
    if (path.size() == n) return true;

    for (int mv : {2, 3, -2, -3}) {
        int next = pos + mv;
        if (next >= 1 && next <= n && !vis[next]) {
            vis[next] = true;
            path.push_back(next);
            if (dfs(n, next, vis, path)) return true;
            path.pop_back();
            vis[next] = false;
        }
    }
    return false;
}

vector<int> solve_case(int n) {
    for (int start = 1; start <= n; ++start) {
        vector<bool> vis(n + 1, false);
        vector<int> path = {start};
        vis[start] = true;
        if (dfs(n, start, vis, path)) {
            return path;
        }
    }
    return {}; 
}

static void  main2() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> result = solve_case(n);
        if (result.empty()) {
            cout << -1 << "\n";
        } else {
            for (int x : result) cout << x << " ";
            cout << "\n";
        }
    }
}




static void run_with_stack_size(void (*func)(), size_t stsize) {
    char *stack, *send;
    stack=(char *)malloc(stsize);
    send=stack+stsize-16;
    send=(char *)((uintptr_t)send/16*16);
    asm volatile(
    "mov %%rsp, (%0)\n"
            "mov %0, %%rsp\n"
    :
    : "r" (send));
    func();
    asm volatile(
    "mov (%0), %%rsp\n"
    :
    : "r" (send));
    free(stack);
}

signed main() {
    run_with_stack_size(main2, 256*1024*1024);
}




