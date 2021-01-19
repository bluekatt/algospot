#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int n, k;
int r[1002], c[1002];

bool decision(double rank){
    vector<double> v(n);
    for(int i=0;i<n;i++){
        v[i] = rank*c[i] - r[i];
    }
    sort(v.begin(), v.end(), greater<double>());
    double c_r = 0;
    for(int i=0;i<k;i++){
        c_r += v[i];
    }
    return c_r >= 0;
}

double optimize(){
    double lo = 0, hi = 1.1;
    for(int i=0;i<100;i++){
        double mid = (lo+hi)/2;
        if(decision(mid)){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> k;
        for(int i=0;i<n;i++){
            cin >> r[i] >> c[i];
        }
        cout << optimize() << "\n";
        t--;
    }
}


