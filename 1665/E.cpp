#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct MergeSortTree {
    vector<int> a;
    vector<vector<int>> vec;

    vector<int> merge(vector<int> a, vector<int> b) {
        int x = 0, y = 0;
        vector<int> c;
        while (!(x == a.size() && y == b.size())) {
            if (x == a.size()) {
                c.push_back(b[y++]);
            } else if (y == b.size()) {
                c.push_back(a[x++]);
            } else if (a[x] < b[y]) {
                c.push_back(a[x++]);
            } else {
                c.push_back(b[y++]);
            }
        }
        return c;
    }

    vector<int> indices;

    void rec(int dum, int tl, int tr, int l, int r) {
        if (tl >= l && tr <= r) {
            indices.push_back(dum);
            return;
        }
        if (tr < l || tl > r) {
            return;
        }
        rec(2 * dum + 1, tl, (tl + tr) / 2, l, r);
        rec(2 * dum + 2, (tl + tr) / 2 + 1, tr, l, r);
    }

    void rec(int l, int r) {
        indices.clear();
        rec(0, 0, a.size() - 1, l, r);
    }

    void build(int dum, int tl, int tr) {
        if (tl == tr) {
            vec[dum].push_back(a[tl]);
            return;
        }
        build(2 * dum + 1, tl, (tl + tr) / 2);
        build(2 * dum + 2, (tl + tr) / 2 + 1, tr);
        vec[dum] = merge(vec[2 * dum + 1], vec[2 * dum + 2]);
    }

    MergeSortTree(vector<int> a) {
        int n = a.size();
        n = (1 << ((int) log2(n))) * 2;
        this->a.resize(n);
        for (int i = 0; i < a.size(); i++) {
            this->a[i] = a[i];
        }
        vec.resize(2 * n);
        build(0, 0, n - 1);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < a.size(); i++) {
        cin >> a[i];
    }
    MergeSortTree ms(a);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        ms.rec(l, r);
        int left[ms.indices.size()];
        int right[ms.indices.size()];
        for (int j = 0; j < ms.indices.size(); j++) {
            left[j] = 0;
            right[j] = ms.vec[ms.indices[j]].size() - 1;
        }
        vector<int> possible;
        int val = 0;
        int dig = 0;
        for (int x = 29; x >= 0; x--) {
            int powr = (1 << x);
            int cntr = 0;
            int last = -1;
            dig += (1 << x);
            for (int j = 0; j < ms.indices.size(); j++) {
                for (int k = left[j]; k <= min(right[j], left[j] + 1); k++) {
                    if ((ms.vec[ms.indices[j]][k] & powr) != powr) {
                        cntr++;
                        last = ms.vec[ms.indices[j]][k];
                    }
                }
            }
            for (int j: possible) {
                if ((j & (dig ^ val)) == 0) {
                    cntr++;
                }
            }
            if (cntr <= 1) {
                val ^= powr;
            }
            if (cntr == 1 && last != -1) {
                possible.push_back((last | (1 << x)));
            }
            for (int j = 0; j < ms.indices.size(); j++) {
                l = left[j];
                r = right[j];
                if (l > r) {
                    continue;
                }
                if ((ms.vec[ms.indices[j]][right[j]] & powr) == 0) { //all ones
                    if (cntr <= 1) {
                        left[j] = 1;
                        right[j] = 0;
                    }
                } else if ((ms.vec[ms.indices[j]][left[j]] & powr) == powr) { //all zeroes
                    if (cntr >= 2) {
                        left[j] = 1;
                        right[j] = 0;
                    }
                } else {
                    while (l != r) {
                        int m = (l + r + 1) / 2;
                        if ((ms.vec[ms.indices[j]][m] & powr) == powr) {
                            r = m - 1;
                        } else {
                            l = m;
                        }
                    }
                    if (cntr >= 2) {
                        right[j] = r;
                    } else {
                        left[j] = l + 1;
                    }
                }
            }
        }
        cout << val << '\n';
    }
}

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        solve();
    }
}
