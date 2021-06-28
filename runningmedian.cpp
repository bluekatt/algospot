#include <bits/stdc++.h>
#define MOD 20090711

using namespace std;

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0) {
        priority_queue<int, vector<int>, greater<int> > minHeap;
        priority_queue<int, vector<int>, less<int> > maxHeap;
        int n, a, b;
        cin >> n >> a >> b;
        long long tar = 1983;
        int sum = tar;
        maxHeap.push(tar);
        for(int i=1;i<n;i++) {
            tar = (tar * a + b) % MOD;
            if(maxHeap.size() == minHeap.size()) {
                maxHeap.push(tar);
            } else {
                minHeap.push(tar);
            }
            if(maxHeap.top()>minHeap.top()) {
                int maxTop = maxHeap.top();
                int minTop = minHeap.top();
                maxHeap.pop(); minHeap.pop();
                maxHeap.push(minTop); minHeap.push(maxTop);
            }
            sum = (sum + maxHeap.top()) % MOD;
        }
        cout << sum << "\n";
        t--;
    }
}

