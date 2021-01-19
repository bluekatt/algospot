#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

int found;
int n;
int board[22][22];
int cands[10][46][1024];
int hint_num[20][20][2];
int sum[400], length[400], known[400];

int get_size(int set){
    int cnt = 0;
    for(int i=1;i<10;i++){
        if(set&(1<<i)){
            cnt++;
        }
    }
    return cnt;
}

int get_sum(int set){
    int s = 0;
    for(int i=1;i<10;i++){
        if(set&(1<<i)){
            s += i;
        }
    }
    return s;
}

void generate_candidates(){
    for(int set=0;set<1024;set+=2){
        int subset = set;
        int s = get_sum(set);
        int l = get_size(set);
        while(1){
            cands[l][s][subset] |= (set&~subset);
            if(subset==0){
                break;
            }
            subset = (subset-1)&set;
        }
    }
}

int get_cand(int y, int x){
    int cs[2];
    for(int i=0;i<2;i++){
        int h = hint_num[y][x][i];
        int l = length[h];
        int s = sum[h];
        int k = known[h];
        cs[i] = cands[l][s][k];
    }
    return cs[0] & cs[1];
}

void print_board(){
    for(int y=1;y<=n;y++){
        for(int x=1;x<=n;x++){
            cout << board[y][x] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void put(int y, int x, int num){
    board[y][x] = num;
    for(int d=0;d<2;d++){
        int h = hint_num[y][x][d];
        known[h] |= (1<<num);
    }
}

void remove(int y, int x, int num){
    board[y][x] = -1;
    for(int d=0;d<2;d++){
        int h = hint_num[y][x][d];
        known[h] &= ~(1<<num);
    }
}

bool solve(){
    int t_x=-1, t_y=-1;
    int min_cand = 1023;
    for(int y=1;y<=n;y++){
        for(int x=1;x<=n;x++){
            int cand = get_cand(y, x);
            if(board[y][x]==-1&&get_size(cand)<get_size(min_cand)){
                min_cand = cand;
                t_y = y;
                t_x = x;
            }
        }
    }
    if(min_cand==0){
        return false;
    }
    if(t_x==-1){
        print_board();
        return true;
    }
    for(int i=1;i<=9;i++){
        if(min_cand&(1<<i)){
            put(t_y, t_x, i);
            if(solve()) return true;
            remove(t_y, t_x, i);
        }
    }
    return false;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n;
        for(int y=1;y<=n;y++){
            for(int x=1;x<=n;x++){
                int b;
                cin >> b;
                board[y][x] = -b;
            }
        }
        memset(cands, 0, sizeof(cands));
        memset(hint_num, 0, sizeof(hint_num));
        memset(sum, 0, sizeof(sum));
        memset(length, 0, sizeof(length));
        memset(known, 0, sizeof(known));
        int q;
        cin >> q;
        for(int i=1;i<=q;i++){
            int y, x, d, s;
            cin >> y >> x >> d >> s;
            int l = 0;
            if(d==0){
                x++;
                while(x<=n&&board[y][x]!=0){
                    hint_num[y][x++][d] = i;
                    l++;
                }
            } else {
                y++;
                while(y<=n&&board[y][x]!=0){
                    hint_num[y++][x][d] = i;
                    l++;
                }
            }
            sum[i] = s;
            length[i] = l;
        }
        generate_candidates();
        found = 0;
        solve();
        t--;
    }
}


