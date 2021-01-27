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

vector<int> getPartialMatch(const string& a){
    int n = a.size();
    int matched = 0;
    vector<int> pi(n, 0);
    for(int i=1;i<n;i++){
        while(matched>0&&a[i]!=a[matched]){
            matched = pi[matched-1];
        }
        if(a[i]==a[matched]){
            matched++;
            pi[i] = matched;
        }
    }
    return pi;
}

int kmpFirstSearch(const string& a, const string& b){
    int n = a.size(), m = b.size();
    int matched = 0;
    vector<int> pi = getPartialMatch(b);
    vector<int> ret;
    for(int i=0;i<n;i++){
        while(matched>0&&a[i]!=b[matched]){
            matched = pi[matched-1];
        }
        if(a[i]==b[matched]){
            matched++;
            if(matched==m){
                return i-m+1;
            }
        }
    }
    return 0;
}

int shift(const string& a, const string& b){
    string lengthen = a + a;
    return kmpFirstSearch(lengthen, b);
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n;
        cin >> n;
        string pre;
        string cur;
        cin >> pre;
        int cnt = 0;
        for(int i=0;i<n;i++){
            cin >> cur;
            if(i%2){
                cnt += shift(pre, cur);
            }else{
                cnt += shift(cur, pre);
            }
            pre = cur;
        }
        cout << cnt << "\n";
        t--;
    }
}

