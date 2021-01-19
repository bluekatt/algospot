#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

int n;
int mat[52][52];
double cache[52][52][102];
double prob[52];

double cal_prob(int src, int dst, int d){
    double& ret = cache[src][dst][d];
    if(ret!=-1){
        return ret;
    }
    if(d==0){
        if(src==dst){
            return ret = 1;
        } else {
            return ret = 0;
        }
    }
    ret = 0;
    for(int i=0;i<n;i++){
        if(mat[src][i]) ret += prob[src] * cal_prob(i, dst, d-1);
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        int d, p;
        cin >> n >> d >> p;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin >> mat[i][j];
            }
        }
        for(int i=0;i<n;i++){
            double pr = 0;
            for(int j=0;j<n;j++){
                if(mat[i][j]){
                    pr += 1;
                }
            }
            prob[i] = 1/pr;
        }
        for(int i=0;i<52;i++){
            for(int j=0;j<52;j++){
                for(int k=0;k<102;k++){
                    cache[i][j][k] = -1;
                }
            }
        }
        int c;
        cin >> c;
        for(int i=0;i<c;i++){
            int q;
            cin >> q;
            cout.setf(ios::fixed);
            cout.precision(10);
            cout << cal_prob(p, q, d) << " ";
        }
        cout << "\n";
        t--;
    }
}


