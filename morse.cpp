#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

const int MAX = 1000000000 + 10;
int binomial[202][202];

int bino(int n, int m){
    int& ret = binomial[n][m];
    if(ret!=-1){
        return ret;
    }
    if(m==0||n==m){
        return ret = 1;
    } else if(m==1) {
        return ret = n;
    }
    return ret = min(MAX, bino(n-1, m-1) + bino(n-1, m));
}

string get_morse(int n, int m, int k){
    if(n==0){
        return string(m, 'o');
    }
    int b = bino(n+m-1, m);
    if(b>=k){
        return '-' + get_morse(n-1, m, k);
    } else {
        return 'o' + get_morse(n, m-1, k-b);
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    memset(binomial, -1, sizeof(binomial));
    int t;
    cin >> t;
    while(t>0){
        int n, m, k;
        cin >> n >> m >> k;
        cout << get_morse(n, m, k) << "\n";
        t--;
    }
}


