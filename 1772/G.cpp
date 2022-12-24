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
void solve () {
    int64_t n, x, y;
    cin >> n >> x >> y;
    vector<int64_t> a(n);
    for (int64_t i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<int64_t> pref(n + 1);
    pref[0] = 0;
    int64_t cnt = 0;
    for (int64_t i = 1; i <= n; i++) {
        pref[i] = max(pref[i - 1], a[i - 1] - (i - 1));
        cnt += (pref[i] <= x);
        if (cnt + x == y) {
            cout << i << '\n';
            return;
        }
    }
    if (cnt <= n - cnt) {
        cout << -1 << '\n';
        return;
    }
    int64_t myMin = LLONG_MAX;
    for (int64_t i = 0; i != -1; i++) {
        int64_t lo = 0;
        int64_t hi = n - 1;
        while (lo != hi) {
            int64_t mid = (lo + hi + 1)/2;
            if (pref[mid + 1] <= x) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        if (x + lo + 1 >= y || lo == n - 1) {
            cout << min(i * n + y - x, myMin) << '\n';
            return;
        }
        int64_t upd = 2 * (lo + 1) - n;
        x += upd;
        if (x + (lo + 1) >= y) {
            cout << (i + 1) * n + (y - x) << '\n';
            return;
        }
        int64_t gamma = (y - x - (lo + 1) + upd - 1)/upd;
        myMin = min((gamma + i + 1) * n + (y - (x + upd * gamma)), myMin);
        if (x >= pref[lo + 2]) {
            continue;
        }
        gamma = (pref[lo + 2] - x + upd - 1)/upd;
        i += gamma;
        x += upd * gamma;
    }
    cout << -1 << '\n';
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
