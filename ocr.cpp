#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

int m;
double B[502];
double T[502][502];
double M[502][502];
string words[502];
map<string, int> w_map;
int sentence[102];
int choice[102][502];
double cache[102][502];

double max_pos(int cur, int prevMatch, int n){
    if(cur==n){
        return 0;
    }
    double& ret = cache[cur][prevMatch];
    if(ret!=1){
        return ret;
    }
    ret = -1e200;
    int& choose = choice[cur][prevMatch];
    for(int i=1;i<=m;i++){
        double cand = T[prevMatch][i] + M[i][sentence[cur]] + max_pos(cur+1, i, n);
        if(ret<cand){
            ret = cand;
            choose = i;
        }
    }
    return ret;
}

string reconstruct(int cur, int prevMatch, int n){
    if(cur==n){
        return "";
    }
    int choose = choice[cur][prevMatch];
    return words[choose] + " " + reconstruct(cur+1, choose, n);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> m >> t;
    for(int i=1;i<=m;i++){
        string w;
        cin >> w;
        words[i] = w;
        w_map.insert(make_pair(w, i));
    }
    for(int i=0;i<=m;i++){
        for(int j=1;j<=m;j++){
            double d;
            cin >> d;
            T[i][j] = log10(d);
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            double d;
            cin >> d;
            M[i][j] = log10(d);
        }
    }
    while(t>0){
        int n;
        cin >> n;
        for(int i=0;i<102;i++){
            for(int j=0;j<502;j++){
                cache[i][j] = 1;
                choice[i][j] = 0;
            }
        }
        for(int i=0;i<n;i++){
            string w;
            cin >> w;
            sentence[i] = w_map[w];
        }
        max_pos(0, 0, n);
        cout << reconstruct(0, 0, n) << "\n";
        t--;
    }
}


