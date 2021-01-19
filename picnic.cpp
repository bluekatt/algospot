#include <iostream>
#include <cstring>

using namespace std;

int friends[12][12] = {0};

int get_pairs(int k, int n, int used[]){
    if(k==n-1){
        int valid = 1;
        for(int i=0;i<n;i++){
            if(!used[i]){
                valid = 0;
                break;
            }
        }
        if(valid) {
            return 1;
        } else {
            return 0;
        }
    }
    if(used[k]){
        return get_pairs(k+1, n, used);
    }
    int ret = 0;
    for(int i=k+1;i<n;i++){
        if(friends[k][i]&&!used[i]){
            used[i] = 1;
            used[k] = 1;
            ret += get_pairs(k+1, n, used);
            used[i] = 0;
            used[k] = 0;
        }
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n, m;
        cin >> n >> m;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                friends[i][j] = 0;
            }
        }
        for(int i=0;i<m;i++){
            int f1, f2;
            cin >> f1 >> f2;
            friends[f1][f2] = 1;
            friends[f2][f1] = 1;
        }
        int used[12] = {0};
        cout << get_pairs(0, n, used) << "\n";
        t--;
    }
}

