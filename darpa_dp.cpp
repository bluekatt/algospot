#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int n, m;
double locations[202];
double cache[202][102];

double solve(int idx, int left){
    if(left<=1){
        return 987654321;
    }
    double& ret = cache[idx][left];
    if(ret!=-1){
        return ret;
    }
    ret = 0;
    for(int i=idx+1;i<m-left+2;i++){
        double cand = min(locations[i]-locations[idx], solve(i, left-1));
        if(cand>ret){
            ret = cand;
        }
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(2);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> m;
        for(int i=0;i<m;i++){
            cin >> locations[i];
        }
        for(int i=0;i<202;i++){
            for(int j=0;j<102;j++){
                cache[i][j] = -1;
            }
        }
        cout << solve(0, n) << "\n";
        t--;
    }
}


