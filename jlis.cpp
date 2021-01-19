#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <climits>

using namespace std;

int n, m;
int seq[102];
int seq2[102];
int cache[102][102];

int jlis(int s1, int s2){
    int& ret = cache[s1+1][s2+1];
    if(ret!=-1){
        return ret;
    }
    ret = 2;
    long long a = (s1==-1) ? LLONG_MIN : seq[s1];
    long long b = (s2==-1) ? LLONG_MIN : seq2[s2];
    long long cur = max(a, b);
    for(int i=s1+1;i<n;i++){
        if(cur<seq[i]){
            ret = max(ret, jlis(i, s2)+1);
        }
    }
    for(int i=s2+1;i<m;i++){
        if(cur<seq2[i]){
            ret = max(ret, jlis(s1, i)+1);
        }
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> m;
        for(int i=0;i<n;i++){
            cin >> seq[i];
        }
        for(int i=0;i<m;i++){
            cin >> seq2[i];
        }
        memset(cache, -1, sizeof(cache));
        cout << jlis(-1,-1)-2 << "\n";
        t--;
    }
}

