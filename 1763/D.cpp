#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
#include <queue>
#include <cmath>
#include <map>
#include <stack>
#include <ctime>
using namespace std;

void solve () {
    int n, i, j, x, y;
    cin >> n >> i >> j >> x >> y;
    i--, j--, x--, y--;
    int64_t MOD = 1e9 + 7;
    int64_t dp[n + 1][n + 1];
    for (int left = 0; left <= n; left++) {
        for (int right = 0; right <= n; right++) {
            dp[left][right] = 0;
        }
    }
    dp[0][0] = 1;
    for (int left = 0; left <= n + 1; left++) {
        for (int right = 0; left + right <= n; right++) {
            int val = left + right - 1;
            if (left != 0) {
                if (((left - 1 == i) == (val == x)) && ((left - 1 == j) == (val == y))) {
                    dp[left][right] += dp[left - 1][right];
                }
            }
            if (right != 0) {
                if (((n - right == i) == (val == x)) && ((n - right == j) == (val == y))) {
                    dp[left][right] += dp[left][right - 1];
                }
            }
            dp[left][right] %= MOD;
        }
    }
    int64_t val = 0;
    for (int left = 0; left <= n; left++) {
        val += dp[left][n - left];
        val %= MOD;
    }
    int64_t ans =(val * (MOD + 1)/2) % MOD;
    ans -= (i == x && j == y);
    ans -= (i == n - x - 1 && j == n - y - 1);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
