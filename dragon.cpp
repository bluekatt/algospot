#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

const int MAX = 1000000000 + 10;
const string seed = "FX";
const string x_expand = "X+YF";
const string y_expand = "FX-Y";
int cache[502];
int length[502];

void precal(){
    length[0] = 1;
    for(int i=1;i<502;i++){
        length[i] = min(MAX, length[i-1]*2 + 2);
    }
}

char curve(int gen, int p, const string& s){
    if(gen==0){
        return s[p-1];
    }
    for(int i=0;i<s.size();i++){
        if(s[i]=='X') {
            if(p > length[gen]) {
                p -= length[gen];
            } else {
                return curve(gen-1, p, x_expand);
            }
        } else if(s[i]=='Y'){
            if(p > length[gen]) {
                p -= length[gen];
            } else {
                return curve(gen-1, p, y_expand);
            }
        } else if(p>1) {
            p--;
        } else {
            return s[i];
        }
    }
    return ' ';
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int n, p, l;
        cin >> n >> p >> l;
        memset(cache, -1, sizeof(cache));
        precal();
        for(int i=0;i<l;i++){
            cout << curve(n, p+i, seed);
        }
        cout << "\n";
        t--;
    }
}


