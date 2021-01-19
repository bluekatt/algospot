#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

const int D = 1000000007;
int n;
string e, digits;
int m;
int cache[1<<15][20][2];

string digit_sort(string s){
    int d[10] = {0};
    for(int i=0;i<s.size();i++){
        d[s[i]-'0']++;
    }
    string ret;
    for(int i=0;i<10;i++){
        ret += string(d[i], i+'0');
    }
    return ret;
}

int cal_possible(int idx, int taken, int rest, int less){
    if(taken==(1<<n)-1){
        if(less&&rest==0){
            return 1;
        } else {
            return 0;
        }
    }
    int& ret = cache[taken][rest][less];
    if(ret!=-1){
        return ret;
    }
    ret = 0;
    for(int i=0;i<n;i++){
        if(!less&&e[idx]<digits[i]) {
            continue;
        } else if((i>0&&digits[i-1]==digits[i])&&!(taken&(1<<(i-1)))){
            continue;
        } else if(!(taken&(1<<i))) {
            int n_taken = taken | (1<<i);
            int n_rest = (10*rest+digits[i]-'0')%m;
            int n_less = less || (e[idx]>digits[i]);
            ret = (ret + cal_possible(idx+1, n_taken, n_rest, n_less))%D;
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
        cin >> e >> m;
        n = e.size();
        digits = digit_sort(e);
        memset(cache, -1, sizeof(cache));
        cout << cal_possible(0, 0, 0, 0) << "\n";
        t--;
    }
}


