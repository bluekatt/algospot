#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

const int M = 1000000007;
int cache[102];

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
    cache[1] = 1;
    cache[2] = 2;
    while(t>0){
        int n;
        cin >> n;
        cout << tiling(n) << "\n";
        t--;
    }
}

