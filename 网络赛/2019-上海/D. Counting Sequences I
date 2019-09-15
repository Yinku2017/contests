#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1000000007;

map<vector<short>, short> m;
vector<short> vec;

void calc(int num1) {
    vector<short> tmp;
    if(num1)
        tmp.push_back(num1);
    int n = vec.size();
    int cur = 1;
    for(int i = 1; i < n; ++i) {
        if(vec[i] != vec[i - 1]) {
            tmp.push_back(cur);
            cur = 1;
        } else
            ++cur;
    }
    tmp.push_back(cur);
    sort(tmp.begin(), tmp.end());
    m[tmp]++;
}

void dfs(int last, int cur, ll pro, int sum) {
    for(int i = last; i <= 3000; ++i) {
        int tcur = cur + 1;
        ll tpro = pro * i;
        int tsum = sum + i;
        if(tpro - tsum + tcur > 3000)
            break;

        vec.push_back(i);
        calc(tpro - tsum);
        if(tpro * i - (tsum + i) + (tcur + 1) <= 3000)
            dfs(i, tcur, tpro, tsum);
        vec.pop_back();
    }
}

ll qpow(ll x, int n) {
    ll res = 1;
    while(n) {
        if(n & 1)
            res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}

int ans[3005], prod[3005], invprod[3005];

void Init() {
    dfs(2, 0, 1, 0);
    prod[0] = 1;
    for(int i = 1; i <= 3000; ++i) {
        prod[i] = 1ll * prod[i - 1] * i % MOD;
        invprod[i] = qpow(prod[i], MOD - 2);
    }
    for(auto mi : m) {
        ll sum = 1;
        int len = 0;
        for(auto vi : mi.first) {
            len += vi;
            sum = (sum * invprod[vi]) % MOD;
        }
        sum = (sum * prod[len]) % MOD;
        sum = (sum * mi.second) % MOD;
        ans[len] = (sum + ans[len]) % MOD;
    }
    ans[0] = ans[1] = 0;
}

int main() {
#ifdef Yinku
    freopen("Yinku.in", "r", stdin);
#endif // Yinku
    Init();
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", ans[n]);
    }
}
