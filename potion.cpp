#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b, a%b);
}

vector<int> require(const vector<int>& r, const vector<int>& p){
    int n = r.size();
    int g = r[0];
    for(int i=1;i<n;i++){
        g = gcd(g, r[i]);
    }
    vector<int> u(n);
    for(int i=0;i<n;i++){
        u[i] = r[i] / g;
    }
    int ratio = 0;
    for(int i=0;i<n;i++){
        ratio = max(ratio, (p[i]-r[i]+u[i]-1)/u[i]);
    }
    vector<int> ret(n);
    for(int i=0;i<n;i++){
        ret[i] = r[i] + u[i]*ratio - p[i];
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
        vector<int> r(n), p(n);
        for(int i=0;i<n;i++){
            cin >> r[i];
        }
        for(int i=0;i<n;i++){
            cin >> p[i];
        }
        vector<int> req = require(r, p);
        for(int i=0;i<n;i++){
            cout << req[i] << " ";
        }
        cout << "\n";
        t--;
    }
}


