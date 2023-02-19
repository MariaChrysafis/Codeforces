#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <cassert>
#include <cmath>

using namespace std;

using std::cout;
using std::endl;
using std::vector;
template <class T> class MinSegmentTree {
private:
    /** The operation to use for combining two elements. (Must be associative)
     */
    T comb(T a, T b) { return std::min(a, b); }
    const T DEFAULT = 1e8;  // Will overflow if T is an int

    vector<T> segtree;
    int len;

public:
    MinSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

    void update (int ind, T val) {
        assert(0 <= ind && ind < len);
        ind += len;
        if (val > segtree[ind]) {
            return;
        }
        segtree[ind] = min(val, segtree[ind]);
        for (; ind > 1; ind /= 2) {
            segtree[ind >> 1] = comb(segtree[ind], segtree[ind ^ 1]);
        }
    }

    T query (int start, int end) {
        assert(0 <= start && start < len && 0 < end && end <= len);
        T sum = DEFAULT;
        for (start += len, end += len; start < end; start /= 2, end /= 2) {
            if ((start & 1) != 0) { sum = comb(sum, segtree[start++]); }
            if ((end & 1) != 0) { sum = comb(sum, segtree[--end]); }
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N), inv(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        inv[a[i]] = i;
    }
    int sq = (int)sqrt(N);
    vector<pair<int,int>> queries[N];
    pair<int,int> vec[Q];
    for (int i = 0; i < Q; i++) {
        int l, r; cin >> l >> r;
        --l, --r;
        vec[i] = make_pair(l, r);
        queries[l].emplace_back(i, r);
    }
    MinSegmentTree<int> st(N + 2);
    int ans[N];
    for (int l = N - 1; l >= 0; l--) {
        for (int i = l + 1; i <= min(l + sq, N - 1); i++) {
            st.update(i, abs(a[i] - a[l]));
        }
        for (int i = -sq - 3; i <= sq + 3; i++) {
            if (a[l] + i > N or a[l] + i <= 0 or inv[a[l] + i] < l or i == 0) {
                continue;
            }
            st.update(inv[a[l] + i], abs(i));
        }
        for (int i = 0; i < queries[l].size(); i++) {
            ans[queries[l][i].first] = st.query(l, queries[l][i].second + 1);
        }
    }
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}
