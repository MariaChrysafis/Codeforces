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

string pickK(string s, int k) {
    set<int> oc[11];
    for (int i = 0; i < s.size(); i++) {
        oc[s[i] - '0'].insert(i);
    }
    int pick = k;
    int prev = -1;
    string res = "";
    for (int i = 0; i < pick; i++) {
        //prev + 1
        for (int x = 0; x <= 9; x++) {
            if (!oc[x].empty() and oc[x].lower_bound(prev + 1) != oc[x].end()) {
                auto it = oc[x].lower_bound(prev + 1);
                int ind = *it;
                if (s.size() - ind >= pick - i) {
                    prev = ind;
                    res += '0' + x;
                    break;
                }
            }
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int k;
        cin >> k;
        k = s.size() - k;
        int first_oc[10];
        for (int i = 0; i < 10; i++) {
            first_oc[i] = -1;
        }
        for (int i = 0; i < s.size(); i++) {
            if (first_oc[s[i] - '0'] == -1) {
                first_oc[s[i] - '0'] = i;
            }
        }
        int starting_index = 0;
        for (int x = 1; x <= 9; x++) {
            if (first_oc[x] == -1) {
                continue;
            }
            if (s.size() - first_oc[x] >= k) {
                starting_index = first_oc[x];
                break;
            }
        }
        string after = "";
        for (int i = starting_index + 1; i < s.size(); i++) {
            after += s[i];
        }
        after = s[starting_index] + pickK(after, k - 1);
        cout << after << '\n';
    }
}
