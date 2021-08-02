#include <bits/stdc++.h>

using namespace std;

vector<pair<int, double> > adj[10002];

vector<double> dijkstra(int src, int n) {
    vector<double> dist(n, DBL_MAX);
    priority_queue<pair<double, int> > pq;
    pq.push(make_pair(-1, src));
    dist[src] = 1;
    while(!pq.empty()) {
        int here = pq.top().second;
        double cost = -pq.top().first;
        pq.pop();
        if(dist[here]<cost) continue;
        for(int i=0;i<adj[here].size();i++) {
            int there = adj[here][i].first;
            double newCost = adj[here][i].second*cost;
            if(newCost<dist[there]) {
                dist[there] = newCost;
                pq.push(make_pair(-newCost, there));
            }
        }
    }
    return dist;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int n, m;
        cin >> n >> m;
        for(int i=0;i<n;i++) {
            adj[i].clear();
        }
        for(int i=0;i<m;i++) {
            int a, b;
            double c;
            cin >> a >> b >> c;
            adj[a].push_back(make_pair(b, c));
            adj[b].push_back(make_pair(a, c));
        }
        vector<double> dist = dijkstra(0, n);
        cout << dist[n-1] << "\n";
    }
}
