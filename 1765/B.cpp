#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include <climits>
#include <queue>
#include <bitset>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        bool fine = (s.size() % 3 != 2);
        for (int i = 2; i < s.size(); i += 3) {
            //cout << i << " " << s[i - 1] << '\n';
            if (s[i] != s[i - 1]) {
                fine = false;
            }
        }
        cout << (fine ? "YES\n" : "NO\n");
    }
}
