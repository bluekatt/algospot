#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

#define MAX_N 100

using namespace std;

const int INF = 987654321;

int classes[12];
int semesters[10];
int cache[10][1<<12];
int n, k, m, l;

int bit_cnt(int n) {
    int cnt = 0;
    while(n!=0) {
        if(n&1) {
            cnt++;
        }
        n = n >> 1;
    }
    return cnt;
}

int graduate(int s, int completed){
    if(bit_cnt(completed)>=k) {
        return 0;
    }
    if(s>=m) {
        return INF;
    }
    int& ret = cache[s][completed];
    if(ret!=-1) {
        return ret;
    }
    ret = INF;
    int canTake = (semesters[s] & ~completed);
    for(int i=0;i<n;i++){
        if(canTake&(1<<i)) {
            if((classes[i]|completed)!=completed) {
                canTake &= ~(1<<i);
            }
        }
    }
    for(int c=canTake;c>0;c=((c-1)&canTake)) {
        if(bit_cnt(c)>l) continue;
        ret = min(ret, graduate(s+1, completed | c)+1);
    }
    ret = min(ret, graduate(s+1, completed));
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        memset(classes, 0, sizeof(classes));
        memset(semesters, 0, sizeof(semesters));
        memset(cache, -1, sizeof(cache));
        cin >> n >> k >> m >> l;
        for(int i=0;i<n;i++) {
            int r;
            cin >> r;
            for(int j=0;j<r;j++){
                int p;
                cin >> p;
                classes[i] |= (1<<p);
            }
        }
        for(int i=0;i<m;i++) {
            int c;
            cin >> c;
            for(int j=0;j<c;j++){
                int cl;
                cin >> cl;
                semesters[i] |= (1<<cl);
            }
        }
        int ans = graduate(0, 0);
        if(ans<INF){
            cout << ans << "\n";
        } else {
            cout << "IMPOSSIBLE\n";
        }
        t--;
    }
}

