#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

string s;
int s_size;
int cache[10002];

int get_difficulty(const string& str){
    char start = str[0];
    int d = str[1] - str[0];
    int diff[6] = {1,1,1,0,1,1};
    if(d!=0){
        diff[1] = 0;
    }
    if(d!=1&&d!=-1){
        diff[2] = 0;
    }
    for(int i=2;i<str.size();i++){
        if(start!=str[i]){
            diff[1] = 0;
        }
        if(str[i]-str[i-1]!=d){
            diff[2] = 0;
            diff[5] = 0;
        }
        if(str[i]!=str[i%2]){
            diff[4] = 0;
        }
    }
    for(int i=1;i<=5;i++){
        if(diff[i]){
            return i;
        }
    }
    return 10;
}

int memorize(int idx){
    if(s_size==idx){
        return 0;
    }
    int& ret = cache[idx];
    if(ret!=-1){
        return ret;
    }
    ret = 987654321;
    if(s_size-idx<3){
        return ret;
    }
    for(int i=3;i<=5;i++){
        if(idx+i<=s_size){
            ret = min(ret, get_difficulty(s.substr(idx, i))+memorize(idx+i));
        }
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> s;
        memset(cache, -1, sizeof(cache));
        s_size = s.size();
        cout << memorize(0) << "\n";
        t--;
    }
}

