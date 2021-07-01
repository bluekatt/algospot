#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    vector<int> tree;

    FenwickTree(int size): tree(size+1) {}

    int sum(int pos) {
        ++pos;
        int ret = 0;
        while(pos>0) {
            ret += tree[pos];
            pos &= (pos-1);
        }
        return ret;
    }

    void add(int pos, int val) {
        ++pos;
        while(pos<tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n;
        cin >> n;
        int num;
        long long ret = 0;
        FenwickTree tree = FenwickTree(1000000);
        for(int i=0;i<n;i++) {
            cin >> num;
            ret += tree.sum(999999) - tree.sum(num);
            tree.add(num, 1);
        }
        cout << ret << "\n";
        t--;
    }
}
