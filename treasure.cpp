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

double ccw(vector2 a, vector2 b) {
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p, b-p);
}

bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a, b, c) * ccw(a, b ,d);
    double cd = ccw(c, d, a) * ccw(c, d, b);
    if(ab==0&&cd==0){
        if(b<a) swap(a, b);
        if(d<c) swap(c, d);
        return !((b<c)||(d<a));
    }
    return ab<=0 && cd<=0;
}

bool isInside(const vector<vector2>& poly, vector2 p){
    int cross = 0;
    for(int i=0;i<poly.size();i++){
        int j = (i+1)%poly.size();
        if(poly[i].y>p.y==poly[j].y>p.y) continue;
        double atX = (poly[j].x-poly[i].x) * (p.y-poly[i].y) / (poly[j].y-poly[i].y) + poly[i].x;
        if(p.x<atX) {
            cross++;
        }
    }
    return cross%2 > 0;
}

vector<vector2> cutPoly(const vector<vector2>& poly, const vector2& a, const vector2& b, bool towardY){
    vector<bool> inside(poly.size());
    for(int i=0;i<poly.size();i++){
        inside[i] = ccw(a, b, poly[i]) >= 0;
    }
    vector<vector2> ret;
    for(int i=0;i<poly.size();i++){
        int j = (i+1)%poly.size();
        if(inside[i]) ret.push_back(poly[i]);
        if(inside[i]!=inside[j]) {
            if(towardY&&poly[i].x>a.x!=poly[j].x>a.x){
                double atY = (poly[j].y-poly[i].y) * (a.x-poly[i].x) / (poly[j].x-poly[i].x) + poly[i].y;
                ret.push_back(vector2(a.x, atY));
            } else if(!towardY&&poly[i].y>a.y!=poly[j].y>a.y){
                double atX = (poly[j].x-poly[i].x) * (a.y-poly[i].y) / (poly[j].y-poly[i].y) + poly[i].x;
                ret.push_back(vector2(atX, a.y));
            }
        }
    }
    return ret;
}

double getArea(const vector<vector2>& poly, const vector<vector2>& rect){
    bool towardY = false;
    vector<vector2> overlapped = cutPoly(poly, rect[0], rect[1], towardY);
    for(int i=1;i<rect.size();i++){
        int j = (i+1)%rect.size();
        towardY = i%2 > 0;
        overlapped = cutPoly(overlapped, rect[i], rect[j], towardY);
    }
    double area = 0;
    for(int i=0;i<overlapped.size();i++){
        int j = (i+1)%overlapped.size();
        area += overlapped[i].cross(overlapped[j]);
    }
    return fabs(area)/2;
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cout << fixed;
    cout.precision(10);
    int t;
    cin >> t;
    while(t>0){
        double x1, y1, x2, y2;
        int n;
        cin >> x1 >> y1 >> x2 >> y2 >> n;
        vector<vector2> poly;
        for(int i=0;i<n;i++){
            double xi, yi;
            cin >> xi >> yi;
            poly.push_back(vector2(xi, yi));
        }
        vector<vector2> rect;
        rect.push_back(vector2(x1, y1)); rect.push_back(vector2(x2, y1));
        rect.push_back(vector2(x2, y2)); rect.push_back(vector2(x1, y2));
        cout << getArea(poly, rect) << "\n";
        t--;
    }
}


