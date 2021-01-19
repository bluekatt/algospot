#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n;
int triangle[102][102];
int cache[102][102];

int find_max(int x, int y){
    int& ret = cache[x][y];
    if(ret!=-1){
        return ret;
    }
    if(x==n){
        return ret = 0;
    }
    return ret = (triangle[x][y] + max(find_max(x+1, y), find_max(x+1, y+1)));
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n;
        for(int i=0;i<n;i++){
            for(int j=0;j<=i;j++){
                cin >> triangle[i][j];
            }
        }
        memset(cache, -1, sizeof(cache));
        cout << find_max(0, 0) << "\n";
        t--;
    }
}

