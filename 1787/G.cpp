#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <deque>
#include <cmath>
#include <queue>
#include <vector>
#include <iostream>
#include <iterator>
#include <map>
#include <functional>
using namespace std;
struct SegmentTree {
    vector<int64_t> vec;
    vector<int64_t> addLater;

    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }

    const int64_t INF = 0;

    int64_t upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return (vec[dum] += val);
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        int64_t left = upd(2 * dum, tl, mid, l, r, val);
        int64_t right = upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = max(vec[2 * dum], vec[2 * dum + 1]));
    }

    void upd(int l, int r, int64_t val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    int64_t get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return max(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    int64_t get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};
void dfs (map<pair<int,int>,int>& color, map<int,int> &num, vector<vector<int>>&adj, int cur, int prev) {
    queue<int> q;
    q.push(cur);
    set<int> vis;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (vis.count(p)) {
            continue;
        }
        vis.insert(p);
        for (int i: adj[p]) {
            int col = color[make_pair(p, i)];
            if (!num.count(col)) {
                num[col] = num.size();
            }
            q.push(i);
        }
    }
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    map<int,vector<pair<int,int>>> edges;
    map<int,int> weight;
    map<pair<int,int>,int> color;
    vector<vector<int>> adj(n);
    vector<int> deg;
    deg.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        u--, v--;
        deg[u]++, deg[v]++;
        adj[u].push_back(v), adj[v].push_back(u);
        edges[c].emplace_back(u, v);
        weight[c] += w;
        color[make_pair(u, v)] = color[make_pair(v, u)] = c;
    }
    for (auto& p: edges) {
        map<int,int> deg;
        for (auto& q: p.second) {
            deg[q.first]++, deg[q.second]++;
        }
        int c1 = 0;
        for (auto& q: deg) {
            if (q.second > 2) {
                weight[p.first] = 0;
            }
            c1 += (q.second == 1);
        }
        if (c1 > 2) {
            weight[p.first] = 0;
        }
    }
    int mx = -1;
    int ind = -1;
    for (int i = 0; i < deg.size(); i++) {
        if (deg[i] > mx) {
            mx = deg[i];
            ind = i;
        }
    }
    map<int,int> num;
    dfs(color, num, adj, ind, ind);
    vector<vector<pair<int,int>>> queries;
    for (int i = 0; i < n; i++) {
        //for each node that we update, which paths change?
        set<int> s;
        for (int j: adj[i]) {
            int col = color[make_pair(i, j)];
            s.insert(num[col]);
        }
        vector<pair<int,int>> dum;
        dum.push_back(make_pair(*s.begin(), *s.begin()));
        for (int i: s) {
            if (i == *s.begin()) continue;
            if (dum.back().second == i - 1) {
                dum.back().second++;
            } else {
                dum.emplace_back(make_pair(i, i));
            }
        }
        assert(dum.size() <= 1000);
        queries.push_back(dum);
    }
    SegmentTree st;
    st.resz(n);
    for (auto& p: weight) {
        st.upd(num[p.first], num[p.first], weight[p.first]);
    }
    //cout << st.get(0, n - 1) << '\n';
    const int64_t MX = 1e10;
    while (q--) {
        int p, x;
        cin >> p >> x;
        x--;
        if (p == 0) {
            for (auto& q: queries[x]) {
                st.upd(q.first, q.second, -MX);
            }
        } else {
            for (auto& q: queries[x]) {
                st.upd(q.first, q.second, MX);
            }
        }
        cout << max(st.get(0, n - 1), 0ll) << '\n';
    }

}
