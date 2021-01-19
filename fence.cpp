#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int fence[20002];

int max_area(int s, int e){
    int m = (e+s)/2;
    if(s+1==e){
        return fence[s];
    }
    int ret = max(max_area(s, m), max_area(m, e));
    int l = m-1;
    int r = m;
    int length = min(fence[l], fence[r]);
    int mid_max = length*2;
    while(s<l&&r<e-1){
        if(fence[l-1]<fence[r+1]){
            r++;
            length = min(length, fence[r]);
        } else {
            l--;
            length = min(length, fence[l]);
        }
        mid_max = max(mid_max, (r-l+1)*length);
    }
    while(s<l){
        length = min(length, fence[l]);
        mid_max = max(mid_max, (r-l+1)*length);
        l--;
    }
    while(r<e-1){
        length = min(length, fence[r]);
        mid_max = max(mid_max, (r-l+1) * length);
        r++;
    }
    length = min(length, fence[r]);
    mid_max = max(mid_max, (r-l+1) * length);
    return max(ret, mid_max);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n;
        cin >> n;
        for(int i=0;i<n;i++){
            cin >> fence[i];
        }
        cout << max_area(0, n) << "\n";
        t--;
    }
}

