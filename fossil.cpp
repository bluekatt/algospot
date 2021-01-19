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
double minX, maxX;
vector<pair<double, double> > c1;
vector<pair<double, double> > c2;

double gap(double tx){
    double t1 = -1, t2 = -1, b1 = 101, b2 = 101;
    for(int i=0;i<n;i++){
        pair<double, double> p1 = c1[i];
        pair<double, double> p2 = c1[(i+1)%n];
        if(p1.first>p2.first){
            swap(p1, p2);
        }
        if(p1.first>tx||p2.first<tx) continue;
        double ty = p1.second + (p2.second-p1.second)*(tx-p1.first)/(p2.first-p1.first);
        if(ty>t1){
            t1 = ty;
        }
        if(ty<b1){
            b1 = ty;
        }
    }
    for(int i=0;i<m;i++){
        pair<double, double> p1 = c2[i];
        pair<double, double> p2 = c2[(i+1)%m];
        if(p1.first>p2.first){
            swap(p1, p2);
        }
        if(p1.first>tx||p2.first<tx) continue;
        double ty = p1.second + (p2.second-p1.second)*(tx-p1.first)/(p2.first-p1.first);
        if(ty>t2){
            t2 = ty;
        }
        if(ty<b2){
            b2 = ty;
        }
    }
    double ret = min(t1, t2) - max(b1, b2);
    if(ret<0||ret==102) {
        ret = 0;
    }
    return ret;
}

double solve(){
    double lo = minX, hi = maxX;
    for(int i=0;i<100;i++){
        double llh = (2*lo+hi)/3;
        double lhh = (lo+2*hi)/3;
        if(gap(llh)<gap(lhh)){
            lo = llh;
        } else {
            hi = lhh;
        }
    }
    return gap((lo+hi)/2);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> m;
        double x, y;
        c1.clear();
        c2.clear();
        double minX1 = 101, maxX1 = -1;
        for(int i=0;i<n;i++){
            cin >> x >> y;
            c1.push_back(make_pair(x, y));
            if(x>maxX1) maxX1 = x;
            if(x<minX1) minX1 = x;
        }
        double minX2 = 101, maxX2 = -1;
        for(int i=0;i<m;i++){
            cin >> x >> y;
            c2.push_back(make_pair(x, y));
            if(x>maxX2) maxX2 = x;
            if(x<minX2) minX2 = x;
        }
        maxX = min(maxX1, maxX2);
        minX = max(minX1, minX2);
        cout << solve() << "\n";
        t--;
    }
}


