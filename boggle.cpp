#include <iostream>
#include <cstring>

using namespace std;

char dir[8][2] = {{1,1}, {1,0}, {1,-1}, {0,1}, {0,-1}, {-1,1}, {-1,0}, {-1,-1}};

char board[5][5] = {0};
string words[12];
char cache[5][5][12];

char has_word(int x, int y, int wi, int idx){
    if(x<0||x>=5||y<0||y>=5){
        return 0;
    }
    char& ret = cache[x][y][idx];
    if(ret!=-1){
        return ret;
    }
    if(board[x][y]!=words[wi][idx]){
        return ret = 0;
    }
    if(words[wi].size()-idx==1){
        return ret = 1;
    }
    for(int i=0;i<8;i++){
        int dx = x + dir[i][0];
        int dy = y + dir[i][1];
        if(has_word(dx, dy, wi, idx+1)){
            return ret = 1;
        }
    }
    return ret = 0;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int wn;
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                cin >> board[i][j];
            }
        }
        cin >> wn;
        for(int i=0;i<wn;i++){
            cin >> words[i];
        }
        for(int k=0;k<wn;k++){
            memset(cache, -1, sizeof(cache));
            cout << words[k] << " ";
            char result = 0;
            for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                    result = has_word(i, j, k, 0);
                    if(result==1){
                        break;
                    }
                }
                if(result==1){
                    break;
                }
            }
            if(result==1){
                cout << "YES\n";
            } else if(result==0) {
                cout << "NO\n";
            }
        }
        t--;
    }
}

