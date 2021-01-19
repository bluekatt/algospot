#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

string w, s;
int w_size, s_size;
int cache[102][102];

bool conform(int wn, int sn){
    int& ret = cache[wn][sn];
    if(ret!=-1){
        return ret;
    }
    if(wn<w_size&&sn<s_size&&(w[wn]=='?'||w[wn]==s[sn])){
        return ret = conform(wn+1, sn+1);
    }
    if(wn==w_size){
        return ret = (sn==s_size);
    }
    if(w[wn]=='*'){
        return conform(wn+1, sn) || (sn<s_size && conform(wn, sn+1));
    }
    return ret = false;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n;
        cin >> w;
        w_size = w.size();
        cin >> n;
        vector<string> v;
        for(int i=0;i<n;i++){
            cin >> s;
            s_size = s.size();
            memset(cache, -1, sizeof(cache));
            if(conform(0, 0)){
                v.push_back(s);
            }
        }
        sort(v.begin(), v.end());
        for(auto a: v){
            cout << a << "\n";
        }
        t--;
    }
}

