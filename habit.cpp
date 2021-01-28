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

struct Comp {
    vector<int>& group;
    int t;
    Comp(vector<int>& _group, int _t): group(_group), t(_t) {}

    bool operator() (int a, int b){
        if(group[a]!=group[b]) {
            return group[a] < group[b];
        }else{
            return group[a+t] < group[b+t];
        }
    }
};

vector<int> getSuffixArray(const string& s){
    int n = s.size();
    vector<int> perm(n);
    for(int i=0;i<n;i++){
        perm[i] = i;
    }
    int t = 1;
    vector<int> group(n+1);
    for(int i=0;i<n;i++){
        group[i] = s[i];
    }
    group[n] = -1;
    while(t<n){
        Comp compWith2T(group, t);
        sort(perm.begin(), perm.end(), compWith2T);

        t *= 2;
        if(t>=n) break;

        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i=1;i<n;i++){
            if(compWith2T(perm[i-1], perm[i])) {
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            } else {
                newGroup[perm[i]] = newGroup[perm[i-1]];
            }
        }
        group = newGroup;
    }
    return perm;
}

int commonPrefix(const string& s, int i, int j){
    int k = 0;
    while(i+k<s.size()&&j+k<s.size()&&s[i+k]==s[j+k]){
        k++;
    }
    return k;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int k;
        string script;
        cin >> k;
        cin >> script;
        vector<int> sa = getSuffixArray(script);
        int ret = 0;
        for(int i=0;i+k<=sa.size();i++){
            ret = max(ret, commonPrefix(script, sa[i], sa[i+k-1]));
        }
        cout << ret << "\n";
        t--;
    }
}

