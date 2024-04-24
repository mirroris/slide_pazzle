#include <bits/stdc++.h>

using namespace std;
using ll = long long;

queue<string> q;
unordered_map<string, vector<pair<string, int>>> g;
unordered_map<string, bool> visited;
vector<int> ans;

bool dfs(string u, string ide) {
    if (u == ide) return true;

    for (auto p : g[u]) {
        string v = p.first;
        auto op = p.second;
        if (dfs(v, ide)) {
            ans.push_back(op);
            return true;
        }
    }
    return false;
}

int main() {
    cout << "input the number of tiles!" << endl;
    int n;
    cin >> n;
    if (n<4 || n>16 || n%2!=0) {
        cerr << "input error: n should be [4, 16] and odd!" << endl;
        return 0;
    }
 
    cout << "input the permutation to align" << endl;
    string a, e;
    for (int i=0;i<n;i++) {
        int ax;
        cin >> ax;
        ax--;
        a.push_back('0'+ax);
        e.push_back('0'+i);
    }

    q.push(a);
    visited[a] = true;

    ll searchOrder = 0;
    // construct graph
    while (!q.empty()) {
        searchOrder++;
        auto p = q.front();
        q.pop();
        if (p == e) cout << "found!" << endl;

        for (int i=0;i+3<=(n-1);i+=2) {
            string swapped = p;
            // calc rotated id
            int tmp = swapped[i];
            swapped[i] = swapped[i+1];
            swapped[i+1] = swapped[i+3];
            swapped[i+3] = swapped[i+2];
            swapped[i+2] = tmp;

            if (visited.find(swapped) == visited.end()) {
                if (g.find(p) == g.end()) g.insert(make_pair(p, vector<pair<string, int>>()));
                g[p].push_back(make_pair(swapped, i/2 + 1));
                q.push(swapped);
                visited[swapped] = true;
            } else continue;
        }
    }

    cout << "you found  = " << visited.size() << " permutations that can reach the goal!!" << endl;

    if (dfs(a, e)) {
        cout << "possible!" << endl;
        reverse(ans.begin(), ans.end());

        int index = 0;
        for (;index<ans.size();index++) {
            int cnt = 1;
            for (;index+1<ans.size() && ans[index+1]==ans[index];index++) cnt++;
            cout << "push button" << ans[index] << " " << cnt << " times" << endl;
        }
    } else {
        cout << "impossible!" << endl;
    }

    return 0;
}
