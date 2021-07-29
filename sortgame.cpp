#include <bits/stdc++.h>

using namespace std;

map<vector<int>, int> toSort;

void preCalc(int n) {
    vector<int> perm(n);
    for(int i=0;i<n;i++) perm[i] = i;
    queue<vector<int> > q;
    q.push(perm);
    toSort[perm] = 0;
    while(!q.empty()) {
        vector<int> here = q.front();
        q.pop();
        int cost = toSort[here];
        for(int i=0;i<n;i++) {
            for(int j=i+2;j<=n;j++) {
                reverse(here.begin()+i, here.begin()+j);
                if(toSort.count(here)==0) {
                    toSort[here] = cost+1;
                    q.push(here);
                }
                reverse(here.begin()+i, here.begin()+j);
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    for(int i=1;i<=8;i++) preCalc(i);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i=0;i<n;i++) {
            cin >> a[i];
        }
        vector<int> sorted = a;
        sort(sorted.begin(), sorted.end());
        map<int, int> sortMap;
        for(int i=0;i<n;i++) sortMap[sorted[i]] = i;
        vector<int> mapped(n);
        for(int i=0;i<n;i++) {
            mapped[i] = sortMap[a[i]];
        }
        cout << toSort[mapped] << "\n";
    }
}
