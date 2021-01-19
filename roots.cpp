#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

double val(const vector<double>& c, double x){
    double ret = 0;
    double xn = 1;
    for(int i=0;i<c.size();i++){
        ret += (c[i]*xn);
        xn *= x;
    }
    return ret;
}

vector<double> differentiate(const vector<double>& c){
    vector<double> d(c.size()-1);
    for(int i=c.size()-1;i>0;i--){
        d[i-1] = c[i] * i;
    }
    return d;
}

double find(const vector<double>& c, double lo, double hi){
    if(val(c, lo)>0){
        swap(lo, hi);
    }
    for(int i=0;i<100;i++){
        double mid = (lo+hi)/2;
        if(val(c, mid)>0){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}

vector<double> solve(const vector<double>& c){
    vector<double> s;
    if(c.size()==2){
        s.push_back(-c[0]/c[1]);
        return s;
    }
    vector<double> dc = differentiate(c);
    vector<double> ds = solve(dc);
    ds.insert(ds.begin(), -20);
    ds.insert(ds.end(), 20);
    for(int i=0;i<ds.size()-1;i++){
        double lo, hi;
        lo = ds[i]; hi = ds[i+1];
        double vl = val(c, lo), vh = val(c, hi);
        if(vl*vh>0) continue;
        double ans = find(c, lo, hi);
        s.push_back(ans);
    }
    return s;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(12);
    int t;
    cin >> t;
    while(t>0){
        int n;
        cin >> n;
        vector<double> c(n+1);
        for(int i=n;i>=0;i--){
            cin >> c[i];
        }
        vector<double> s = solve(c);
        for(int i=0;i<s.size();i++){
            cout << s[i] << " ";
        }
        cout << "\n";
        t--;
    }
}


