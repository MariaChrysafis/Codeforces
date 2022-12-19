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

bool solve () {
    priority_queue<pair<int,int>> pq;
    int64_t n, k;
    cin >> n >> k;
    int64_t h[n];
    int64_t p[n];
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    vector<pair<int64_t,int64_t> > vec;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        vec.emplace_back(p[i], h[i]);
    }
    sort(vec.begin(), vec.end());
    int64_t tot = 0;
    for (int _ = 0; _ < vec.size(); _++) {
        int64_t power = vec[_].first;
        int64_t health = vec[_].second - tot;
        while (k > 0 && health - k > 0) {
            health -= k;
            tot += k;
            k -= power;
        }
    }
    return (k > 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        bool b = solve();
        if (b) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
