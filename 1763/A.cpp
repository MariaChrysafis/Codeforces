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
    int n;
    cin >> n;
    int64_t arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int64_t ans = 0;
    for (int i = 0; i < 31; i++) {
        int64_t mn = (1 << i);
        int64_t mx = 0;
        for (int j = 0; j < n; j++) {
            mn = min(mn, arr[j] & (1 << i));
            mx = max(mx, arr[j] & (1 << i));
        }
        ans += mx - mn;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
