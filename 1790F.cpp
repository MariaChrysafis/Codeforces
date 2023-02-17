#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = INT_MAX;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        int c[N];
        for (int i = 0; i < N; i++) {
            cin >> c[i];
            --c[i];
        }
        int dist[N];
        vector<int> adj[N];
        for (int i = 0; i < N - 1; i++) {
            dist[i] = dist[i + 1] = INF;
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int ans = INT_MAX;
        for (int i = 0; i < N; i++) {
            ans = min(ans, dist[c[i]]);
            queue<pair<int,int>> q;
            q.push(make_pair(c[i], 0));
            while (!q.empty()) {
                auto p = q.front();
                q.pop();
                if (p.second >= ans) {
                    continue;
                }
                if (dist[p.first] <= p.second) {
                    continue;
                }
                dist[p.first] = p.second;
                for (int x: adj[p.first]) {
                    q.push(make_pair(x, p.second + 1));
                }
            }
            if (i != 0) {
                cout << ans << ' ';
            }
        }
        cout << '\n';
    }
}
