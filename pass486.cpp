#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int factors[10000002] = {0};
int minFactorCounts[10000002] = {0};
int minFactor[10000002] = {0};

void getFactors(){
    for(int i=2;i<=10000000;i++){
        minFactor[i] = i;
        minFactorCounts[i] = 1;
        factors[i] = 2;
    }
    for(int i=2;i*i<=10000000;i++){
        if(minFactor[i]==i){
            for(int j=i*i;j<=10000000;j+=i){
                if(minFactor[j]==j) {
                    minFactor[j] = i;
                }
            }
        }
    }
    for(int i=2;i<=10000000;i++){
        int mf = minFactor[i];
        if(mf==i) continue;
        if(mf==minFactor[i/mf]) {
            minFactorCounts[i] = minFactorCounts[i/mf] + 1;
            factors[i] = factors[i/mf] / (minFactorCounts[i/mf]+1) * (minFactorCounts[i]+1);
        } else {
            minFactorCounts[i] = 1;
            factors[i] = factors[i/mf] * 2;
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    getFactors();
    int t;
    cin >> t;
    while(t>0){
        int n, lo, hi;
        cin >> n >> lo >> hi;
        int cnt = 0;
        for(int i=lo;i<=hi;i++){
            if(factors[i]==n) cnt++;
        }
        cout << cnt << "\n";
        t--;
    }
}


