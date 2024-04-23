#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define MAX_SIZE 10000000000
int n;

ll getId(vector<int> &a) {
    ll ret = 0;  
    for (int i=0;i<a.size();i++) {
        ret = ret*n + (a[i]-1);
    }
    return ret;
}

vector<int> getP(ll id) {
    ll divisor = 1;
    for (int i=0;i<n-1;i++) divisor *= n;

    vector<int> ret;
    for (int i=0;i<n;i++) {
        ll divided = id/divisor;
        ret.push_back(divided+1);
        id -= divisor*(divided);
        divisor /= n;
    }
    return ret;
}

queue<ll> q;
unordered_map<ll, vector<pair<ll, pair<int, int>>>> g;
unordered_map<ll, bool> visited;
vector<pair<int, int>> ans;

bool dfs(ll u, ll idg) {
    if (u == idg) return true;

    for (auto p : g[u]) {
        ll v = p.first;
        auto op = p.second;
        if (dfs(v, idg)) {
            ans.push_back(op);
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n;
    vector<int> a, b;
    for (int i=0;i<n;i++) {
        int ax;
        cin >> ax;
        a.push_back(ax);
        b.push_back(i+1);
    }

    if (n<4 || n>10 || n%2!=0) {
        cerr << "input error: n should be [4, 10] and odd!" << endl;
        return 0;
    }

    ll ids = getId(a);
    q.push(ids);
    visited[ids] = true;

    // construct graph
    while (!q.empty()) {
        auto id = q.front();
        q.pop();

        for (int i=0;i+3<=(n-1);i+=2) {
            vector<int> curState = getP(id);
            for (int j=1;j<2;j++) {
                // calc rotated id
                int tmp = curState[i];
                curState[i] = curState[i+1];
                curState[i+1] = curState[i+3];
                curState[i+3] = curState[i+2];
                curState[i+2] = tmp;

                ll swappedId = getId(curState);
                if (visited.find(swappedId) == visited.end()) {
                    if (g.find(id) == g.end()) g.insert(make_pair(id, vector<pair<ll, pair<int, int>>>()));
                    g[id].push_back(make_pair(swappedId, make_pair(i/2 + 1, j)));
                    q.push(swappedId);
                    visited[swappedId] = true;
                } else continue;
            }
        }
    }

    bool flag = dfs(getId(a), getId(b));
    if (flag) {
        cout << "possible!" << endl;
        reverse(ans.begin(), ans.end());

        int index = 0;
        for (;index<ans.size();index++) {
            int cnt = 1;
            for (;index+1<ans.size() && ans[index+1]==ans[index];index++) cnt++;
            cout << "push button" << ans[index].first << " " << cnt << " times" << endl;
        }
    } else {
        cout << "impossible!" << endl;
    }

    return 0;
}