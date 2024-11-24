#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> u(n - 1), v(n - 1), deg(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> u[i] >> v[i];
        --u[i], --v[i];
        ++deg[u[i]];
        ++deg[v[i]];
    }

    vector<int> second_deg(n);
    for (int i = 0; i < n - 1; i++)
        if (deg[u[i]] > 1 && deg[v[i]] > 1)
            ++second_deg[u[i]], ++second_deg[v[i]];

    basic_string<int> ends;

    bool ok = true;
    if (*max_element(begin(second_deg), end(second_deg)) > 2)
        ok = false;

    int twos = 0, ones = 0;
    for (int i = 0; i < n; i++)
        if (second_deg[i] == 1)
            ++ones, ends.push_back(i);
        else if (second_deg[i] == 2)
            ++twos;
    ok &= (ones == 2);

    vector cc(n, vector(2, false));
    if (ok && (ones + twos)) {
        for (int j = 0; j < 2; j++)
            cc[ends[j]][j] = true;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < 2; j++) {
                if (u[i] == ends[j] && deg[v[i]] == 1)
                    cc[v[i]][j] = true;
                if (v[i] == ends[j] && deg[u[i]] == 1)
                    cc[u[i]][j] = true;
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int s, t;
        cin >> s >> t;
        --s;
        --t;
        cout << ((ones + twos == 0) || (ok && ((cc[s][0] && cc[t][1]) ||
                                               (cc[s][1] && cc[t][0])))
                     ? "YES\n"
                     : "NO\n");
    }
    return 0;
}