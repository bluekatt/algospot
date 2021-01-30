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

void printPostOrder(vector<int>& pre, vector<int>& in, int pb, int ib, int size){
    if(size<=0){
        return;
    }
    int root = pre[pb];

    int lSize = find(in.begin(), in.end(), root) - in.begin() - ib;

    printPostOrder(pre, in, pb+1, ib, lSize);
    printPostOrder(pre, in, pb+1+lSize, ib+1+lSize, size-1-lSize);

    cout << root << " ";
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n;
        cin >> n;
        vector<int> pre(n);
        vector<int> in(n);
        for(int i=0;i<n;i++){
            cin >> pre[i];
        }
        for(int i=0;i<n;i++){
            cin >> in[i];
        }
        printPostOrder(pre, in, 0, 0, n);
        t--;
    }
}

