#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;



void pre_cal(vector<vector<vector<long long>>>& dp) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) {
            if (i == j) {
                dp[0][i][j] = 1;
            }
            else {
                dp[0][i][j] = 0;
            }
        }

    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) {
            if (i == 2 && j == 3 || i == 2 && j == 4 || i == 4 && j == 3 || i == 4 && j == 4) {
                dp[1][i][j] = 0;
            }
            else {
                dp[1][i][j] = 1;
            }
        }
}


void full_cal(vector<vector<vector<long long>>>& dp, const long long& p) {
    for (int l = 2; l < 51; ++l) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                dp[l][i][j] = 0;
                for (int ii = 0; ii < 5; ++ii) {
                    for (int jj = 0; jj < 5; ++jj) {
                        if (ii == 2 && jj == 3 || ii == 2 && jj == 4 || ii == 4 && jj == 3 || ii == 4 && jj == 4) continue;
                        dp[l][i][j] += ((dp[l - 1][i][ii] % p) * (dp[l - 1][jj][j] % p)) % p;
                    }
                }
            }
        }
    }
}


long long result(const vector<vector<vector<long long>>>& dp, const long long& x, const long long& p) {
    long long n = x;
    long long k = 1ll << 50;
    vector<vector<long long>> a(5, vector<long long>(5));
    int d = 50;
    long long ans = 0;
    while (k > n) {
        k /= 2;
        d--;
    }
    n -= k;
    a = dp[d];
    while (k > 0 && n > 0) {
        if (n >= k) {
            n -= k;
            vector<vector<long long>> temp = a;
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    a[i][j] = 0;
                    for (int ii = 0; ii < 5; ++ii)
                        for (int jj = 0; jj < 5; ++jj) {
                            if (ii == 2 && jj == 3 || ii == 2 && jj == 4 || ii == 4 && jj == 3 || ii == 4 && jj == 4) continue;
                            a[i][j] += ((temp[i][ii] % p) * (dp[d][jj][j] % p)) % p;
                        }
                }
            }
        }
        k /= 2;
        d--;
    }
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            ans += a[i][j];
            ans %= p;
        }
    }

    return ans;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const long long p = 999999937;
    vector<vector<vector<long long>>> dp(51, vector<vector<long long>>(5, vector<long long>(5)));

    pre_cal(dp);
    full_cal(dp);

    long long n;
    cin >> n;

    while (n > 0) {
        cout << result(dp, n) << endl;
        cin >> n;
    }

    return 0;
}