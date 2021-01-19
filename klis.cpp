#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

int n;
int cache[502];
int cnt_cache[502];
int A[502];

int lis(int idx){
    int& ret = cache[idx];
    if(ret!=-1){
        return ret;
    }
    ret = 1;
    for(int i=idx+1;i<=n;i++){
        if(idx==0||A[idx]<A[i]){
            ret = max(ret, 1+lis(i));
        }
    }
    return ret;
}

int count(int idx){
    int& ret = cnt_cache[idx];
    if(ret!=-1){
        return ret;
    }
    if(lis(idx)==1){
        return ret = 1;
    }
    ret = 0;
    for(int i=idx+1;i<=n;i++){
        if((idx==0||A[idx]<A[i])&&lis(idx)==1+lis(i)){
            ret = min<long long>(INT_MAX, (long long)ret + count(i));
        }
    }
    return ret;
}

void klis(int idx, int k, vector<int>& r){
    vector<int> p;
    for(int i=idx+1;i<=n;i++){
        if(A[idx]<A[i]&&lis(idx)==1+lis(i)){
            p.push_back(i);
        }
    }
    int skip = k;
    for(auto it = p.rbegin();it!=p.rend();it++){
        int tar = *it;
        if(skip<=count(tar)){
            r.push_back(A[tar]);
            klis(tar, skip, r);
            return;
        } else {
            skip -= (int)count(tar);
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int k;
        cin >> n >> k;
        for(int i=1;i<=n;i++){
            cin >> A[i];
        }
        memset(cache, -1, sizeof(cache));
        memset(cnt_cache, -1, sizeof(cnt_cache));
        cout << lis(0)-1 << "\n";
        count(0);
        vector<int> r;
        klis(0, k, r);
        for(auto a: r){
            cout << a << " ";
        }
        cout << "\n";
        t--;
    }
}


