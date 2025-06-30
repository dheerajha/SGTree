// User function Template for Java
import java.util.*;;
class Solution {
    static int merge(int[] arr,int low,int mid,int high){
        ArrayList<Integer> temp = new ArrayList<>();
        int left = low;
        int right = mid+1;
        
        // modification 1
        int cnt = 0 ;
        
        while(left <= mid && right <= high){
            if(arr[left] <= arr[right]){
                temp.add(arr[left]);
                left++;
            }else{
                temp.add(arr[right]);
                cnt += (mid - left +1); // modification 2
                right++;
            }
        }
        
        // if element on the left are still left
        while(left <= mid){
            temp.add(arr[left]);
            left++;
        }
        // if element on the right are still left
        while(right <= high){
            temp.add(arr[right]);
            right++;
        }
        
        // transfering all the element  from temp to arr
        for(int i = low; i <= high ; i++){
            arr[i] = temp.get(i-low);
        }
        return cnt; //modification 3
    }
    static int mergeSort(int[] arr,int low,int high){
        int cnt = 0;
        if(low >= high) return cnt;
        int mid = (low + high) >> 1;
        cnt += mergeSort(arr,low,mid);
        cnt += mergeSort(arr,mid+1,high);
        cnt += merge(arr,low,mid,high);
        return cnt;
    }
    // Function to count inversions in the array.
    static int inversionCount(int arr[]) {
        // Your Code Here
        int n = arr.length;
        return mergeSort(arr,0,n-1);
    }
}