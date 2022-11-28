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
    int n;
    cin >> n;
    long long arr[n][n];
    long long diagonal = LLONG_MAX;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            sum += arr[i][j];
        }
        diagonal = min(diagonal, arr[i][n - i - 1]);
    }
    cout << sum - diagonal << '\n';
}
