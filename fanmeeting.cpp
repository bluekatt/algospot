#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

vector<int> multiply(const vector<int> &A, const vector<int> &B) {
    vector<int> C(A.size() + B.size() + 1, 0);
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            C[i + j] += A[i] * B[j];
        }
    }
    return C;
}

void addTo(vector<int>& A, const vector<int>& B, int k){
    A.resize(max(A.size(), B.size() + k));
    for (int i = 0; i < B.size(); i++) {
        A[i + k] += B[i];
    }
}

void subFrom(vector<int>& A, const vector<int>& B){
    A.resize(max(A.size(), B.size())+1);
    for (int i = 0; i < B.size(); i++) {
        A[i] -= B[i];
    }
}

vector<int> karatsuba(const vector<int>& A, const vector<int>& B){
    int na = A.size(); int nb = B.size();
    if(nb>na) return karatsuba(B, A);
    if(na==0||nb==0) return vector<int>();
    if(na<=50) return multiply(A, B);
    int half = na/2;
    vector<int> A0(A.begin(), A.begin()+half);
    vector<int> A1(A.begin()+half, A.end());
    vector<int> B0(B.begin(), B.begin()+min<int>(B.size(), half));
    vector<int> B1(B.begin()+min<int>(B.size(), half), B.end());
    vector<int> C0, C1, C2;
    C0 = karatsuba(A0, B0);
    C2 = karatsuba(A1, B1);
    addTo(A0, A1, 0); addTo(B0, B1, 0);
    C1 = karatsuba(A0, B0);
    subFrom(C1, C0);
    subFrom(C1, C2);
    vector<int> ret;
    addTo(ret, C0, 0);
    addTo(ret, C1, half);
    addTo(ret, C2, half+half);
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        string member;
        string fan;
        cin >> member >> fan;
        int m_size = member.size(), f_size = fan.size();
        vector<int> A(m_size), B(f_size);
        for(int i=0;i<m_size;i++){
            if(member[i]=='M'){
                A[i] = 1;
            } else {
                A[i] = 0;
            }
        }
        for(int i=0;i<f_size;i++){
            if(fan[i]=='M'){
                B[f_size-i-1] = 1;
            } else {
                B[f_size-i-1] = 0;
            }
        }
        vector<int> C = karatsuba(A, B);
        int allhug = 0;
        for(int i=m_size-1;i<f_size;i++){
            if(C[i]==0){
                allhug++;
            }
        }
        cout << allhug << "\n";
        t--;
    }
}

