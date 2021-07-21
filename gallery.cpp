#include <bits/stdc++.h>

using namespace std;

int g, h;
vector<int> adj[1002];
const int INSTALLED = 0;
const int WATCHED = 1;
const int UNWATCHED = 2;
int installed;

int dfs(int here, vector<bool>& visited) {
    visited[here] = true;
    int childrenStatus[3] = { 0, 0, 0 };
    for(int i=0;i<adj[here].size();i++) {
        int there = adj[here][i];
        if(!visited[there]) {
            childrenStatus[dfs(there, visited)]++;
        }
    }
    if(childrenStatus[UNWATCHED]) {
        installed++;
        return INSTALLED;
    }
    if(childrenStatus[INSTALLED]) {
        return WATCHED;
    }
    return UNWATCHED;
}

void dfsAll() {
    vector<bool> visited(g, false);
    for(int i=0;i<g;i++) {
        if(!visited[i]) {
            if(dfs(i, visited)==UNWATCHED) installed++;
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        for(int i=0;i<1000;i++) {
            adj[i].clear();
        }
        installed = 0;
        cin >> g >> h;
        for(int i=0;i<h;i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        dfsAll();
        cout << installed << "\n";
    }
}
