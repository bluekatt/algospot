#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > adj[102];

const int M = 999999;
int V;
const int INF = 100000000;

int bellmanFord(int src, int tar, int rev) {
    vector<int> upper(V, INF);
    upper[src] = 0;
    for(int it=0;it<V;it++) {
        for(int here=0;here<V;here++) {
            for(int i=0;i<adj[here].size();i++) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second * rev;
                if(upper[there]>upper[here]+cost) {
                    upper[there] = upper[here] + cost;
                }
            }
        }
    }
    int firstUpperTar = upper[tar];
    int firstUpperSrc = upper[src];
    for(int it=0;it<V;it++) {
        for(int here=0;here<V;here++) {
            for(int i=0;i<adj[here].size();i++) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second * rev;
                if(upper[there]>upper[here]+cost) {
                    upper[there] = upper[here] + cost;
                }
            }
        }
    }
    if(firstUpperTar>upper[tar] || firstUpperSrc>upper[src]) {
        return -INF;
    }
    return upper[tar];
}

bool unreachable(int n) {
    return n > INF-M*2;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int g, w;
        cin >> g >> w;
        V = g;
        for(int i=0;i<g;i++) adj[i].clear();
        for(int i=0;i<w;i++) {
            int a, b, d;
            cin >> a >> b >> d;
            adj[a].push_back(make_pair(b, d));
        }
        int shortest = bellmanFord(0, 1, 1);
        int longest = bellmanFord(0, 1, -1);
        if(unreachable(shortest) || unreachable(longest)) {
            cout << "UNREACHABLE\n";
        } else {
            if(shortest == -INF) {
                cout << "INFINITY";
            } else {
                cout << shortest;
            }
            cout << " ";
            if(longest == -INF) {
                cout << "INFINITY";
            } else {
                cout << -longest;
            }
            cout << "\n";
        }
    }
}
