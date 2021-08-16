#include <bits/stdc++.h>

using namespace std;

int V;
int adj[500][500], W[500][500];
int delay[500];
const int INF = 987654321;

void floyd() {
    vector<pair<int, int> > order;
    for(int i=0;i<V;i++) {
        order.push_back(make_pair(delay[i], i));
    }
    sort(order.begin(), order.end());
    for(int k=0;k<V;k++) {
        int w = order[k].second;
        for(int i=0;i<V;i++) {
            for(int j=0;j<V;j++) {
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                W[i][j] = min(W[i][j], adj[i][j]+delay[w]);
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for(int tc=1;tc<=t;tc++) {
        int e;
        cin >> V >> e;
        for(int i=0;i<V;i++) {
            int d;
            cin >> d;
            delay[i] = d;
        }
        for(int i=0;i<V;i++) {
            for(int j=0;j<V;j++) {
                adj[i][j] = INF;
            }
        }
        for(int i=0;i<e;i++) {
            int a, b, c;
            cin >> a >> b >> c;
            a--; b--;
            adj[a][b] = adj[b][a] = c;
        }
        for(int i=0;i<V;i++) {
            for(int j=0;j<V;j++) {
                if(i==j) W[i][j] = 0;
                else W[i][j] = adj[i][j];
            }
        }
        floyd();
        int T;
        cin >> T;
        for(int i=0;i<T;i++) {
            int s, e;
            cin >> s >> e;
            cout << W[s-1][e-1] << "\n";
        }
//    }
}
