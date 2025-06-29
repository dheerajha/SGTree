import java.util.*;
class segTree {
    int[] tree;
    int n;

    segTree(int[] arr) {
        n = arr.length;
        tree = new int[4 * n]; // safe size
        build(0, 0, n - 1, arr);
    }

    void build(int node, int start, int end, int[] arr) {
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
        if (r < start || end < l) return 0; // no overlap
        if (l <= start && end <= r) return tree[node]; // total overlap
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
}

public class SegmentTree {
    public static void main(String[] args) {
        int[] arr = {1, 3, 5, 7, 9, 11};
        segTree segTree = new segTree(arr);

        // Query sum from index 1 to 3
        System.out.println("Sum from 1 to 3: " + segTree.query(0, 0, arr.length - 1, 1, 3)); // Output: 15

        // Update index 1 to value 10
        segTree.update(0, 0, arr.length - 1, 1, 10);

        // Query again
        System.out.println("Sum from 1 to 3 after update: " + segTree.query(0, 0, arr.length - 1, 1, 3)); // Output: 22
    }
}
