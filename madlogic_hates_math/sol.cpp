#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e9 + 7;

auto mul(int a, int b) -> int {
    a %= MOD, a += MOD, a %= MOD;
    b %= MOD, b += MOD, b %= MOD;
    return (1ll * a * b) % MOD;
}

auto add(int a, int b) -> int {
    a %= MOD, a += MOD, a %= MOD;
    b %= MOD, b += MOD, b %= MOD;
    return (0ll + a + b + MOD) % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int &val : a)
        cin >> val;

    int res = 0;
    for (int i = 0; i < n; i++)
        res = add(res, mul(a[i], mul(i + 1, i + 1)));

    vector<int> st;
    vector<int> prev(n, -1);
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[i] > a[st.back()])
            st.pop_back();
        if (!st.empty())
            prev[i] = st.back();
        st.push_back(i);
    }

    vector<int> nxt(n, n);
    st.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[i] >= a[st.back()])
            st.pop_back();
        if (!st.empty())
            nxt[i] = st.back();
        st.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        auto left = i - prev[i];
        auto right = nxt[i] - i;
        res = add(res, mul(a[i], mul(left, right)));
        res = add(res, -a[i]);
    }

    cout << res << '\n';

    return 0;
}