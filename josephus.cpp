#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <list>
#include <map>

using namespace std;

int n, k;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        cin >> n >> k;
        list<int> l;
        for(int i=2;i<=n;i++){
            l.push_back(i);
        }
        n--;
        auto it = l.begin();
        while(n>2){
            for(int i=0;i<k-1;i++){
                it++;
                if(it==l.end()) it = l.begin();
            }
            it = l.erase(it);
            if(it==l.end()) it = l.begin();
            n--;
        }
        cout << l.front() << " " << l.back() << "\n";
        t--;
    }
}

