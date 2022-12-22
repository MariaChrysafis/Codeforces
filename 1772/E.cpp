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
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] -= 1;
    }
    int c = 0;
    set<int> s[2], common;
    for (int i = 0; i < n; i++) {
        s[0].insert(i), s[1].insert(i);
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == i) {
            c ++;
            s[0].erase(i);
        }
        if (arr[i] == n - i - 1) {
            c --;
            s[1].erase(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[0].count(i) && s[1].count(i)) {
            common.insert(i);
            s[0].erase(i), s[1].erase(i);
        }
    }
    bool moves = 0;
    while (true) {
        if (s[0].empty() && common.empty()) {
            cout << "First\n";
            return;
        }
        if (s[1].empty() && common.empty()) {
            cout << "Second\n";
            return;
        }
        if (s[0].empty() && s[1].empty() && !common.empty()) {
            cout << "Tie\n";
            return;
        }
        if (!s[moves].empty()) {
            s[moves].erase(*s[moves].begin());
            moves = !moves;
            continue;
        }
        common.erase(*common.begin());
        moves = !moves;
    }
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
