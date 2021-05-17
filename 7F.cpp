#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;


pair<pair<long long, int>, vector<vector<long long>>> shortest_length(const int& n, const vector<vector<int>>& a) {
    const long long INF = 1000000000;
    long long p = 1ll << n;
    vector<vector<long long>> dp(n, vector<long long>(p, INF));

    for (int i = 0; i < n; ++i) {
        dp[i][1 << i] = 0;
    }

    for (int i = 1; i < p; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = 0; l < n; ++l) {
                if ((((1 << j) & i) != 0) && (((1 << l) & i) == 0)) {
                    int newmask = i | (1 << l);
                    dp[l][newmask] = min(dp[l][newmask], dp[j][i] + a[j][l]);
                }
            }
        }
    }

    long long ans = INF;
    int k = 0;
    p--;

    for (int i = 0; i < n; ++i) {
        if (ans > dp[i][p]) {
            ans = dp[i][p];
            k = i;
        }
    }

    return { { ans, k }, dp };
}

string way(const pair<pair<long long, int>, vector<vector<long long>>>& glob, const int& n, const vector<vector<int>>& a) {
    auto ans = glob.first.first;
    auto k = glob.first.second;
    auto dp = glob.second;
    vector <int> b(1);
    b[0] = k + 1;
    long long p = (1ll << n) - (1ll << k) - 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (((1ll << j) & p) != 0)
                if (dp[j][p] + a[j][k] == ans) {
                    ans = dp[j][p];
                    k = j;
                    break;
                }
        }
        b.push_back(k + 1);
        p -= (1ll << k);
    }

    string str = "";
    for (int i = n - 1; i >= 0; --i) {
        str += to_string(b[i]) + " ";
    }

    return str;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }

    auto res = shortest_length(n, a);
    cout << res.first.first << endl;
    cout << way(res, n, a);

    return 0;
}