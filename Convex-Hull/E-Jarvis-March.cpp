#include <bits/stdc++.h>
#define sz(x) (int)x.size()
#define trav(v, x) for (auto v : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define set_to(x, v) fill(all(x), v)
#define eb emplace_back
#define lso(x) ((x)&-(x))
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
const int mod = 1e9 + 7;

class JarvisMarch {
public:
    struct Point {
        int x;
        int y;
        bool extreme;
        int succ;
    };

    void jarvis(Point S[], int n) {
      for (int k = 0; k < n; ++k) {
        S[k].extreme = false;
      }
      int ltl = LTL(S, n);
      int k = ltl;
      do {
        P[k].extreme = true;
        int s = -1;
        for (int t = 0; t < n; ++t) {
          if (t != k && t != s
              && (s == -1 || !to_left(P[k], P[s], P[t]))) {
            s = t;
          }
        }
        P[k].succ = s;
        k = s;
      } while (ltl != k);
    }

    void solveOne(istream& in, ostream& out) {

    }

    void solve(istream& in, ostream& out) {
        int testNumber = 1;
        //in >> testNumber;
        re(tc, 1, testNumber+1) {
            //out << "Case #" << tc << ": ";
            solveOne(in, out);
        }
    }
};
