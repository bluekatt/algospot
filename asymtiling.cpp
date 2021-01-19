#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

const int M = 1000000007;
int asym_cache[102];
int cache[102];

int tiling(int n);

int asym_tiling(int n){
    int& ret = asym_cache[n];
    if(ret!=-1){
        return ret;
    }
    if(n%2==1){
        int ans = (tiling(n) - tiling((n-1)/2))%M;
        while(ans<0){
            ans = ans + M;
        }
        return ret = ans;
    } else {
        int ans = (tiling(n) - tiling((n-2)/2) - tiling(n/2))%M;
        while(ans<0){
            ans = ans + M;
        }
        return ret = ans;
    }
}

int tiling(int n){
    int& ret = cache[n];
    if(ret!=-1){
        return cache[n];
    }
    return ret = (tiling(n-1) + tiling(n-2))%M;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    memset(cache, -1, sizeof(cache));
    memset(asym_cache, -1, sizeof(cache));
    cache[1] = 1;
    asym_cache[1] = 0;
    cache[2] = 2;
    asym_cache[2] = 0;
    while(t>0){
        int n;
        cin >> n;
        cout << asym_tiling(n) << "\n";
        t--;
    }
}


