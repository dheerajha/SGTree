import java.util.*;
public class XaniaBit{
    public static void build(int idx,int low,int high,int[] arr,int[] seg,boolean or){
        if(low == high){
            seg[idx] = arr[low];
            return;
        }
        int mid = (low + high) >> 1; 
        build(2*idx+1, low, mid, arr, seg, !or);
        build(2*idx+2, mid+1, high, arr, seg, !or);
        if (or) {
            seg[idx] = seg[2*idx + 1] | seg[2*idx+2];
        }else{
            seg[idx] = seg[2*idx + 1] ^ seg[2*idx+2];
        }
    }
    public static void update(int idx,int low,int high,int[] seg,boolean or,int i,int val){
        if (low == high) {
            seg[idx] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if (i <= mid) {
            update(2*idx+1, low, mid, seg, !or, i, val);
        }else{
            update(2*idx+2, mid+1, high, seg, !or, i, val);
        }
        if (or) {
            seg[idx] = seg[2*idx + 1] | seg[2*idx+2];
        }else{
            seg[idx] = seg[2*idx + 1] ^ seg[2*idx+2];
        }
        
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int q = sc.nextInt();
        int element = (int) Math.pow(2, n);
        int[] arr = new int[element];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = sc.nextInt();
        }
        int[] sgt = new int[4*element];
        if(n % 2 == 0){
            build(0, 0, element -1, arr, sgt, false);
        }else{
            build(0, 0, element -1, arr, sgt, true);
        }

        while (q-- > 0) {
            int i = sc.nextInt();
            int val = sc.nextInt();
            i--; // for making it 0 based indexing 
            if (n%2 == 0) {
                update(0,0, element-1, sgt, false, i, val);
            }else{
                update(0, 0, element-1, sgt, true, i, val);
            }
            System.out.println(sgt[0]);
        }
        sc.close();
    } 
}