#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;

    const auto f = [&](int num) {
        int ret = 0;
        while (num)
            ret += num % 10, num /= 10;
        return ret;
    };

    vector dp(r + 1, vector<int>(50, -1));
    vector pick(r + 1, vector<int>(50));

    const auto solve = [&](auto &&self, int cur, int prev) {
        if (cur > r)
            return 0;
        if (dp[cur][prev] != -1)
            return dp[cur][prev];
        auto first = self(self, cur + 1, prev);
        auto second = 0;
        if (f(cur) >= prev)
            second = 1 + self(self, cur + 1, f(cur));
        if (second > first)
            pick[cur][prev] = 1;
        return dp[cur][prev] = max(first, second);
    };
    solve(solve, l, 0);

    basic_string<int> res;
    int cur = l, prev = 0;
    while (cur <= r) {
        if (pick[cur][prev])
            res += cur, prev = f(cur);
        ++cur;
    }

    res.resize(n);

    for (int val : res)
        cout << val << ' ';
    cout << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}