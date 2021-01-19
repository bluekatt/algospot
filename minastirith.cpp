#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

vector<pair<double, double> > ranges;
const double pi = M_PI;
const int INF = 987654321;

int linear_solve(double begin, double end){
    int used = 0;
    int idx = 0;
    while(begin<end){
        double maxCover = begin;
        if(idx>=ranges.size()){
            return INF;
        }
        while(ranges[idx].first<=begin){
            maxCover = max(maxCover, ranges[idx].second);
            idx++;
            if(idx>=ranges.size()){
                break;
            }
        }
        if(maxCover<=begin){
            return INF;
        }
        used++;
        begin = maxCover;
    }
    return used;
}

int solve(){
    int ret = INF;
    for(auto range: ranges){
        if(range.first<=0 || range.second>=2*pi){
            double begin = fmod(range.second+2*pi, 2*pi);
            double end = fmod(range.first+2*pi, 2*pi);
            ret = min(ret, 1+linear_solve(begin, end));
        }
    }
    return ret;
}

void precal(const vector<double>& x, const vector<double>& y, const vector<double>& r){
    for(int i=0;i<x.size();i++){
        double loc = fmod(2*pi+atan2(y[i], x[i]), 2*pi);
        double range = 2*asin(r[i]/16);
        ranges.push_back(make_pair(loc-range, loc+range));
    }
    sort(ranges.begin(), ranges.end());
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n;
        cin >> n;
        vector<double> coord_x(n);
        vector<double> coord_y(n);
        vector<double> radius(n);
        for(int i=0;i<n;i++){
            cin >> coord_y[i] >> coord_x[i] >> radius[i];
        }
        ranges.clear();
        precal(coord_x, coord_y, radius);
        int s = solve();
        if(s>=INF){
            cout << "IMPOSSIBLE\n";
        } else {
            cout << s << "\n";
        }
        t--;
    }
}


