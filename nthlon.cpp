#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > adj[410];

int vertex(int delta) {
    return delta + 200;
}

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
        for(int i=0;i<410;i++) adj[i].clear();
        int m;
        cin >> m;
        vector<int> a(m);
        vector<int> b(m);
        for(int i=0;i<m;i++) {
            cin >> a[i] >> b[i];
        }
        int start = 401;
        for(int i=0;i<m;i++) {
            int delta = a[i] - b[i];
            adj[start].push_back(make_pair(vertex(delta), a[i]));
        }
        for(int delta=-200;delta<=200;delta++) {
            int here = vertex(delta);
            for(int i=0;i<m;i++) {
                int next = delta + a[i] - b[i];
                if(abs(next) > 200) continue;
                adj[here].push_back(make_pair(vertex(next), a[i]));
            }
        }
        vector<int> dist = dijkstra(start, 402);
        int ans = dist[vertex(0)];
        if(ans==INT_MAX) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << ans << "\n";
        }
    }
}
