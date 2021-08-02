#include <bits/stdc++.h>

using namespace std;

int switchBar(int state, int disc, int bar) {
    int mask = ~(3<<(2*disc));
    int newState = state & mask;
    int newDisc = bar << (2*disc);
    newState |= newDisc;
    return newState;
}

int sgn(int x) { if(x==0) return 0; return x > 0 ? 1 : -1; }

int incr(int x) { if(x>0) return x+1; return x-1; }

int bidirectional(int discs, int begin, int end) {
    queue<int> q;
    map<int, int> c;
    c[begin] = 1;
    c[end] = -1;
    q.push(begin);
    q.push(end);
    while(!q.empty()) {
        int here = q.front();
        q.pop();
        int tops[4] = { 0, 0, 0, 0 };
        for(int i=1;i<=discs;i++) {
            int bar = (here >> (i*2)) & 3;
            if(tops[bar]==0) tops[bar] = i;
        }
        for(int i=0;i<4;i++) {
            if(tops[i]==0) continue;
            for(int j=0;j<4;j++) {
                if(tops[i]<tops[j] || tops[j]==0) {
                    int there = switchBar(here, tops[i], j);
                    if(c[there]==0) {
                        c[there] = incr(c[here]);
                        q.push(there);
                    } else if(sgn(c[there]) != sgn(c[here])) {
                        return abs(c[there]) + abs(c[here]) - 1;
                    }
                }
            }
        }
    }
    return -1;
}

void assignBar(int& state, int disc, int bar) {
    int newDisc = bar << (2*disc);

    state |= newDisc;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc=1;tc<=t;tc++) {
        int n;
        cin >> n;
        int begin = 0;
        for(int i=0;i<4;i++) {
            int k;
            cin >> k;
            for(int j=0;j<k;j++) {
                int disc;
                cin >> disc;
                assignBar(begin, disc, i);
            }
        }
        int end = 0;
        for(int i=1;i<=n;i++) {
            assignBar(end, i, 3);
        }
        cout << bidirectional(n, begin, end) << "\n";
    }
}
