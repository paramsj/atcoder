#include<bits/stdc++.h>
#define int long long int
using namespace std;

struct Node {
    int max_val;
    Node(int max_val) : max_val(max_val) {}
    Node() : max_val(0) {} 
};

Node merge(Node a, Node b) {
    return Node(max(a.max_val, b.max_val));
}

struct SegmentTree {
    int n;
    vector<Node> tree;

    SegmentTree(int n) : n(n) {
        tree.resize(4 * n + 1);
    }

    void build(int idx, int tl, int th, const vector<int> &a) {
        if(tl == th) {
            tree[idx] = Node(a[tl]);
            return;
        }
        int mid = (tl + th) / 2;
        build(2 * idx, tl, mid, a);
        build(2 * idx + 1, mid + 1, th, a);
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }

    Node query(int idx, int tl, int th, int ql, int qh) {
        if(ql <= tl && th <= qh) {
            return tree[idx];
        }
        if(ql > th || qh < tl) {
            return Node();
        }
        int mid = (tl + th) / 2;
        return merge(query(2 * idx, tl, mid, ql, qh), query(2 * idx + 1, mid + 1, th, ql, qh));
    }

    void update(int idx, int tl, int th, int pos, int val) {
        if(tl == th) {
            tree[idx] = Node(val);
            return;
        }
        int mid = (tl + th) / 2;
        if(pos <= mid) {
            update(2 * idx, tl, mid, pos, val);
        } else {
            update(2 * idx + 1, mid + 1, th, pos, val);
        }
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
    }
};

struct HLD {
    int n, LOG;
    vector<vector<int>> adj;
    vector<int> subtreeSize, depth, heavyChild, chainHead, segTreePos;
    vector<vector<int>> up;
    vector<int> baseArray;
    int currentPos;
    SegmentTree st;

    HLD(int n, const vector<vector<int>>& adj, const vector<int>& nodeValues) 
        : n(n), adj(adj), st(n) {
        
        LOG = ceil(log2(n + 1)) + 1;
        subtreeSize.resize(n + 1);
        depth.resize(n + 1);
        heavyChild.assign(n + 1, -1);
        chainHead.resize(n + 1);
        segTreePos.resize(n + 1);
        baseArray.resize(n + 1);
        up.assign(n + 1, vector<int>(LOG, 0));
        currentPos = 1;

        dfs_sz(1, 0, 0);
        dfs_hld(1, 0, 1, nodeValues);
        st.build(1, 1, n, baseArray);
    }

    int dfs_sz(int u, int p, int d) {
        subtreeSize[u] = 1;
        depth[u] = d;
    
        up[u][0] = p;
        for(int i = 1; i < LOG; i++) {
            up[u][i] = up[ up[u][i-1] ][i-1];
        }

        int maxSubtree = 0;
        for (int v : adj[u]) {
            if (v != p) {
                int subSize = dfs_sz(v, u, d + 1);
                subtreeSize[u] += subSize;
                if (subSize > maxSubtree) {
                    maxSubtree = subSize;
                    heavyChild[u] = v;
                }
            }
        }
        return subtreeSize[u];
    }

    void dfs_hld(int u, int p, int headNode, const vector<int>& nodeValues) {
        chainHead[u] = headNode;
        segTreePos[u] = currentPos;
        baseArray[currentPos] = nodeValues[u];
        currentPos++;

        if (heavyChild[u] != -1) {
            dfs_hld(heavyChild[u], u, headNode, nodeValues);
        }

        for (int v : adj[u]) {
            if (v != p && v != heavyChild[u]) {
                dfs_hld(v, u, v, nodeValues);
            }
        }
    }

    int getLCA(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for(int i = LOG - 1; i >= 0; i--) {
            if((diff >> i) & 1) {
                u = up[u][i];
            }
        }
        if(u == v) return u;
        for(int i = LOG - 1; i >= 0; i--) {
            if(up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    void updateNode(int node, int newValue) {
        st.update(1, 1, n, segTreePos[node], newValue);
    }

    int queryPathUpward(int u, int lca) {
        Node result = Node();
        
        while (chainHead[u] != chainHead[lca]) {
            result = merge(result, st.query(1, 1, n, segTreePos[chainHead[u]], segTreePos[u]));
            u = up[chainHead[u]][0];
        }
        result = merge(result, st.query(1, 1, n, segTreePos[lca], segTreePos[u]));
        
        return result.max_val;
    }

    int queryPath(int u, int v) {
        int lca = getLCA(u, v);
        int maxU = queryPathUpward(u, lca);
        int maxV = queryPathUpward(v, lca);
        return max(maxU, maxV);
    }
};


void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> nodeValues(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> nodeValues[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HLD hld(n, adj, nodeValues);

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int node, newValue;
            cin >> node >> newValue;
            hld.updateNode(node, newValue);
        } else if (type == 2) {
            int u, v;
            cin >> u >> v;
            cout << hld.queryPath(u, v) << " ";
        }
    }
    cout << "\n";
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}