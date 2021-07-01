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

const int MAX_N = 100000;

vector<int> child[MAX_N];
int no2Serial[MAX_N], serial2No[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];

int serialNo;

void traverse(int node, int d, vector<int>& trip) {
    no2Serial[node] = serialNo;
    serial2No[serialNo] = node;
    serialNo++;

    depth[node] = d;
    locInTrip[node] = trip.size();

    trip.push_back(no2Serial[node]);

    for(auto it=child[node].begin();it!=child[node].end();it++) {
        traverse(*it, d+1, trip);

        trip.push_back(no2Serial[node]);
    }
}

SegmentTree prepareTree() {
    serialNo = 0;
    vector<int> trip;
    traverse(0, 0, trip);

    return SegmentTree(trip);
}

int distance(int a, int b, SegmentTree& st) {
    int la = locInTrip[a], lb = locInTrip[b];
    if(la>lb) swap(la, lb);
    int ancestor = serial2No[st.queryMin(la, lb)];
    return depth[a] + depth[b] - 2*depth[ancestor];
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        int n, q;
        cin >> n >> q;
        for(int i=0;i<MAX_N;i++) {
            child[i].clear();
        }
        for(int i=1;i<n;i++) {
            int an;
            cin >> an;
            child[an].push_back(i);
        }
        SegmentTree st = prepareTree();
        for(int i=0;i<q;i++) {
            int a, b;
            cin >> a >> b;
            cout << distance(a, b, st) << "\n";
        }
        t--;
    }
}
