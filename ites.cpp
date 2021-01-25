#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <list>
#include <stack>
#include <map>

using namespace std;

int n, k;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        cin >> k >> n;
        queue<int> q;
        unsigned int gen = 1983;
        int qsum = 0;
        int cnt = 0;
        for(int i=0;i<n;i++){
            int newNum = gen%10000 + 1;
            qsum += newNum;
            q.push(newNum);
            while(qsum>k){
                qsum -= q.front();
                q.pop();
            }
            if(qsum==k){
                cnt++;
            }
            gen = gen*214013 + 2531011;
        }
        t--;
        cout << cnt << "\n";
    }
}

