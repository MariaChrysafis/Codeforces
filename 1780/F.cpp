#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
int gcd (int x, int y) {
    return ((!x || !y) ? max(x, y) : gcd(max(x, y) % min(x, y), min(x, y)));
}
const int MX = 3e5 + 1;
bool isPrime[MX];
vector<int> prime_factors[MX];
vector<int> factors[MX];
int64_t contrib (vector<int64_t>& f, int x) {
    int64_t ans = 0;
    for (int i = 0; i < (1 << (int)prime_factors[x].size()); i++) {
        int prod = 1;
        for (int j = 0; j < (int)prime_factors[x].size(); j++) {
            if (i & (1 << j)) {
                prod *= prime_factors[x][j];
            }
        }
        ans += pow(-1, __builtin_popcount(i)) * f[prod];
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < MX; i++) {
        isPrime[i] = true;
        factors[i] = {1};
    }
    isPrime[1] = false;
    for (int i = 2; i < MX; i++) {
        if (isPrime[i]) {
            prime_factors[i].push_back(i);
        }
        for (int j = 2 * i; j < MX; j += i) {
            isPrime[j] = false;
            if (isPrime[i]) {
                prime_factors[j].push_back(i);
            }
            factors[j].push_back(i);
        }
        factors[i].push_back(i);
    }
    int N;
    cin >> N;
    int arr[N];
    int cont[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + N);
    vector<int64_t> left(MX), right(MX);
    left.assign(MX, 0);
    right.assign(MX, 0);
    int64_t l = 0, r = 0;
    for (int i = 0; i < N; i++) {
        r += contrib(right, arr[i]);
        for (int j: factors[arr[i]]) {
            right[j]++;
        }
    }
    for (int i = 0; i < N; i++) {
        cont[i] = contrib(right, arr[i]) - (arr[i] == 1);
    }
    int64_t tot = r;
    int64_t ans = 0;
    for (int i = 0; i < N - 1; i++) {
        for (int j: factors[arr[i]]) {
            right[j]--;
        }
        r -= contrib(right, arr[i]);
        ans += tot - l - r - cont[i];
        l += contrib(left, arr[i]);
        for (int j: factors[arr[i]]) {
            left[j]++;
        }
    }
    cout << ans << '\n';
}
