#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

int connectivity[10][5] = {
        {0, 1, 2, -1, -1},
        {3, 7, 9, 11, -1},
        {4, 10, 14, 15, -1},
        {0, 4, 5, 6, 7},
        {6, 7, 8, 10, 12},
        {0, 2, 14, 15, -1},
        {3, 14, 15, -1, -1},
        {4, 5, 7, 14, 15},
        {1, 2, 3, 4, 5},
        {3, 4, 5, 9, 13}
};

int clocks[16];

void push(int swi){
    for(int i=0;i<5;i++){
        int tar = connectivity[swi][i];
        if(tar==-1){
            break;
        }
        clocks[tar] += 3;
        clocks[tar] %= 12;
    }
}

int traverse(int swi){
    bool valid = true;
    for(int i=0;i<16;i++){
        if(clocks[i]!=0){
            valid = false;
            break;
        }
    }
    if(valid){
        return 0;
    }
    if(swi>=10){
        return 987654321;
    }
    int ret = 987654321;
    for(int i=0;i<4;i++){
        ret = min(ret, i+traverse(swi+1));
        push(swi);
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        for(int i=0;i<16;i++){
            cin >> clocks[i];
            clocks[i] %= 12;
        }
        int ans = traverse(0);
        if(ans==987654321){
            ans = -1;
        }
        cout << ans << "\n";
        t--;
    }
}

