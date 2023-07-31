//from ordered_set import OrderedSet
#include <iostream>
#include <set>
#include <cassert>
#include <vector>
using namespace std;
int main() {
    int n;
    cin >> n;
    int sz[n + 1];
    sz[1] = 1;
    for (int i = 1; i <= n + 1; i++) {
        sz[i] = 1;
        for (int a = 2; a * a <= i; a++) {
            if (i % a == 0) {
                sz[i] = sz[i/a];
                if (i % (a * a) != 0) {
                    sz[i]++;
                }
                break;
            }
        }
    }
    set<pair<int,int>> fact1[n + 1];
    set<int> fact2[n + 1];
    for (int i = n; i >= 2; i--) {
        if (sz[i] != 1) {
            continue;
        }
        for (int j = i; j <= n; j += i) {
            fact1[i].insert(make_pair(sz[j], j));
            fact2[j].insert(-i);
        }
    }
    set<pair<int,int>> s;
    for (int i = 1; i <= n; i++) {
        s.insert(make_pair(sz[i], i));
    }
    vector<pair<int,int>> res;
    while (!s.empty()) {
        auto remove = [&] (int x) {
            for (int i: fact2[x]) {
                assert(fact1[-i].count(make_pair(sz[x], x)));
                fact1[-i].erase(make_pair(sz[x], x));
            }
            s.erase(make_pair(sz[x], x));
        };
        auto p = *(s.begin());
        remove(p.second);
        pair<int,int> ans = make_pair(p.second, -1);
        for (int i: fact2[p.second]) { //look at all factors of p.first
            if (fact1[-i].empty()) continue;
            auto it = fact1[-i].begin();
            auto q = *it;
            remove(q.second);
            ans.second = q.second;
            break;
        }
        if (ans.second != -1) {
            res.emplace_back(ans);
        }
    }
    cout << res.size() << '\n';
    for (auto& p: res) {
        cout << p.first << " " << p.second << '\n';
    }
}
