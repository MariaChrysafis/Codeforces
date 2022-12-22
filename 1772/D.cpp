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
        int n;
        cin >> n;
        vector<int64_t> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        vector<vector<pair<int64_t,int64_t> > > vec(n);
        for (int i = 1; i < n; i++) {
            //|v[i] - x| > |v[i - 1] - x|
            //v[i] > x && v[i - 1] > x --> v[i] > v[i - 1]
            if (v[i] >= v[i - 1]) {
                vec[i].emplace_back(0, min(v[i], v[i - 1]));
            }
            //v[i] < x && v[i - 1] < x --> x - v[i] > x - v[i - 1] --> v[i] <= v[i - 1]
            if (v[i] <= v[i - 1]) {
                vec[i].emplace_back(max(v[i], v[i - 1]), int64_t(3e9));
            }
            //v[i] < x && v[i - 1] > x --> x - v[i] > v[i - 1] - x --> 2x > v[i - 1] + v[i]
            if (v[i] <= v[i - 1]) {
                vec[i].emplace_back(max((v[i - 1] + v[i] + 1)/2, v[i]), v[i - 1]);
            }
            //v[i] > x && v[i - 1] < x --> v[i] - x > x - v[i - 1] --> 2x < v[i - 1] + v[i]
            if (v[i] >= v[i - 1]) {
                vec[i].emplace_back(v[i - 1], (v[i - 1] + v[i])/2);
            }
        }
        set<int64_t> s;
        for (int i = 0; i < vec.size(); i++) {
            for (auto& p: vec[i]) {
                s.insert(p.first);
                s.insert(p.second);
            }
        }
        bool broken = false;
        for (int64_t x: s) {
            bool fine = true;
            for (int i = 1; i < vec.size(); i++) {
                bool okay = false;
                for (auto& p: vec[i]) {
                    if (x >= p.first && x <= p.second) {
                        okay = true;
                    }
                }
                if (!okay) {
                    fine = false;
                    break;
                }
            }
            if (fine) {
                cout << x << '\n';
                broken = true;
                break;
            }
        }
        if (!broken) {
            cout << "-1\n";
        }
    }

}
