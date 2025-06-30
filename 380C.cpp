#include <bits/stdc++.h>
using namespace std;

struct info {
    int open, close, full;

    // Default constructor
    info() {
        open = close = full = 0;
    }

    // Parameterized constructor
    info(int _open, int _close, int _full) {
        open = _open;
        close = _close;
        full = _full;
    }
};

// Merge two segment tree nodes
info merge(info left, info right) {
    int match = min(left.open, right.close);
    info ans;
    ans.full = left.full + right.full + match;
    ans.open = left.open + right.open - match;
    ans.close = left.close + right.close - match;
    return ans;
}

// Build the segment tree
void build(int ind, int low, int high, const string &s, info seg[]) {
    if (low == high) {
        seg[ind] = info(s[low] == '(', s[low] == ')', 0);
        return;
    }
    int mid = (low + high) >> 1;
    build(2 * ind + 1, low, mid, s, seg);
    build(2 * ind + 2, mid + 1, high, s, seg);
    seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
}

// Query on segment tree
info query(int ind, int low, int high, int l, int r, info seg[]) {
    if (r < low || high < l) return info(); // No overlap
    if (l <= low && high <= r) return seg[ind]; // Complete overlap
    int mid = (low + high) >> 1;
    info left = query(2 * ind + 1, low, mid, l, r, seg);
    info right = query(2 * ind + 2, mid + 1, high, l, r, seg);
    return merge(left, right);
}

int main() {
    // adding below 2 line will not give output just after the input 
    ios::sync_with_stdio(false); // Fast I/O
    cin.tie(0);

    string s;
    cin >> s;
    int n = s.size();
    info seg[4 * n];
    build(0, 0, n - 1, s, seg);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--; // 0-based indexing
        info res = query(0, 0, n - 1, l, r, seg);
        cout << res.full * 2 << '\n'; // length of longest valid subsequence
    }

    return 0;
}
