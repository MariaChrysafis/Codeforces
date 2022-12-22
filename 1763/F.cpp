#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
#include <queue>
#include <cmath>
#include <map>
#include <unordered_map>
#include <stack>
#include <ctime>
using namespace std;
class DisjointSetUnion {
protected: //
    vector<int> parent;
    vector<int> compSize;
    const int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    DisjointSetUnion(int sz) : n(sz), connectedComponents(sz) {
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};

class Graph {
    vector<bool> hasVisited;
    vector<pair<int,int>> edges;
    vector<int> parent;
    vector<int> sub;
    vector<int> depth;
    void dfs (int curNode) {
        hasVisited[curNode] = true;
        for (int i: adj[curNode]) {
            if (!hasVisited[i]) {
                new_adj[i].push_back(curNode), new_adj[curNode].push_back(i);
                parent[i] = curNode;
                depth[i] = depth[curNode] + 1;
                dfs (i);
            }
        }
    }
public:
    vector<vector<int>> adj;
    vector<vector<int>> new_adj;
    void add_edge (int u, int v) {
        edges.emplace_back(u, v);
        adj[u].push_back(v), adj[v].push_back(u);
    }
    Graph (int n) {
        new_adj.resize(n), adj.resize(n), hasVisited.assign(n, false), parent.assign(n, -1), sub.resize(n), depth.resize(n);
    }
    void fill (int curNode, int prevNode) {
        for (int i: new_adj[curNode]) {
            if (i != prevNode) {
                fill (i, curNode);
                sub[curNode] += sub[i];
            }
        }
    }
    vector<pair<int,int>> read() {
        depth[0] = 0;
        dfs (0);
        for (auto& p: edges) {
            if (parent[p.first] == p.second || parent[p.second] == p.first) {
                continue;
            }
            if (depth[p.first] > depth[p.second]) {
                swap(p.first, p.second);
            }
            sub[p.first] += -1;
            sub[p.second] += 1;
        }
        fill (0, 0);
        vector<pair<int,int>> roads;
        set<pair<int,int> > s;
        for (int i = 0; i < adj.size(); i++) {
            for (int j: adj[i]) {
                s.insert(make_pair(min(i, j), max(i, j)));
            }
        }
        for (int i = 1; i < (int)adj.size(); i++) {
            if (sub[i] == 0) {
                s.erase(make_pair(min(i, parent[i]), max(i, parent[i])));
                roads.emplace_back(i + 1, parent[i] + 1);
            }
        }
        return std::vector<pair<int,int>>(s.begin(), s.end());
    }
};
struct Tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<vector<int>> sum;
    vector<int> enter;
    vector<int> exit;
    vector<int> val;
    vector<map<int,int> > myMap;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev){
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }
    void dfs1 (int u, int prev) {
        sum[u][0] = 0;
        if (myMap[u].count(prev)) sum[u][0] = val[myMap[u][prev]];
        for (int i = 1; i <= lg2; i++) {
            sum[u][i] = merge(u, dp[u][i - 1], dp[u][i], sum[u][i - 1], sum[dp[u][i - 1]][i - 1]);
        }
        for (int v: adj[u]) {
            if (v != prev) {
                dfs1 (v, u);
            }
        }
    }
    bool isAncestor(int u, int v){
        //is u an ancestor of v
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }
    int leastCommonAncestor(int u, int v){
        if(isAncestor(u, v)){
            return u;
        }
        if(isAncestor(v, u)){
            return v;
        }
        for(int i = lg2; i >= 0; i--){
            if(!isAncestor(dp[u][i], v)){
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    int next_to (int a, int m) { //one away from m
        if (isAncestor(m, a)) {
            for(int i = lg2; i >= 0; i--){
                if(!isAncestor(dp[a][i], m)){
                    a = dp[a][i];
                }
            }
            return a;
        } else {
            return dp[m][0];
        }
    }
    int merge (int a, int m, int b, int cost_m_a, int cost_m_b) {
        //[a, m] and [m, b]
        int m_a = next_to(a, m);
        int m_b = next_to(b, m);
        return cost_m_a + cost_m_b - (myMap[m].count(m_b) && myMap[m].count(m_a) && myMap[m][m_b] == myMap[m][m_a]) * val[myMap[m][m_b]];
    }
    int get (int u, int v) { //v is ancestor of u
        int ans = 0;
        int orig = u;
        for (int i = lg2; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v) || dp[u][i] == v) {
                ans = merge(orig, u, dp[u][i], ans, sum[u][i]);
                u = dp[u][i];
            }
        }
        return ans;
    }
    void read(){
        int n = adj.size();
        lg2 = ceil(log2(n));
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        sum.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            sum[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
        dfs1(0, 0);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    Graph gr(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        gr.add_edge(a, b);
    }
    auto bridges = gr.read();
    DisjointSetUnion dsu(n);
    for (auto& q: bridges) {
        dsu.join(q.first, q.second);
    }
    Tree tree;
    tree.adj = gr.new_adj;
    tree.myMap.resize(n);
    int Q;
    cin >> Q;
    vector<int> cnt;
    cnt.assign(gr.adj.size(), 0);
    for (int i = 0; i < gr.adj.size(); i++) {
        for (int j: gr.adj[i]) {
            if (dsu.find_head(i) == dsu.find_head(j)) {
                cnt[dsu.find_head(i)] ++;
            }
        }
    }
    tree.val = cnt;
    for (int i = 0; i < gr.new_adj.size(); i++) {
        for (int j: gr.adj[i]) {
            if (dsu.comp(i, j)) {
                tree.myMap[i].insert(make_pair(j, dsu.find_head(i)));
            }
        }
    }
    tree.read();
    while (Q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a == b) {
            cout << 0 << '\n';
            continue;
        }
        int lca = tree.leastCommonAncestor(a, b);
        int get_a = tree.get(a, lca);
        int get_b = tree.get(b, lca);
        cout << tree.merge(a, lca, b, get_a, get_b)/2 << '\n';
    }

}
