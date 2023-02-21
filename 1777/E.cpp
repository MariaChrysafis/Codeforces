#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <cassert>
#include <bit>
#include <bitset>
#include <cmath>

using namespace std;

struct Graph {
    vector<vector<int>> adj;
private:
    vector<vector<int>> adj_rev;
    vector<bool> vis;
    vector<int> order;
    vector<vector<int>> comp;
    void dfs (int curNode) {
        vis[curNode] = true;
        for (int i: adj[curNode]) {
            if (!vis[i]) {
                dfs (i);
            }
        }
        order.push_back(curNode);
    }
    void rev_dfs (int curNode) {
        comp.back().push_back(curNode);
        vis[curNode] = true;
        for (int i: adj_rev[curNode]) {
            if (!vis[i]) {
                rev_dfs (i);
            }
        }
    }
public:
    Graph (int n) {
        adj.resize(n);
        adj_rev.resize(n);
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    vector<vector<int>> read () {
        vis.assign(adj.size(), false);
        for (int i = 0; i < adj.size(); i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        vis.assign(adj.size(), false);
        reverse(order.begin(), order.end());
        for (int i: order) {
            if (!vis[i]) {
                comp.emplace_back();
                rev_dfs(i);
            }
        }
        return comp;
    }
};

set<int> vis;

void dfs (vector<vector<int>>& adj, int x) {
    vis.insert(x);
    for (int i: adj[x]) {
        if (!vis.count(i)) {
            dfs (adj, i);
        }
    }
}

bool okay (vector<pair<pair<int,int>,int>> v, int x) {
    int n = 0;
    for (auto& p: v) {
        n = max(n, max(p.first.first, p.first.second) + 1);
    }
    Graph gr (n);
    auto add = v; add.clear();
    for (auto& p: v) {
        gr.add_edge(p.first.first, p.first.second);
        if (p.second <= x) {
            gr.add_edge(p.first.second, p.first.first);
        }
    }
    auto gamma = gr.read();
    int id[n];
    for (int i = 0; i < gamma.size(); i++) {
        for (int j: gamma[i]) {
            id[j] = i;
        }
    }
    vector<vector<int>> adj(gamma.size());
    for (int i = 0; i < gr.adj.size(); i++) {
        for (int j: gr.adj[i]) {
            if (id[j] != id[i]) {
                adj[id[i]].push_back(id[j]);
            }
        }
    }
    vis.clear();
    dfs(adj, 0);
    return (vis.size() == gamma.size());
}

void solve () {
    int N, M;
    cin >> N >> M;
    Graph gr(N);
    vector<pair<pair<int,int>,int>> vec;
    vector<vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        vec.push_back(make_pair(make_pair(u, v), w));
    }
    vis.clear();
    dfs(adj, 0);
    if (vis.size() != N) {
        cout << -1 << '\n';
        return;
    }
    int l = 0;
    int r = 1e9 + 1;
    while (l != r) {
        int m = (l + r)/2;
        if (okay(vec, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    if (l == 1e9 + 1) {
        l = -1;
    }
    cout << l << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
