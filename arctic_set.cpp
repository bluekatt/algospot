#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int n;
vector<pair<double, double> > coord;
double dist[102][102];
int parent[102];

void clear_set(){
    for(int i=0;i<n;i++){
        parent[i] = i;
    }
}

int find(int a){
    if(parent[a]==a){
        return a;
    }
    return find(parent[a]);
}

int merge(int a, int b){
    int r_a = find(a);
    int r_b = find(b);
    if(r_a!=r_b){
        parent[r_b] = r_a;
    }
    return r_a;
}

bool decision(double r){
    clear_set();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(dist[i][j]<r*r){
                merge(i, j);
            }
        }
    }
    int root = find(0);
    for(int i=1;i<n;i++){
        if(root!=find(i)){
            return false;
        }
    }
    return true;
}

double optimize(){
    double lo = 0, hi = 2000;
    for(int i=0;i<100;i++){
        double mid = (lo+hi)/2;
        if(decision(mid)){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    return lo;
}

void cal_dist(){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double d = (coord[i].first - coord[j].first)*(coord[i].first - coord[j].first);
            d += (coord[i].second - coord[j].second)*(coord[i].second - coord[j].second);
            dist[i][j] = d;
            dist[j][i] = d;
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(2);
    int t;
    cin >> t;
    while(t>0){
        cin >> n;
        coord.clear();
        for(int i=0;i<n;i++){
            double x, y;
            cin >> x >> y;
            coord.push_back(make_pair(x, y));
        }
        cal_dist();
        cout << optimize() << "\n";
        t--;
    }
}


