#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> bit;  // Binary Indexed Tree (1-based indexing)
    int n;

public:
    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0);  // Initialize with 0s, size n+1 for 1-based indexing
    }

    // Add value `val` to index `i`
    void update(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += (i & -i);  // Move to parent
        }
    }

    // Get prefix sum from index 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += bit[i];
            i -= (i & -i);  // Move to ancestor
        }
        return sum;
    }

    // Get sum of range [l, r]
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    int n = 10;
    FenwickTree ft(n);

    // Example: initial values are 0
    ft.update(3, 5);  // Add 5 to index 3
    ft.update(7, 2);  // Add 2 to index 7
    ft.update(1, 4);  // Add 4 to index 1

    cout << "Prefix sum up to index 3: " << ft.query(3) << endl; // Output: 9
    cout << "Sum of range [3, 7]: " << ft.rangeQuery(3, 7) << endl; // Output: 7

    return 0;
}
