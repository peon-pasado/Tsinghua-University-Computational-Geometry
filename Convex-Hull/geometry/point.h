#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
using namespace std;


const double eps = 1e-8;
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    
    void swap(Point&& p) {swap(x, p.x); swap(y, p.y);}
    template <class U> 
    explicit operator Point<U>() const {return Point<U>(static_cast<U>(x), static_cast<U>(y));}
    //bool operations
    template<class U>
    bool operator<(const Point<U> p) const {return x+eps<p.x||(abs(x-p.x)<eps&&y+eps<p.y);}
    template<class U>
    bool operator>(const Point<U> p) const {return p<*this;}
    template<class U>
    bool operator<=(const Point<U> p) const {return !(*this>p);}
    template<class U>
    bool operator>=(const Point<U> p) const {return !(*this<p);}
    template<class U>
    bool operator==(const Point<U> p) const {return abs(x-p.x)<eps&&abs(y-p.y)<eps;}
    template<class U>
    bool operator!=(const Point<U> p) const {return !(*this == p);}

    //asign expresions
    template<class U>
    P& operator+=(Point<U> p) {return *this=*this+p;}
    template<class U>
    P& operator-=(Point<U> p) {return *this=*this-p;}
    template<class U>
    P& operator=(Point<U> p) {return *this=p;}
    
    
    //geometry operations
    template<class U>
    auto dot(const Point<U> p) const {return (*this)*p;}
    template<class U, class V>
    auto dot(const Point<U> p, const Point<V> q) const {return (p-*this)*(q-*this);}
    template<class U>
    auto cross(const Point<U> p) const {return (*this)^p;}
    template<class U, class V>
    auto cross(const Point<U> p, const Point<V> q) const {return (p-*this)^(q-*this);}
    auto norm2() const {return (*this)*(*this);}
    auto norm() const {return sqrt(norm2());}
    template<class U>
    auto dist(Point<U> p) {return (p-*this).norm();}
    auto angle() const {return atan2(y, x);}
    template<class U> //angle to x-axis in interval [-pi, pi]
    auto angle(Point<U> p) const {return atan2(*this ^ p, *this * p);}
    auto unit() const {return *this / norm();}
    P perp() const {return P(-y, x);} // rotates +90 degrees
    auto normal() const {return perp().unit();}
    // returns point rotated 'a' radians ccw around the origin
    auto rotate(double a) const {return rot(*this, a);}
    template<class U>
    auto rotate(Point<U> p, double a) const {return rot(*this-p, a)+p;}
    
    //I/O    
    friend istream& operator>>(istream& is, P& other) {return is >> other.x >> other.y;}
    friend ostream& operator<<(ostream& os, P other) {
        os << other.x << " " << other.y;
        return  os;
    }
};

//arithmetic operations
template<class U, class V>
auto operator+(const Point<U> p, const Point<V> q) {
    return Point(p.x+q.x, p.y+q.y);
}
template<class U, class V>
auto operator-(const Point<U> p, const Point<V> q) {
    return Point(p.x-q.x, p.y-q.y);
}
template<class U, class T>
auto operator*(const Point<U> p, const T c) {
    return Point(p.x*c, p.y*c);
}
template<class U, class T> 
auto operator/(const Point<U> p, const T c) {
    return Point(p.x/c, p.y/c);
}
template<class T, class U>
auto operator*(const T c, const Point<U> p) {
    return p*c;
}

//geometry operations
template<class U, class V>
auto operator*(const Point<U> p, const Point<V> q) {
    return p.x*q.x+p.y*q.y;
}
template<class U, class V>
auto operator^(const Point<U> p, const Point<V> q) {
    return p.x*q.y-p.y*q.x;
}
template<class U>
auto rot(const Point<U> p, double alpha) {
    Point sc(sin(alpha), cos(alpha));
    return Point(p^sc, p*sc);
}

#endif