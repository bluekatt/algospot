#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > adj;

void makeGraph(string d, int n, int m) {
    sort(d.begin(), d.end());
    adj.clear(); adj.resize(n*2);
    for(int i=0;i<adj.size();i++) {
        adj[i] = vector<int>(10, -1);
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<d.size();j++) {
            int child = d[j]-'0';
            int next = (i*10+child)%n;
            if(i*10+child>=n) {
                adj[i][child] = next+n;
            } else {
                adj[i][child] = next;
            }
            adj[i+n][child] = next+n;
        }
    }
}

void bfs(int start, vector<int>& choice, vector<int>& parent) {
    choice = parent = vector<int>(adj.size(), -1);

    queue<int> q;
    parent[start] = start;
    q.push(start);

    while(!q.empty()) {
        int here = q.front();
        q.pop();
        for(int i=0;i<10;i++) {
            int there = adj[here][i];
            if(there==-1) continue;
            if(parent[there]==-1) {
                q.push(there);
                parent[there] = here;
                choice[there] = i;
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int n, m;
        string d;
        cin >> d >> n >> m;

        makeGraph(d, n, m);

        vector<int> choice;
        vector<int> parent;
        bfs(0, choice, parent);

        if(parent[m+n]==-1) {
            cout << "IMPOSSIBLE\n";
        } else {
            stack<int> st;
            int here = m+n;
            while(parent[here]!=here) {
                st.push(choice[here]);
                here = parent[here];
            }
            while(!st.empty()) {
                cout << st.top();
                st.pop();
            }
            cout << "\n";
        }
    }
}
