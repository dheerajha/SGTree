public class FenwickTree {
    private int[] bit;
    int n ;

    public FenwickTree(int n){
        this.n = n;
        bit = new int[n+1]; //1 based index
    }

    public void update(int i,int val){
        while (i < n) {
            bit[i] += val;
            i += (i & -i); // move to the next index
        }
    }

    // get prefix from 1 to i
    public int query(int i){
        int sum = 0 ;
        while (i> 0) {
            sum += bit[i];
            i -= (i & -i);
        }
        return sum;
    }

    // get sum in range (l,r)
    public int rangeQuery(int l,int r){
        return query(r) - query(l-1);
    }
    public static void main(String[] args) {
        FenwickTree ft = new FenwickTree(10);

        ft.update(3, 5); // Add 5 at index 3
        ft.update(7, 2); // Add 2 at index 7
        ft.update(1, 4); // Add 4 at index 1

        System.out.println("Prefix sum up to index 3: " + ft.query(3));      // Output: 9
        System.out.println("Range sum from index 3 to 7: " + ft.rangeQuery(3, 7)); // Output: 7
    }
}
