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
        long long n, a, b;
        cin >> n >> a >> b;
        if (b >= a) {
            cout << (n + a - 1)/a << '\n';
        } else {
            cout << 1 << '\n';
        }
    }
}
