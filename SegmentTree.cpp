#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct SegmentTreeMin {
    vector<int> tree;
    int n;

    SegmentTreeMin(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, arr);
    }

    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid, arr);
            build(2 * node + 2, mid + 1, end, arr);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return INT_MAX;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int leftMin = query(2 * node + 1, start, mid, l, r);
        int rightMin = query(2 * node + 2, mid + 1, end, l, r);
        return min(leftMin, rightMin);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node + 1, start, mid, idx, val);
            else
                update(2 * node + 2, mid + 1, end, idx, val);
            tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }
};

int main() {
    vector<int> arr = {1, 3, -2, 8, -7, 10};
    SegmentTreeMin st(arr);

    cout << "Min from 1 to 4: " << st.query(0, 0, arr.size() - 1, 1, 4) << endl;

    st.update(0, 0, arr.size() - 1, 4, 9);

    cout << "Min from 1 to 4 after update: " << st.query(0, 0, arr.size() - 1, 1, 4) << endl;

    return 0;
}
