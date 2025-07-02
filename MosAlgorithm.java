import java.util.*;
import java.io.*;

public class MosAlgorithm {
    static class Query implements Comparable<Query> {
        int l, r, idx;

        Query(int l, int r, int idx) {
            this.l = l;
            this.r = r;
            this.idx = idx;
        }

        @Override
        public int compareTo(Query other) {
            int blockA = this.l / blockSize;
            int blockB = other.l / blockSize;
            if (blockA != blockB)
                return Integer.compare(blockA, blockB);
            return Integer.compare(this.r, other.r);
        }
    }

    static int[] arr;
    static int[] freq;
    static int[] answers;
    static int distinct = 0;
    static int blockSize;

    static void add(int index) {
        freq[arr[index]]++;
        if (freq[arr[index]] == 1)
            distinct++;
    }

    static void remove(int index) {
        freq[arr[index]]--;
        if (freq[arr[index]] == 0)
            distinct--;
    }

    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt(); // size of array
        int q = sc.nextInt(); // number of queries

        arr = new int[n];
        freq = new int[1000001]; // assuming elements <= 1e6
        blockSize = (int) Math.sqrt(n);

        for (int i = 0; i < n; i++)
            arr[i] = sc.nextInt();

        Query[] queries = new Query[q];
        answers = new int[q];

        for (int i = 0; i < q; i++) {
            int l = sc.nextInt();
            int r = sc.nextInt();
            queries[i] = new Query(l, r, i);
        }

        Arrays.sort(queries);

        int l = 0, r = -1;

        for (Query query : queries) {
            while (l > query.l) add(--l);
            while (r < query.r) add(++r);
            while (l < query.l) remove(l++);
            while (r > query.r) remove(r--);

            answers[query.idx] = distinct;
        }

        for (int ans : answers)
            System.out.println(ans);
    }
}
