#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    int n;
    vector<int> rangeMin;
    vector<int> rangeMax;

    SegmentTree(const vector<int>& array) {
        n = array.size();
        rangeMin.resize(n * 4);
        rangeMax.resize(n * 4);

        initMin(array, 0, n-1, 0);
        initMax(array, 0, n-1, 0);
    }

    int initMin(const vector<int>& array, int left, int right, int node) {
        if (left == right) return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = initMin(array, left, mid, node*2+1);
        int rightMin = initMin(array, mid+1, right, node*2+2);
        return rangeMin[node] = min(leftMin, rightMin);
    }

    int initMax(const vector<int>& array, int left, int right, int node) {
        if (left == right) return rangeMax[node] = array[left];
        int mid = (left + right) / 2;
        int leftMax = initMax(array, left, mid, node*2+1);
        int rightMax = initMax(array, mid+1, right, node*2+2);
        return rangeMax[node] = max(leftMax, rightMax);
    }

    int queryMin(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (nodeRight < left || right < nodeLeft)
            return INT_MAX;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        int mid = (nodeLeft + nodeRight) / 2;
        int leftMin = queryMin(left, right, node*2+1, nodeLeft, mid);
        int rightMin = queryMin(left, right, node*2+2, mid+1, nodeRight);
        return min(leftMin, rightMin);
    }

    int queryMax(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (nodeRight < left || right < nodeLeft)
            return INT_MIN;
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMax[node];
        int mid = (nodeLeft + nodeRight) / 2;
        int leftMin = queryMax(left, right, node*2+1, nodeLeft, mid);
        int rightMin = queryMax(left, right, node*2+2, mid+1, nodeRight);
        return max(leftMin, rightMin);
    }

    int queryMin(int left, int right) {
        return queryMin(left, right, 0, 0, n-1);
    }

    int queryMax(int left, int right) {
        return queryMax(left, right, 0, 0, n-1);
    }
};

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n, q;
        cin >> n >> q;
        vector<int> array(n);
        for(int i=0;i<n;i++) {
            cin >> array[i];
        }
        SegmentTree st = SegmentTree(array);
        for(int i=0;i<q;i++) {
            int left, right;
            cin >> left >> right;
            int maxHeight = st.queryMax(left, right);
            int minHeight = st.queryMin(left, right);
            cout << maxHeight - minHeight << "\n";
        }
        t--;
    }
}

