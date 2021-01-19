#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int h, w;
int r, c;
int board[11][11];
int block[11][11];
int best;
int covered;
int boardsize;
int blocksize;
vector<vector<pair<int, int> > > rotat;

void rotate(){
    int n_block[11][11];
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            n_block[j][i] = block[i][j];
        }
    }
    for(int i=0;i<c;i++){
        for(int j=0;j<r;j++){
            block[i][j] = n_block[i][r-1-j];
        }
    }
    swap(r, c);
}

void generate_rotate(){
    rotat.clear();
    rotat.resize(4);
    for(int ro=0;ro<4;ro++){
        int o_x = -1, o_y = -1;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(block[i][j]){
                    if(o_x==-1){
                        o_x = i;
                        o_y = j;
                    }
                    rotat[ro].push_back(make_pair(i-o_x, j-o_y));
                }
            }
        }
        rotate();
    }
    sort(rotat.begin(), rotat.end());
    rotat.erase(unique(rotat.begin(), rotat.end()), rotat.end());
    blocksize = rotat[0].size();
}

bool cover(int x, int y, int rot, int cov){
    bool ret = true;
    for(int i=0;i<rotat[rot].size();i++){
        int t_x = x + rotat[rot][i].first;
        int t_y = y + rotat[rot][i].second;
        if(t_x<0||t_y<0||t_x>=h||t_y>=w){
            ret = false;
            continue;
        }
        if(board[t_x][t_y]){
            ret = false;
        }
        board[t_x][t_y] += cov;
    }
    return ret;
}

int left_board(int x, int y){
    int cnt = 0;
    for(int j=y;j<w;j++){
        if(board[x][j]==0){
            cnt++;
        }
    }
    for(int i=x+1;i<h;i++){
        for(int j=0;j<w;j++){
            if(board[i][j]==0){
                cnt++;
            }
        }
    }
    return cnt;
}

void solve(int x, int y){
    if(covered+left_board(x, y)/blocksize<best){
        return;
    }
    if(x>=h){
        if(covered>best){
            best = covered;
        }
        return;
    }
    int next_x = x;
    int next_y = y+1;
    if(next_y>=w){
        next_x = x+1;
        next_y = 0;
    }
    for(int i=0;i<rotat.size();i++){
        if(cover(x, y, i, 1)){
            covered++;
            solve(next_x, next_y);
            covered--;
        }
        cover(x, y, i, -1);
    }
    solve(next_x, next_y);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> h >> w >> r >> c;
        boardsize = 0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                char ch;
                cin >> ch;
                if(ch=='#'){
                    board[i][j] = 1;
                } else {
                    board[i][j] = 0;
                    boardsize++;
                }
            }
        }
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                char ch;
                cin >> ch;
                if(ch=='#'){
                    block[i][j] = 1;
                } else {
                    block[i][j] = 0;
                }
            }
        }
        generate_rotate();
        best = -1;
        covered = 0;
        solve(0, 0);
        cout << best << "\n";
        t--;
    }
}


