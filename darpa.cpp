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

bool decision(double gap){
    int closest = 0;
    double gap_so_far = 0;
    int installed = 1;
    for(int i=1;i<m;i++){
        gap_so_far = (locations[i]-locations[closest]);
        if(gap_so_far>=gap){
            installed++;
            closest = i;
            gap_so_far = 0;
        }
    }
    return installed>=n;
}

double optimize(){
    double lo = 0, hi = 241;
    for(int i=0;i<100;i++){
        double mid = (lo+hi)/2.0;
        if(decision(mid)){
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
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
        cout << optimize() << "\n";
        t--;
    }
}


