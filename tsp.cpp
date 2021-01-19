#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

const double MAX = 987654321;
int n;
double dist[22][22];
double cache[22][1100000];

double tsp(int last, int visit){
    if(visit==(1<<n)-1){
        return 0;
    }
    double& ret = cache[last][visit];
    if(ret!=-1){
        return ret;
    }
    ret = MAX;
    for(int i=0;i<n;i++){
        if(last==n||((1<<i)&visit)==0){
            ret = min(ret, dist[last][i] + tsp(i, (visit|(1<<i))));
        }
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);
    int t;
    cin >> t;
    while(t>0){
        cin >> n;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin >> dist[i][j];
            }
        }
        for(int i=0;i<=n;i++){
            dist[n][i] = 0;
            for(int j=0;j<(1<<n);j++){
                cache[i][j] = -1;
            }
        }
        cout << tsp(n, 0) << "\n";
        t--;
    }
}


