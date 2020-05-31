#include <iostream>

struct Point {
    int x;
    int y;
};

struct Edge {
    Point p;
    Point q;
    Edge() {}
    Edge(Point p, Point q): p(p), q(q) {}
};

long long cross(Point p, Point q) {
    return p.x * q.y - p.y * q.x;
}

long long area2(Point p, Point q, Point s) {
    return cross(p, q) + cross(q, s) + cross(s, p);
}

bool toLeft(Point p, Point q, Point s) {
    return area2(p, q, s) > 0;
}

void extreme_edges(Point S[], int n, Edge E[]) {
    int index = 0;
    for (int p = 0; p < n; ++p) {
        for (int q = p + 1; q < n; ++q) {
            int toLeftCount = 0;
            for (int r = 0; r < n; ++r) {
                if (p == r || q == r) continue;
                toLeftCount += toLeft(S[p], S[q], S[r]);
            }
            if (toLeftCount == 0 || toLeftCount == n-2) {
                E[index++] = Edge(S[p], S[q]);
            }
        }
    }
}

int main() {

    return 0;
}
