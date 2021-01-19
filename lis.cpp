#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n;
int seq[502];
int cache[502];

int lis(int s){
    int& ret = cache[s+1];
    if(ret!=-1){
        return ret;
    }
    ret = 1;
    for(int i=s+1;i<n;i++){
        if(s==-1||seq[s]<seq[i]){
            ret = max(ret, lis(i)+1);
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
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> seq[i];
        }
        memset(cache, -1, sizeof(cache));
        cout << lis(-1)-1 << "\n";
        t--;
    }
}

