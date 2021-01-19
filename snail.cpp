#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

double cache[1002][1002];

double get_prob(int n, int m){
    if(n<=0){
        return 1;
    }
    if(m<=0){
        return 0;
    }
    double& ret = cache[n][m];
    if(ret!=-1){
        return ret;
    }
    return ret = 0.25 * get_prob(n-1, m-1) + 0.75 * get_prob(n-2, m-1);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n, m;
        cin >> n >> m;
        for(int i=0;i<1002;i++){
            for(int j=0;j<1002;j++){
                cache[i][j] = -1;
            }
        }
        cout.setf(ios::fixed);
        cout.precision(10);
        cout << get_prob(n, m) << "\n";
        t--;
    }
}
