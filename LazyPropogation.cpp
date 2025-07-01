#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree, lazy;
    int n;

public:
    SegmentTree(vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(0, 0, n - 1, arr);
    }

    void build(int node, int start, int end, vector<int>& arr) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid, arr);
        build(2 * node + 2, mid + 1, end, arr);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void updateRange(int l, int r, int val) {
        updateRangeUtil(0, 0, n - 1, l, r, val);
    }

    void updateRangeUtil(int node, int start, int end, int l, int r, int val) {
        // Apply any pending updates
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        // No overlap
        if (start > r || end < l) return;

        // Complete overlap
        if (start >= l && end <= r) {
            tree[node] += (end - start + 1) * val;
            if (start != end) {
                lazy[2 * node + 1] += val;
                lazy[2 * node + 2] += val;
            }
            return;
        }

        // Partial overlap
        int mid = (start + end) / 2;
        updateRangeUtil(2 * node + 1, start, mid, l, r, val);
        updateRangeUtil(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int queryRange(int l, int r) {
        return queryRangeUtil(0, 0, n - 1, l, r);
    }

    int queryRangeUtil(int node, int start, int end, int l, int r) {
        // Apply pending updates
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }

        // No overlap
        if (start > r || end < l) return 0;

        // Complete overlap
        if (start >= l && end <= r) return tree[node];

        // Partial overlap
        int mid = (start + end) / 2;
        int left = queryRangeUtil(2 * node + 1, start, mid, l, r);
        int right = queryRangeUtil(2 * node + 2, mid + 1, end, l, r);
        return left + right;
    }
};

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11};
    SegmentTree seg(arr);

    cout << "Initial sum (1-3): " << seg.queryRange(1, 3) << endl; // 3 + 5 + 7 = 15

    seg.updateRange(1, 3, 10); // add 10 to elements at index 1 to 3

    cout << "After update (1-3): " << seg.queryRange(1, 3) << endl; // 13 + 15 + 17 = 45

    cout << "Full range sum (0-5): " << seg.queryRange(0, 5) << endl;

    return 0;
}
