#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <deque>
#include <vector>
#include <iostream>
#include <iterator>
#include <functional>
using namespace std;
void solve (int n, int k, int x) {
    int b_xor = 0;
    for (int i = 1; i <= n; i++) {
        b_xor ^= i;
    }
    if (b_xor != ((k % 2 == 0) ? 0 : x)) {
        cout << "NO\n";
        return;
    }
    vector<bool> s;
    s.assign(n + 1, true);
    s[0] = false;
    vector<pair<int,int>> v;
    if (x <= n and s[x]) {
        s[x] = false;
        v.push_back({0, x});
    }
    for (int i = 1; i <= n; i++) {
        if (i <= (x ^ i) and (x ^ i) <= n) {
            s[i] = false;
            s[x ^ i] = false;
            v.push_back({i, (x ^ i)});
            continue;
        }
    }
    vector<int> vec;
    for (int i = 1; i <= n; i++) {
        if (s[i]) {
            vec.push_back(i);
        }
    }
    if (v.size() + (vec.empty() ? 0 : 1) < k) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    while (v.size() + (vec.empty() ? 0 : 1) != k) {
        auto p = v.back();
        v.pop_back();
        if (p.first != 0) vec.push_back(p.first);
        if (p.second != 0) vec.push_back(p.second);
    }
    if (!vec.empty()) {
        cout << vec.size()  << ' ';
        for (int i: vec) {
            cout << i << ' ';
        }
        cout << '\n';
    }
    for (auto& p: v) {
        if (p.first == 0) {
            cout << 1 << " " << p.second << '\n';
            continue;
        }
        cout << 2 << " " << p.first << " " << p.second << '\n';
    }
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, k, x;
        cin >> n >> k >> x;
        solve(n, k, x);
    }
}
