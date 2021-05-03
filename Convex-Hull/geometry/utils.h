#ifndef UTILS_H
#define UTILS_H

#include "point.h"

template<class T, class U, class V, class W>
bool in_triangle(const Point<T> a, const Point<U> b, const Point<V> c, const Point<W> q) {
    if (a == b && b == c) return a == q;
    if (a == b) return (b.cross(c, q) == 0) && (min(b, c) <= q && q <= max(b, c));
    if (b == c) return (a.cross(b, q) == 0) && (min(a, b) <= q && q <= max(a, b));
    if (a == c) return (a.cross(c, q) == 0) && (min(a, c) <= q && q <= max(a, c));
    bool ab_left = a.cross(b, q) <= 0;
    bool bc_left = b.cross(c, q) <= 0;
    bool ca_left = c.cross(a, q) <= 0;
    return ab_left == bc_left && ab_left == ca_left;
}

template<class T, class U, class V>
bool to_left(Point<T> o, Point<U> a, Point<V> b) {
    return o.cross(a, b) >= 0;
}
#endif