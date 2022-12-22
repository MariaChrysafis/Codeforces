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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int k, n;
        cin >> k >> n;
        vector<int> v(k);
        v[0] = 1;
        for (int i = 1; i < k; i++) {
            if (v[i - 1] + i + (k - 1 - i) > n) {
                v[i] = v[i - 1] + 1;
                continue;
            }
            v[i] = min(v[i - 1] + i, n);
        }
        for (int j: v) {
            cout << j << ' ';
        }
        cout << '\n';
    }

}
