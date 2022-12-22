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
vector<pair<int,int> > spots (vector<vector<char> > &grid) {
    vector<pair<int,int> > ans;
    for (int i = 1; i < grid.size() - 1; i++) {
        for (int j = 1; j < grid[i].size() - 1; j++) {
            bool fine = true;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1) {
                        if (grid[i + dx][j + dy] == grid[i][j]) {
                            fine = false;
                        }
                    }
                }
            }
            if (fine) {
                ans.emplace_back(i, j);
            }
        }
    }
    return ans;
}
vector<pair<int,int> > dif (vector<pair<int,int>> prev, vector<pair<int,int>> cur) {
    map<pair<int,int>,int> m1, m2;
    for (auto& p: prev) {
        m1[p] += 1;
    }
    for (auto& p: cur) {
        m2[p] += 1;
    }
    vector<pair<int,int> > ans;
    for (auto& p: prev) {
        if (m1.count(p) && !m2.count(p)) {
            ans.push_back(p);
        }
        if (m2.count(p) && !m1.count(p)) {
            ans.push_back(p);
        }
    }
    return ans;
}
void solve () {
    int n, m, k;
    cin >> n >> m >> k;
    vector< pair<pair<int, vector<pair<int,int>>>,int> > vec;
    map<pair<int,int>,set<int> > myMap;
    for (int i = 0; i < k + 1; i++) {
        vector<vector<char> > grid(n);
        for (int j = 0; j < n; j++) {
            string s;
            cin >> s;
            for (int k = 0; k < s.size(); k++) {
                grid[j].push_back(s[k]);
                myMap[make_pair(j, k)].insert(s[k] - '0');
            }
        }
        auto f = spots(grid);
        vec.push_back(make_pair(make_pair(f.size(), f), i));
    }
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    cout << vec[0].second + 1 << '\n';
    vector<vector<int> > ans;
    for (int i = 1; i < vec.size(); i++) {
        auto prev = vec[i - 1].first.second;
        auto cur = vec[i].first.second;
        //cout << 2 << " " << vec[i].second + 1 << '\n';
        for (auto& p: dif(prev, cur)) {
            if (myMap[p].size() == 1) {
                continue;
            }
            ans.push_back({1, p.first + 1, p.second + 1});
            //cout << 1 << " " << p.first + 1 << " " << p.second + 1 << '\n';
        }
        ans.push_back({2, vec[i].second + 1});
    }
    cout << ans.size() << '\n';
    for (auto& q: ans) {
        for (int x: q) {
            cout << x << ' ';
        }
        cout << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
