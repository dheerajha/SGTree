#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree;

    SegmentTree(const vector<int>& arr) {
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
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        int leftSum = query(2 * node + 1, start, mid, l, r);
        int rightSum = query(2 * node + 2, mid + 1, end, l, r);
        return leftSum + rightSum;
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
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    int mx = -1;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        mx = max(mx, arr[i]);
    }

    mx += 1;
    vector<int> freq(mx, 0);

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    SegmentTree st(freq);
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        freq[arr[i]]--;
        st.update(0, 0, mx - 1, arr[i], freq[arr[i]]);
        cnt += st.query(0, 0, mx - 1, 0, arr[i] - 1);  // query for elements smaller than arr[i]
    }

    cout << cnt << endl;
    return 0;
}
