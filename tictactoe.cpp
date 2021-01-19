#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

int cache[20000];

int get_index(const int board[3][3]){
    int idx = 0;
    int base = 1;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            idx += board[i][j]*base;
            base*=3;
        }
    }
    return idx;
}

int get_next(const int board[3][3]){
    int xs = 0;
    int os = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==1){
                os++;
            } else if(board[i][j]==2){
                xs++;
            }
        }
    }
    if(xs>os){
        return 1;
    } else {
        return 2;
    }
}

int judge(const int board[3][3]){
    int winner = 0;
    for(int i=0;i<3;i++){
        int hor = 1;
        int ver = 1;
        for(int j=1;j<3;j++){
            if(board[i][j]==0||board[i][j]!=board[i][j-1]){
                hor = 0;
            }
            if(board[j][i]==0||board[j][i]!=board[j-1][i]){
                ver = 0;
            }
        }
        if(hor){
            winner = board[i][0];
        }
        if(ver){
            winner = board[0][i];
        }
    }
    if(board[0][0]!=0&&board[0][0]==board[1][1]&&board[1][1]==board[2][2]){
        winner = board[0][0];
    }
    if(board[2][0]!=0&&board[2][0]==board[1][1]&&board[1][1]==board[0][2]){
        winner = board[2][0];
    }
    return winner;
}

int can_win(int board[3][3], int turn){
    int& ret = cache[get_index(board)];
    if(ret!=-1){
        return ret;
    }
    int jud = judge(board);
    if(jud!=0){
        return ret = jud;
    }
    ret = 3;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==0){
                board[i][j] = turn;
                int r = can_win(board, 3-turn);
                board[i][j] = 0;
                if(r==turn){
                    return ret = r;
                }
                ret = min(ret, r);
            }
        }
    }
    if(ret==3){
        ret = 0;
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int board[3][3];
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                char c;
                cin >> c;
                if(c=='x'){
                    board[i][j] = 2;
                } else if(c=='o'){
                    board[i][j] = 1;
                } else {
                    board[i][j] = 0;
                }
            }
        }
        memset(cache, -1, sizeof(cache));
        int turn = get_next(board);
        int w = can_win(board, turn);
        if(w==2){
            cout << 'x' << "\n";
        } else if(w==1){
            cout << 'o' << "\n";
        } else {
            cout << "TIE" << "\n";
        }
        t--;
    }
}


