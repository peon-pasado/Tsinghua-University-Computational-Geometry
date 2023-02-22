#include <bits/stdc++.h>
#define rep(i, j, n) for (int i=j; i<n; ++i)
using namespace std;

struct Edge {
    int bck, nxt;
    int u;
};

/**
 * @brief Algorithm to find dual tree of a polygon 
 * given triangulation diagonals. 
 * 
 * @idea
 *      - use ear theorem, remove an ear in n-2 steps (create a node for every one).
 *      - maintain a list for the dynamic polygon boundary.
 *      - associate "ear nodes" to polygon boundary.    
 *
 */
using pii = pair<int, int>;
vector<pii> diagonals_to_dual_tree(vector<pii> diagonals) {
    int n = diagonals.size() + 3;
    vector<int> deg(n, 2);
    vector<pii> edges;
    vector<Edge> L;
    rep(i, 0, n) L.push_back({(i+n-1)%n, (i+1)%n, -1});
    for (auto [u, v] : diagonals)
        deg[u]++, deg[v]++;
    auto remove_point = [&](int v, int node) {
        int u = L[L[v].bck].u, w = L[v].u;
        if (u != -1) edges.emplace_back(u, node);
        if (w != -1) edges.emplace_back(w, node);
        L[L[v].bck].nxt = L[v].nxt;
        L[L[v].nxt].bck = L[v].bck;
        L[L[v].bck].u = node;
    };
    queue<int> Q;
    for (int i=0; i<n; ++i)
        if (deg[i] == 2) {
            deg[i]--;
            Q.emplace(i);
        }
    for (int i=0; i<n-2; ++i) {
        int q = Q.front(); Q.pop();
        remove_point(q, i);
        for (int u : {L[q].bck, L[q].nxt})
            if (--deg[u] == 2) Q.emplace(u);
    }
    int q = Q.front();
    int u = L[q].u, v = L[L[q].nxt].u;
    if (u > v) swap(u, v);
    if (u != -1) edges.emplace_back(u, v);
    return edges;
}

int main() {
    vector<pii> D = {{1, 3}, {3, 5}, {5, 7}, {7, 1}, {1, 5}};   
    auto E = diagonals_to_dual_tree(D);
    for (auto e : E)
        cout << e.first << " " << e.second << '\n';
    return 0;
}
