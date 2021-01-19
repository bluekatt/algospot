#include <iostream>
#include <cstring>

using namespace std;

int shape[4][2][2] = {{{0,1},{1,0}}, {{0,1},{1,1}}, {{1,0},{1,1}}, {{1,0},{1,-1}}};

int h, w;
int board[22][22];

bool cover(int m, int s, int x, int y){
    bool ret = true;
    board[x][y] += m;
    for(int i=0;i<2;i++){
        int dx = x + shape[s][i][0];
        int dy = y + shape[s][i][1];
        if(dx>=h||dx<0||dy>=w||dy<0){
            ret = false;
            continue;
        }
        if(board[dx][dy]){
            ret = false;
        }
        board[dx][dy] += m;
    }
    return ret;
}

int count_ways(int blank, int x, int y){
    if(blank==0){
        return 1;
    }
    if(blank%3){
        return 0;
    }
    int nextX = 0, nextY = 0;
    if(y+1>=w){
        if(x+1>=h){
            return 0;
        }
        nextX = x+1; nextY = 0;
    } else {
        nextX = x; nextY = y+1;
    }
    if(board[x][y]){
        return count_ways(blank, nextX, nextY);
    }
    int ret = 0;
    for(int i=0;i<4;i++){
        if(cover(1, i, x, y)){
            ret += count_ways(blank-3, nextX, nextY);
        }
        cover(-1, i, x, y);
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> h >> w;
        int blank = 0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                char c;
                cin >> c;
                if(c=='.'){
                    blank++;
                    board[i][j] = 0;
                } else {
                    board[i][j] = 1;
                }
            }
        }
        cout << count_ways(blank, 0, 0) << "\n";
        t--;
    }
}

