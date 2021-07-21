#include <bits/stdc++.h>

using namespace std;

vector<pair<int, string> > adj[26];
int indegrees[26], outdegrees[26];

void getEulerCircuit(int here, const string& hereStr, vector<string>& circuit) {
    while(!adj[here].empty()) {
        pair<int, string> there = adj[here].back();
        adj[here].pop_back();
        getEulerCircuit(there.first, there.second, circuit);
    }
    circuit.push_back(hereStr);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        for(int i=0;i<26;i++) {
            indegrees[i] = 0;
            outdegrees[i] = 0;
            adj[i].clear();
        }
        int estart = 0;
        int n;
        cin >> n;
        for(int i=0;i<n;i++) {
            string str;
            cin >> str;
            int start = str.at(0)-'a';
            int end = str.at(str.size()-1)-'a';
            pair<int, string> newNode = make_pair(end, str);
            adj[start].push_back(newNode);
            outdegrees[start]++; indegrees[end]++;
            if(i==0) estart = start;
        }
        int plus = 0, minus = 0;
        for(int i=0;i<26;i++) {
            int delta = outdegrees[i] - indegrees[i];
            if(delta==1) {
                plus++;
                estart = i;
            }
            if(delta==-1) minus++;
            if(delta>1 || delta<-1) plus = 2;
        }
        if(!(plus==1 && minus==1) && !(plus==0 && minus==0)) {
            cout << "IMPOSSIBLE\n";
            continue;
        } else {
            vector<string> circuit;
            getEulerCircuit(estart, "", circuit);
            for(auto it=circuit.rbegin()+1;it!=circuit.rend();it++) {
                cout << *it << " ";
            }
            cout << "\n";
        }
    }
}
