#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

bool decision(double n, int m, double p, double c){
    double left = n;
    for(int i=0;i<m;i++){
        left *= (1+p/1200);
        left -= c;
    }
    return left <= 0;
}

double solve(double n, int m, double p){
    double lo = 0, hi = n*(1+p/1200);
    for(int i=0;i<100;i++){
        double mid = (lo+hi)/2;
        if(decision(n, m, p, mid)){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return hi;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);
    int t;
    cin >> t;
    while(t>0){
        double n, p;
        int m;
        cin >> n >> m >> p;
        cout << solve(n, m, p) << "\n";
        t--;
    }
}


