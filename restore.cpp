#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

int k;
string words[16];
int ols[16][16] = {0};
int cache[16][1<<16];
int m_cache[16][1<<16];

struct Comp {
    bool operator()(string a, string b){
        return a.size() > b.size();
    }
};

void cal_ols(){
    for(int i=1;i<=k;i++){
        for(int j=1;j<=k;j++){
            ols[i][j] = 0;
            int i_size = words[i].size();
            int j_size = words[j].size();
            int length = min(i_size, j_size);
            for (int l=0;l<length;l++) {
                string i_sub = words[i].substr(l + i_size - length, length - l);
                if (i_sub == words[j].substr(0, length - l)) {
                    ols[i][j] = length - l;
                    break;
                }
            }
        }
    }
}

void rm_overlap(){
    int rmd = 0;
    sort(words+1, words+k+1, Comp());
    for(int i=2;i<=k;i++){
        for(int j=1;j<i;j++){
            int i_sz = words[i].size();
            int j_sz = words[j].size();
            if(i_sz==0||j_sz==0){
                continue;
            }
            for(int l=0;l<j_sz-i_sz+1;l++){
                string a = words[j].substr(l, i_sz);
                if(a==words[i]){
                    words[i] = "";
                    rmd++;
                    break;
                }
            }
        }
    }
    sort(words+1, words+k+1, Comp());
    k-=rmd;
}

int overlap(int cur, int visited){
    if(visited==(1<<(k+1))-1){
        return 0;
    }
    int& ret = cache[cur][visited];
    if(ret!=-1){
        return ret;
    }
    ret = -1;
    for(int i=1;i<=k;i++) {
        if(visited&(1<<i)) {
            continue;
        }
        int ol = 0;
        if(cur != 0) {
            ol = ols[cur][i];
        }
        int cand = ol+overlap(i, visited|(1<<i));
        if(cand > ret) {
            ret = cand;
            m_cache[cur][visited] = i;
        }
    }
    return ret;
}

string reconstruct(int cur, int visited){
    if(visited==(1<<(k+1))-1){
        return words[cur];
    }
    int next = m_cache[cur][visited];
    string prefix = "";
    if(cur!=0){
        int len = words[cur].size()-ols[cur][next];
        prefix = words[cur].substr(0, len);
    }
    return prefix + reconstruct(next, visited|(1<<next));
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> k;
        int m = 0;
        for(int i=1;i<=k;i++){
            cin >> words[i];
        }
        rm_overlap();
        cal_ols();
        for(int i=1;i<=k;i++){
            m += words[i].size();
        }
        memset(cache, -1, sizeof(cache));
        overlap(0, 1);
        cout << reconstruct(0, 1) << "\n";
        t--;
    }
}


