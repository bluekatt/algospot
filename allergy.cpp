#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

const int INF = 987654321;
int n, m;
map<string, int> name;
int best;
int edible_count[50];
long long eaters[50];

void solve(int ate, int chosen){
    if(best<=chosen){
        return;
    }
    int max_edible = INF;
    int tar = -1;
    for(int i=0;i<n;i++){
        if(!(ate&(1<<i))&&max_edible>edible_count[i]){
            tar = i;
        }
    }
    if(tar==-1){
        best = chosen;
        return;
    }
    for(int i=0;i<m;i++){
        if(eaters[i]&(1<<tar)){
            solve(ate|eaters[i], chosen+1);
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> m;
        memset(edible_count, 0, sizeof(edible_count));
        memset(eaters, 0, sizeof(eaters));
        for(int i=0;i<n;i++){
            string s;
            cin >> s;
            name[s] = i;
        }
        for(int i=0;i<m;i++){
            int eater;
            cin >> eater;
            for(int j=0;j<eater;j++){
                string s;
                cin >> s;
                eaters[i] = eaters[i] | (1<<name[s]);
                edible_count[name[s]]++;
            }
        }
        best = INF;
        solve(0, 0);
        cout << best << "\n";
        t--;
    }
}


