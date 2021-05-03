#include <iostream>
#include <vector>
#include "convex_hull.h"
#include "geometry/point.h"
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<Point<double>> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    p.erase(graham_scan(p.begin(), p.end()), p.end());
    cout << p.size() << '\n';
    for (int i = 0; i < p.size(); ++i) {
        cout << p[i] << '\n';
    }
    return 0;
}