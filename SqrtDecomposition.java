import java.util.*;

class SqrtDecomposition {
    int[] arr;       // Original array
    int[] blocks;    // Array to store block sums
    int blockSize;   // Size of each block

    // Constructor: O(n)
    public SqrtDecomposition(int[] input) {
        int n = input.length;
        arr = new int[n];
        System.arraycopy(input, 0, arr, 0, n);

        blockSize = (int) Math.sqrt(n) + 1;
        blocks = new int[blockSize];

        // Preprocess block sums
        for (int i = 0; i < n; i++) {
            blocks[i / blockSize] += arr[i];
        }
    }

    // Query sum from l to r: O(√n)
    public int query(int l, int r) {
        int sum = 0;
        while (l <= r) {
            if (l % blockSize == 0 && l + blockSize - 1 <= r) {
                // Whole block can be taken
                sum += blocks[l / blockSize];
                l += blockSize;
            } else {
                // Process one element
                sum += arr[l];
                l++;
            }
        }
        return sum;
    }

    // Update value at index: O(1)
    public void update(int index, int value) {
        int blockIndex = index / blockSize;
        blocks[blockIndex] += value - arr[index];
        arr[index] = value;
    }
    public static void main(String[] args) {
        int[] input = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        SqrtDecomposition sqrt = new SqrtDecomposition(input);

        System.out.println("Sum from 2 to 6: " + sqrt.query(2, 6)); // 3+4+5+6+7 = 25

        sqrt.update(3, 10); // arr[3] = 10 instead of 4

        System.out.println("After update, sum from 2 to 6: " + sqrt.query(2, 6)); // 3+10+5+6+7 = 31
    }
}
