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
        vector<int> v;
        for (int i = 0; i < 4; i++) {
            int x;
            cin >> x;
            v.push_back(x);
        }
        bool fine = false;
        for (int i = 0; i < 4; i++) {
            vector<int> gamma = v;
            gamma[0] = v[2], gamma[1] = v[0], gamma[2] = v[3], gamma[3] = v[1];
            v = gamma;
            if (v[0] < v[1] && v[2] < v[3] && v[0] < v[2] && v[1] < v[3]) {
                fine = true;
            }
        }
        cout << (fine ? "YES\n" : "NO\n");
    }

}
