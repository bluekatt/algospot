#include <bits/stdc++.h>

using namespace std;

struct UnionFind {
    vector<int> rank, size, parent, contrary;

    UnionFind(int n) :
            rank(n, 1),
            size(n, 1),
            parent(n, 1),
            contrary(n, -1) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) return parent[u];
        return parent[u] = find(parent[u]);
    }

    int merge(int u, int v) {
        if(u==-1||v==-1) return max(u, v);
        int pu = find(u), pv = find(v);
        if (pu==pv) return pv;
        if(rank[pu]>rank[pv]) swap(pu, pv);
        parent[pu] = pv;
        if(rank[pu] == rank[pv]) rank[pv]++;
        size[pv] += size[pu];
        return pv;
    }

    bool bond(int u, int v) {
        int pu = find(u), pv = find(v);
        if(contrary[pu] == pv || contrary[pv] == pu) return false;
        int newRoot = merge(pu, pv);
        int newContRoot = merge(contrary[pu], contrary[pv]);
        if(newContRoot!=-1) {
            contrary[newRoot] = newContRoot;
            contrary[newContRoot] = newRoot;
        }
        return true;
    }

    bool separate(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu==pv) return false;
        int newRoot = merge(pu, contrary[pv]);
        int newContRoot = merge(pv, contrary[pu]);
        contrary[newRoot] = newContRoot;
        contrary[newContRoot] = newRoot;
        return true;
    }

    int rootSize(int u) {
        if(u==-1) return 0;
        int pu = find(u);
        return size[pu];
    }

    int findContrary(int u) {
        int pu = find(u);
        if(contrary[pu]==-1) return -1;
        return find(contrary[pu]);
    }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int n, m;
        cin >> n >> m;
        UnionFind uf = UnionFind(n);
        int contradiction = 0;
        for(int i=1;i<=m;i++) {
            string type;
            int a, b;
            cin >> type >> a >> b;
            bool result;
            if (type == "ACK") {
                result = uf.bond(a, b);
            } else {
                result = uf.separate(a, b);
            }
            if(!contradiction && !result) contradiction = i;
        }
        if(contradiction) {
            cout << "CONTRADICTION AT " << contradiction << "\n";
            continue;
        }
        int ret = 0;
        vector<bool> visited(n, false);
        for(int i=0;i<n;i++) {
            int root = uf.find(i);
            if(root!=i) continue;
            if(visited[root]) continue;
            int cont = uf.findContrary(root);
            if(cont!=-1) visited[cont] = true;
            visited[root] = true;
            ret += max(uf.rootSize(cont), uf.rootSize(root));
        }
        cout << "MAX PARTY SIZE IS " << ret << "\n";
    }
}
