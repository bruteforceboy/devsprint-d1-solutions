#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<vector<int>> c(3, vector<int>(2));

        const auto sig = [&](int x) { return (x < 0 ? 0 : 1); };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                int x;
                cin >> x;
                if (x)
                    ++c[j][sig(x)];
            }
        }

        const auto f = [&](int num) { return num * (num - 1) >> 1; };

        int res = 0;
        for (int i = 0; i < 3; i++)
            for (int j = i + 1; j < 3; j++)
                for (int itr = 0; itr < 2; itr++)
                    res += f(c[i][itr]) * f(c[j][1 - itr]),
                        res += f(c[i][itr]) * f(c[j][itr]);

        for (int i = 0; i < 3; i++)
            for (int j = i + 1; j < 3; j++)
                res += (c[i][0] * c[i][1]) * (c[j][0] * c[j][1]);

        cout << res << '\n';
    }

    return 0;
}