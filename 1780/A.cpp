#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int arr[n];
        vector<int> oc[2];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            oc[arr[i] % 2].push_back(i + 1);
        }
        if (oc[1].size() >= 3) {
            cout << "YES\n" << oc[1][0] << " " << oc[1][1] << " " << oc[1][2] << '\n';
            continue;
        }
        if (oc[1].size() >= 1 && oc[0].size() >= 2) {
            cout << "YES\n" << oc[0][0] << " " << oc[0][1] << " " << oc[1][0] << '\n';
            continue;
        }
        cout << "NO\n";
    }
}
