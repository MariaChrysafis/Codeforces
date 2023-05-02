#include <iostream>
#include <set>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;
const int MX = (int)5e6 + 10;
int phi[MX];
int spf[MX];
int depth[MX];
void print(set<int>&s) {
    for (int i: s) {
        cout << i << ' ';
    }
    cout << '\n';
}
set<int> notone;
struct Node {
    int res;
    int sum = 0;
    Node (int x) {
        this->res = x;
        this->sum = depth[x];
    }
};
int combine (int x, int y) {
    while (y != x) {
        if (y > x) {
            swap(y, x);
        }
        x = phi[x];
    }
    return x;
}
Node id = Node(1);
Node merge (Node n1, Node n2) {
    if (n1.res == -1) return n2;
    if (n2.res == -1) return n1;
    Node res = Node(1);
    res.sum = n1.sum + n2.sum;
    res.res = combine(n1.res, n2.res);
    return res;
}
struct SegmentTree {
    vector<Node> vec;
    void update (int x) {
        x = x + (int)vec.size()/2 - 1;
        if (vec[x].res == 1) {
            return;
        }
        vec[x].res = phi[vec[x].res];
        vec[x].sum = depth[vec[x].res];
        if (vec[x].res == 1) {
            notone.erase(x - (int)vec.size()/2 + 1);
        }
        while (x != 0) {
            x = (x - 1)/2;
            vec[x] = merge(vec[2 * x + 1], vec[2 * x + 2]);
        }
    }
    Node query (int dum, int tl, int tr, int l, int r) {
        if (tr < l or tl > r) {
            return id;
        }
        if (tl >= l and tr <= r) {
            return vec[dum];
        }
        return merge(query(2 * dum + 1, tl, (tl + tr)/2, l, r), query(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r));
    }
    void build (vector<int>& v, int dum) {
        if (dum >= (int)v.size() - 1) {
            assert(v[dum - (int)v.size() + 1] != 0);
            vec[dum] = Node(v[dum - (int)v.size() + 1]);
            return;
        }
        build(v, 2 * dum + 1);
        build(v, 2 * dum + 2);
        vec[dum] = merge(vec[2 * dum + 1], vec[2 * dum + 2]);
    }
    SegmentTree (vector<int> v) {
        int sz = (1 << (int)log2(v.size())) * 2;
        while (v.size() != sz) {
            v.push_back(1);
        }
        vec.assign(v.size() * 2, Node(1));
        build(v, 0);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    id.res = -1;
    for (int i = 0; i < MX; i++) {
        spf[i] = i;
    }
    spf[0] = spf[1] = false;
    for (int i = 2; i < MX; i++) {
        if (spf[i] == i) {
            int j = 2 * i;
            while (j < MX) {
                spf[j] = min(spf[j], i);
                j += i;
            }
        }
    }
    depth[1] = 1;
    for (int i = 2; i < MX; i++) {
        if (spf[i] == i) {
            phi[i] = i - 1;
        } else if (i % (spf[i] * spf[i]) == 0) {
            phi[i] = phi[i/spf[i]] * spf[i];
        } else {
            phi[i] = phi[i/spf[i]] * (spf[i] - 1);
        }
        depth[i] = depth[phi[i]] + 1;
    }
    phi[1] = 1;
    int N, M;
    cin >> N >> M;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        if (arr[i] != 1) {
            notone.insert(i);
        }
    }
    SegmentTree st = SegmentTree(arr);
    //exit(0);
    for (int i = 0; i < M; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        --l, --r;
        if (t == 2) {
            auto myNode = st.query(0, 0, (int)st.vec.size()/2 - 1, l, r);
            cout << myNode.sum - depth[myNode.res] * (r - l + 1) << '\n';
        } else {
            auto it = notone.lower_bound(l);
            vector<int> u;
            while (it != notone.end() and *it <= r) {
                u.push_back(*it);
                it++;
            }
            for (int i: u) {
                st.update(i);
            }
        }
    }

}
