#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

string upsidedown(string& pic){
    char f = pic.at(0);
    pic.erase(0, 1);
    if(f=='x'){
        string ul = upsidedown(pic);
        string ur = upsidedown(pic);
        string dl = upsidedown(pic);
        string dr = upsidedown(pic);
        return "x" + dl + dr + ul + ur;
    } else {
        return string(1, f);
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        string pic;
        cin >> pic;
        cout << upsidedown(pic) << "\n";
        t--;
    }
}

