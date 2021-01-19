#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

int n, w;
string name[102];
int volume[102];
int need[102];
int cache[102][1002];
vector<string> choices;

int pack(int item, int space) {
    if(space<=0){
        return 0;
    }
    if(item==n){
        return 0;
    }
    int& ret = cache[item][space];
    if(ret!=-1){
        return ret;
    }
    int put = (space-volume[item] >= 0 ? need[item] + pack(item+1, space-volume[item]) : 0);
    int n_put = pack(item+1, space);
    return ret = max(put, n_put);
}

void reconstruct(int item, int space){
    if(item==n){
        return;
    }
    if(pack(item, space)==pack(item+1,space)){
        reconstruct(item+1, space);
    } else {
        choices.push_back(name[item]);
        reconstruct(item+1, space-volume[item]);
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> w;
        for(int i=0;i<n;i++){
            cin >> name[i] >> volume[i] >> need[i];
        }
        choices.clear();
        memset(cache, -1, sizeof(cache));
        cout << pack(0, w) << " ";
        reconstruct(0, w);
        cout << choices.size() << "\n";
        for(auto a: choices){
            cout << a << "\n";
        }
        t--;
    }
}


