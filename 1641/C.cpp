#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
#include <queue>
#include <cmath>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#include <ctime>

using namespace std;

struct segmentTree {
    vector<int64_t> vec;
    vector<int64_t> setLater;

    void push(int v, int tl, int tr) {
        if (setLater[v] == -1) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] = setLater[v];
        vec[2 * v + 1] = setLater[v] * (tr - tm);
        setLater[2 * v] = setLater[v];
        vec[2 * v] = setLater[v] * (tm - tl + 1);
        setLater[v] = -1;
    }

    const int64_t INF = 0;

    int64_t upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            setLater[dum] = val;
            return (vec[dum] = val * (tr - tl + 1));
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = vec[2 * dum] + vec[2 * dum + 1]);
    }

    void update (int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    int64_t get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }

    int64_t get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, -1);
    }

};

template<class T>
class SegmentTree {
public:

    SegmentTree (int N) {
        N = (1 << ((int)floor(log2(N - 1)) + 1));
        this->N = N;
        val.assign(2 * N, ID);
    }

    void update (int x, T y) {
        x += N - 1;
        val[x] = y;
        while (x != 0) {
            x = (x - 1)/2;
            val[x] = merge(val[2 * x + 1], val[2 * x + 2]);
        }
    }

    T query (int ind, const int l, const int r, int tl, int tr) {
        if (tl >= l && tr <= r) {
            return val[ind];
        }
        if (tr < l || tl > r) {
            return ID;
        }
        return merge(query(2 * ind + 1, l, r, tl, (tl + tr)/2), query(2 * ind + 2, l, r, (tl + tr)/2 + 1, tr));
    }

    T query (int l, int r) {
        return query(0, l, r, 0, N - 1);
    }
private:
    vector<T> val;
    T ID = INT_MAX;
    T merge (T x, T y) {
        return min(x, y);
    }
    int N;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    segmentTree st;
    st.resz(n);
    st.update(0, n - 1, 1);
    SegmentTree<int> rng(n);
    for (int i = 0; i < n; i++) {
        rng.update(i, INT_MAX);
    }
    while (q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            if (x == 0) {
                st.update(l, r, 0);
            } else {
                rng.update(l, min(rng.query(l, l), r));
            }
        } else {
            int x;
            cin >> x;
            x--;
            if (st.get(x, x) == 0) {
                cout << "NO\n";
                continue;
            } else {
                int r = x;
                int l = 0;
                while (l != r) {
                    int m = (l + r)/2;
                    if (st.get(m, x) != 1) {
                        l = m + 1;
                    } else {
                        r = m;
                    }
                }
                int left = l;
                l = x;
                r = n - 1;
                while (l != r) {
                    int m = (l + r + 1)/2;
                    if (st.get(x, m) != 1) {
                        r = m - 1;
                    } else {
                        l = m;
                    }
                }
                int right = l;
                if (rng.query(left, right) <= right && rng.query(left, right) != INT_MAX) {
                    cout << "YES\n";
                } else {
                    cout << "N/A\n";
                }
            }
        }
    }
}
