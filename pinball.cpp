#include <iostream>
#include <cmath>
#include <algorithm>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct vector2 {
    double x, y;
    explicit vector2(double x_, double y_): x(x_), y(y_) {}

    bool operator==(const vector2& rhs) const {
        return x==rhs.x && y==rhs.y;
    }

    bool operator<(const vector2& rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }

    vector2 operator+(const vector2& rhs) const {
        return vector2(x+rhs.x, y+rhs.y);
    }

    vector2 operator-(const vector2& rhs) const {
        return vector2(x-rhs.x, y-rhs.y);
    }

    vector2 operator*(const double r) const {
        return vector2(r*x, r*y);
    }

    double norm() const {
        return hypot(x, y);
    }

    vector2 normalize() const {
        return vector2(x/norm(), y/norm());
    }

    double polar() const {
        return fmod(atan2(y, x)+2*M_PI, 2*M_PI);
    }

    double dot(const vector2& rhs) const {
        return x*rhs.x + y*rhs.y;
    }

    double cross(const vector2& rhs) const {
        return x*rhs.y - y*rhs.x;
    }

    vector2 projectOn(const vector2& rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }

    vector2 reflectOn(const vector2& nml) const {
        vector2 p = this->projectOn(nml);
        return *this - p*2;
    }
};

vector2 perpendicularFoot(const vector2& a, const vector2& dl, const vector2& p) {
    return a + (p-a).projectOn(dl);
}

struct circle {
    double x, y, r;
    explicit circle(double _x, double _y, double _r): x(_x), y(_y), r(_r) {}
};

vector<int> hits(double x, double y, double dx, double dy, const vector<circle>& circles){
    vector<int> ret(100);
    for(int i=0;i<100;i++){
        vector2 s = vector2(x, y);
        vector2 dl = vector2(dx, dy);
        int minC = -1;
        double minD = 200;
        for(int j=0;j<circles.size();j++){
            if(i>0&&ret[i-1]==j) continue;
            vector2 origin = vector2(circles[j].x, circles[j].y);
            vector2 foot = perpendicularFoot(s, dl, origin);
            double r = circles[j].r;
            double dist = (origin-foot).norm();
            if(dist-r<1e-9){
                double h = r*r - dist*dist;
                vector2 hp = foot - dl.normalize() * sqrt(h);
                if((hp-s).dot(dl)<0) continue;
                if(hp.x<0||hp.x>100||hp.y<0||hp.y>100) continue;
                double d = (hp-s).norm();
                if(d<minD){
                    minD = d;
                    minC = j;
                    x = hp.x;
                    y = hp.y;
                }
            }
        }
        ret[i] = minC;
        if(minC==-1){
            break;
        }
        vector2 nml = vector2(x, y) - vector2(circles[minC].x, circles[minC].y);
        vector2 ndl = dl.reflectOn(nml);
        dx = ndl.x;
        dy = ndl.y;
    }
    return ret;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t>0){
        double x, y, dx, dy;
        int n;
        cin >> x >> y >> dx >> dy >> n;
        vector<circle> circles;
        for(int i=0;i<n;i++){
            double xi, yi, ri;
            cin >> xi >> yi >> ri;
            circles.push_back(circle(xi, yi, ri+1));
        }
        vector<int> h = hits(x, y, dx, dy, circles);
        for(int i=0;i<h.size();i++){
            if(h[i]==-1){
                break;
            }
            cout << h[i] << " ";
        }
        cout << "\n";
        t--;
    }
}


