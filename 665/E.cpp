#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <queue>

using namespace std;

struct Trie {
    Trie* children[2];
    int depth = 0;
    int sz = 0;
    Trie (int depth) {
        children[0] = children[1] = nullptr, this->depth = depth, this->sz = 0;
    }
    void add_node (int x) {
        this->sz++;
        if (depth == -1) {
            return;
        }
        bool b = (x & (1 << depth));
        if (!this->children[b]) {
            this->children[b] = new Trie(depth - 1);
        }
        this->children[b]->add_node(x);
    }
    int64_t get (int x, int k) { //how many y are there such that x ^ y >= k
        if (k <= 0) {
            return this->sz;
        }
        if (depth < 0) {
            return 0;
        }
        if ((1ll << (depth + 1)) < k) {
            return 0;
        }
        assert(depth >= 0);
        int ans = 0;
        bool b = !(x & (1 << this->depth));
        if (this->children[b]) ans += this->children[b]->get(x, k - (1 << depth));
        if (this->children[!b]) ans += this->children[!b]->get(x, k);
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Trie* root = new Trie(31);
    int n, k;
    cin >> n >> k;
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        dp[i] = dp[i - 1] ^ x;
    }
    for (int i = 0; i <= n; i++) {
        root->add_node(dp[i]);
    }
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += root->get(dp[i], k);
    }
    cout << ans/2;
}
