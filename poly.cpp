#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

const int M = 10000000;
int cache[102][102];

int poly(int n, int line){
    if(n==0){
        return 0;
    }
    int& ret = cache[n][line];
    if(ret!=-1){
        return ret;
    }
    if(n==line){
        return ret = 1;
    }
    ret = 0;
    for(int i=1;i<=n-line;i++){
        ret += (line+i-1) * poly(n-line, i);
        ret %= M;
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n;
        cin >> n;
        memset(cache, -1, sizeof(cache));
        int ans = 0;
        for(int i=1;i<=n;i++){
            ans += poly(n, i);
            ans %= M;
        }
        cout << ans << "\n";
        t--;
    }
}


