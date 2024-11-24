#include <bits/stdc++.h>
using namespace std;

struct Modular {
    int value;
    static int mod;

    Modular(int64_t v = 0) {
        value = v % mod;
        if (value < 0)
            value += mod;
    }

    static void setMod(int m) { mod = m; }

    Modular &operator+=(Modular const &b) {
        value += b.value;
        if (value >= mod)
            value -= mod;
        return *this;
    }
    Modular &operator-=(Modular const &b) {
        value -= b.value;
        if (value < 0)
            value += mod;
        return *this;
    }
    Modular &operator*=(Modular const &b) {
        value = (int64_t) value * b.value % mod;
        return *this;
    }
    Modular &operator/=(Modular const &b) { return *this *= inverse(b); }

    friend Modular power(Modular a, int64_t e) {
        Modular res = 1;
        for (; e; e >>= 1, a *= a)
            if (e & 1)
                res *= a;
        return res;
    }
    friend Modular inverse(Modular a) { return power(a, mod - 2); }

    friend Modular operator+(Modular a, Modular const b) { return a += b; }
    friend Modular operator-(Modular a, Modular const b) { return a -= b; }
    friend Modular operator-(Modular const a) { return 0 - a; }
    friend Modular operator*(Modular a, Modular const b) { return a *= b; }
    friend Modular operator/(Modular a, Modular const b) { return a /= b; }

    friend bool operator==(Modular const &a, Modular const &b) {
        return a.value == b.value;
    }
    friend bool operator!=(Modular const &a, Modular const &b) {
        return a.value != b.value;
    }

    friend ostream &operator<<(ostream &os, Modular const &a) {
        return os << a.value;
    }
};

int Modular::mod = 1e9 + 7;

struct Matrix {
    using T = Modular;

    int n, m;
    vector<vector<T>> matrix;

    Matrix(const vector<vector<T>> &mat)
        : n(mat.size()), m(mat[0].size()), matrix(mat) {}

    Matrix &operator+=(Matrix const &b) {
        assert(n == b.matrix.size() && m == b.matrix[0].size());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                matrix[i][j] += b.matrix[i][j];
        return *this;
    }
    Matrix &operator-=(Matrix const &b) {
        assert(n == b.matrix.size() && m == b.matrix[0].size());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                matrix[i][j] -= b.matrix[i][j];
        return *this;
    }
    Matrix &operator*=(Matrix const &b) {
        assert(m == b.matrix.size());
        int k = b.matrix[0].size();
        vector<vector<T>> res(n, vector<T>(k));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < k; j++)
                for (int x = 0; x < m; x++)
                    res[i][j] += matrix[i][x] * b.matrix[x][j];
        matrix = res;
        return *this;
    }

    friend Matrix operator+(Matrix a, Matrix const b) { return a += b; }
    friend Matrix operator-(Matrix a, Matrix const b) { return a -= b; }
    friend Matrix operator*(Matrix a, Matrix const b) { return a *= b; }
    friend bool operator==(Matrix const &a, Matrix const &b) {
        return a.matrix == b.matrix;
    }
    friend bool operator!=(Matrix const &a, Matrix const &b) {
        return a.matrix != b.matrix;
    }

    Matrix pow(int64_t e) {
        assert(n == m);
        vector<vector<T>> identity(n, vector<T>(m, static_cast<T>(0)));
        for (int i = 0; i < n; i++)
            identity[i][i] = 1;
        Matrix result(identity), a(matrix);
        while (e) {
            if (e & 1)
                result = result * a;
            a = a * a;
            e >>= 1;
        }
        return result;
    }
    friend ostream &operator<<(ostream &out, Matrix const &a) {
        int n = a.matrix.size(), m = a.matrix[0].size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                out << a.matrix[i][j] << " \n"[j == m - 1];
        return out;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        int n, k, m;
        cin >> n >> k >> m;

        Modular::setMod(m);

        vector<vector<Matrix::T>> vec{{1, 0}};
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            vec[0].push_back(x);
        }

        n += 2;

        vector<vector<Matrix::T>> mat(n, vector<Matrix::T>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j <= i; j++)
                mat[j][i] = 1;

        auto a = Matrix(vec);
        auto b = Matrix(mat);
        b = b.pow(k);

        a = a * b;

        for (int i = 2; i < n; i++)
            cout << a.matrix[0][i] << ' ';
        cout << '\n';
    }

    return 0;
}