#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinComps(vector<int> r, const vector<int>& r2) {
    int p = r.size(), v = r2.size();
    sort(rbegin(r), rend(r));
    vector<pair<int, int>> dp(1 << v, { 1e9, 0 });
    dp[0] = { 0, 0 };
    for (int i = 1;i < 1 << v;i++) {
        for (int j = 0;j < v;j++) {
            if (i & (1 << j)) {
                if (dp[i ^ (1 << j)].second >= r2[j]) {
                    if (dp[i].first > dp[i ^ (1 << j)].first ||
                        dp[i].first == dp[i ^ (1 << j)].first &&
                        dp[i].second < dp[i ^ (1 << j)].second - r2[j]) {
                        dp[i] = { dp[i ^ (1 << j)].first, dp[i ^ (1 << j)].second - r2[j] };
                    }

                }
                else {
                    if (dp[i].first > dp[i ^ (1 << j)].first + 1 &&
                        r[dp[i ^ (1 << j)].first] >= r2[j] ||
                        dp[i].first == dp[i ^ (1 << j)].first + 1 &&
                        dp[i].second < r[dp[i ^ (1 << j)].first] - r2[j]) {
                        dp[i] = { dp[i ^ (1 << j)].first + 1, r[dp[i ^ (1 << j)].first] - r2[j] };
                    }
                }
            }
        }
    }
    return dp.back().first;
}

int getMinResoursesGreedy(vector<int> r, vector<int> r2) {
    int res = 0;
    bool f = 0;
    sort(r.begin(), r.end());
    sort(r2.begin(), r2.end());
    int j = 0;
    for (int i = 0;i < r2.size();i++) {
        if (r[j] >= r2[i]) {
            r[j] -= r2[i];
            res += r2[i];
            f = 1;
        }
        else {
            if (f)
                res += r[j];
            j++;
            i--;
            f = 0;
        }
    }
    if (f)
        res += r[j];
    return res;
}

int getMinCostGreedy(const vector<int>& r, const vector<int>& c, vector<int> r2) {
    vector<pair<int, int>> rc(r.size());
    for (int i = 0;i < r.size();i++) {
        rc[i] = { r[i], c[i] };
    }
    sort(begin(rc), end(rc), [](pair<int, int> l, pair<int, int> r) {return l.second < r.second;});
    sort(begin(r2), end(r2));
    bool f = 0;
    int j = 0, res = 0;
    for (int i = 0;i < r2.size();i++) {
        if (rc[j].first >= r2[i]) {
            rc[j].first -= r2[i];
            f = 1;
        }
        else {
            if (f)
                res += rc[j].second;
            j++;
            i--;
            f = 0;
        }
    }
    if (f)
        res += rc[j].second;
    return res;
}

int main() {
    int p, v;
    cin >> p;
    vector<int> r(p), c(p);
    for (int& x : r)
        cin >> x;
    for (int& x : c)
        cin >> x;
    sort(rbegin(r), rend(r));
    cin >> v;
    vector<int> r2(v);
    for (int& x : r2)
        cin >> x;
    cout << getMinComps(r, r2) << endl << getMinResoursesGreedy(r, r2) << endl << getMinCostGreedy(r, c, r2);
    return 0;
}