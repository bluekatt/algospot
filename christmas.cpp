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

int pn, pk;
int dolls[100002];
int psum[100002];
int cache1[100002][100002];
int cache2[100002][100002];

int ques1(){
    int cnt = 0;
    for(int i=0;i<pn;i++){
        for(int j=i+1;j<pn;j++){
            int p;
            if(i>0){
                p = psum[i-1];
            } else {
                p = 0;
            }
            if((psum[j]-p) % pk==0) {
                cnt = (cnt + 1)%20091101;
            }
        }
    }
    return cnt;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        memset(cache1, -1, sizeof(cache1));
        memset(cache2, -1, sizeof(cache2));
        cin >> pn >> pk;
        for(int i=0;i<pn;i++){
            cin >> dolls[i];
            if(i>0){
                psum[i] = psum[i-1] + dolls[i];
            } else {
                psum[i] = psum[i];
            }
        }
        cout << ques1() << "\n";
        t--;
    }
}

