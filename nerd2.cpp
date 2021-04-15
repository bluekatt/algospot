#include <bits/stdc++.h>

using namespace std;

map<int, int> coord;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n;
        cin >> n;
        coord.clear();
        int p, q;
        int ret = 0;
        for(int i=0;i<n;i++){
            cin >> p >> q;
            auto it = coord.lower_bound(p);
            if(it==coord.end() || it->second<q){
                if(it==coord.begin()) {
                    coord[p] = q;
                    ret += coord.size();
                    continue;
                }
                it--;
                while(true){
                    if(it->second>q) break;
                    if(it==coord.begin()) {
                        coord.erase(it);
                        break;
                    } else {
                        auto jt = it;
                        jt--;
                        coord.erase(it);
                        it = jt;
                    }
                }
                coord[p] = q;
            }
            ret += coord.size();
        }
        cout << ret << "\n";
        t--;
    }
}
