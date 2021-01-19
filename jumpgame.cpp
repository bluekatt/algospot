#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int n;
int board[102][102];
int cache[102][102];

bool path_exists(int x, int y){
    if(x<0||x>=n||y<0||y>=n){
        return false;
    }
    int& ret = cache[x][y];
    if(ret!=-1){
        return ret;
    }
    if(x==n-1&&y==n-1){
        return (ret = true);
    }
    int jump = board[x][y];
    return (ret = (path_exists(x, y+jump) || path_exists(x+jump, y)));
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n;
        for(int i=0;i<n;i++) {
            for (int j = 0; j < n; j++) {
                cin >> board[i][j];
            }
        }
        memset(cache, -1, sizeof(cache));
        if(path_exists(0,0)){
            cout << "YES\n";
        } else {
            cout << "NO\n";
        };
        t--;
    }
}

