#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    pair<int, int> x = {1, 1};
    auto [a, b] = x;
    cout << a << " " << b << endl;
    return 0;
}