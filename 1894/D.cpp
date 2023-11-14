#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <map>
using namespace std;
bool comp (pair<int,int> p, pair<int,int> q) {
    return (p.second - p.first < q.second - q.first);
}
int main () {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n + 2);
        a[0] = (int)1e9 + 10;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        a[n + 1] = 0;
        multiset<int> b;
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            b.insert(x);
        }
        vector<int> ans;
        for (int i = 0; i < a.size(); i++) {
            ans.push_back(a[i]);
            if (a[i] >= a[i + 1]) {
                while (true) {
                    //a[i + 1], a[i]
                    auto it = b.upper_bound(a[i]);
                    if (it == b.begin()) {
                        break;
                    }
                    --it;
                    int x = *it;
                    if (!(x >= a[i + 1] && x <= a[i])) {
                        break;
                    }
                    b.erase(b.find(x));
                    ans.push_back(x);
                }
            }
        }
        for (int i = 1; i < ans.size() - 1; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}


