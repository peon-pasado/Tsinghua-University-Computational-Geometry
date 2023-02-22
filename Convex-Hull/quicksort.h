
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

//[l, r)
void quicksort(vector<int>& arr, int l, int r) {
    if (r <= l+1) return;
    int pivot = arr[random(l, r-1)];
    auto m1 = partition(begin(arr)+l, begin(arr)+r, [pivot](const auto& em) {
        return em < pivot;
    });
    auto m2 = partition(m1, begin(arr)+r, [pivot](const auto& em) {
        return !(pivot < em);
    });
    quicksort(arr, l, m1 - begin(arr));
    quicksort(arr, m2 - begin(arr), r);
}

int main() {


    return 0;
}

