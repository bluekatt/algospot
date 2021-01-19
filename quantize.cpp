#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

int INF = 987654321;
int n, s;
int seq[102];
int p_sum[102], psq_sum[102];
int cache[102][12];

int get_region_ls(int l, int r){
    int lp_sum = 0, lpsq_sum = 0;
    if(l>0){
        lp_sum = p_sum[l-1];
        lpsq_sum = psq_sum[l-1];
    }
    int sum = p_sum[r]-lp_sum;
    int sq_sum = psq_sum[r]-lpsq_sum;
    int m = int(0.5+(double)sum/(r-l+1));
    return sq_sum - 2*m*sum + m*m*(r-l+1);
}

int least_square(int ni, int left_s){
    if(ni==n){
        return 0;
    }
    if(left_s==0){
        return INF;
    }
    int& ret = cache[ni][left_s];
    if(ret!=-1){
        return ret;
    }
    ret = INF;
    for(int i=ni;i<n;i++){
        ret = min(ret, get_region_ls(ni, i)+least_square(i+1, left_s-1));
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        cin >> n >> s;
        for(int i=0;i<n;i++){
            cin >> seq[i];
        }
        memset(cache, -1, sizeof(cache));
        sort(seq, seq+n);
        p_sum[0] = seq[0];
        psq_sum[0] = seq[0]*seq[0];
        for(int i=1;i<n;i++){
            p_sum[i] = p_sum[i-1] + seq[i];
            psq_sum[i] = psq_sum[i-1] + seq[i]*seq[i];
        }
        cout << least_square(0, s) << "\n";
        t--;
    }
}

