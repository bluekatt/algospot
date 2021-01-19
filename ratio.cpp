#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

long long solve(int n, int m){
    long long lo = 0, hi = 2000000001;
    int r = ((long long)m*100)/n;
    while(lo+1<hi){
        long long mid = (lo+hi)/2;
        if((m+mid)*100/(n+mid)>r){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    if(hi>2000000000){
        return -1;
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
        int n, m;
        cin >> n >> m;
        cout << solve(n, m) << "\n";
        t--;
    }
}


