#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > adj[1002];

vector<int> dijkstra(int src, int n) {
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<double, int> > pq;
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while(!pq.empty()) {
        int here = pq.top().second;
        double cost = -pq.top().first;
        pq.pop();
        if(dist[here]<cost) continue;
        for(int i=0;i<adj[here].size();i++) {
            int there = adj[here][i].first;
            double newCost = adj[here][i].second+cost;
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
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int v, e, n, m;
        cin >> v >> e >> n >> m;
        vector<int> fire(n);
        vector<int> statn(m);
        for(int i=0;i<v+1;i++) adj[i].clear();
        for(int i=0;i<e;i++) {
            int a, b, time;
            cin >> a >> b >> time;
            adj[a].push_back(make_pair(b, time));
            adj[b].push_back(make_pair(a, time));
        }
        for(int i=0;i<n;i++) {
            cin >> fire[i];
        }
        for(int i=0;i<m;i++) {
            cin >> statn[i];
        }
        for(int i=0;i<m;i++) {
            adj[0].push_back(make_pair(statn[i], 0));
            adj[statn[i]].push_back(make_pair(0, 0));
        }
        vector<int> dist = dijkstra(0, v+1);
        int sum = 0;
        for(int i=0;i<n;i++) {
            sum += dist[fire[i]];
        }
        cout << sum << "\n";
    }
}
