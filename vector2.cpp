#include <algorithm>
#include <cmath>

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

    vector2 projection(const vector2& rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }
};
