#include <bits/stdc++.h>
using namespace std;

auto solve() -> void {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    const auto min_change = [&](int x, int y) { return abs(x - y); };

    const auto get_to = [&](int x, int y) {
        if (x == 0)
            return min(y + 2, 10 - y);
        else
            return min(10 - y + 1, y + 1);
    };

    const auto get_dist = [&](int x, int y) {
        return min((y - x + 10) % 10, (x - y + 10) % 10);
    };

    auto dp = vector(n, vector(10, -1));

    const auto solve = [&](auto &&self, int idx, int cur) {
        if (idx == n)
            return 0;
        if (cur != -1 && dp[idx][cur] != -1)
            return dp[idx][cur];
        int cur_val = (cur == -1 ? a[idx] - '0' : cur);
        if (idx == n - 1)
            return get_dist(b[idx] - '0', cur_val);
        auto ret =
            min({get_to(9, cur_val) + min_change(b[idx] - '0', 9) +
                     self(self, idx + 1, 9),
                 get_to(0, cur_val) + min_change(b[idx] - '0', 0) +
                     self(self, idx + 1, 0),
                 get_to(0, cur_val) + get_to(9, 0) +
                     min_change(b[idx] - '0', 9) + self(self, idx + 1, 9),
                 get_to(9, cur_val) + get_to(0, 9) +
                     min_change(b[idx] - '0', 0) + self(self, idx + 1, 0),
                 min_change(b[idx] - '0', cur_val) + self(self, idx + 1, cur)});
        return (cur == -1 ? ret : dp[idx][cur] = ret);
    };

    cout << solve(solve, 0, -1) << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}