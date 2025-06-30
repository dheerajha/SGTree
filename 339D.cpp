#include <bits/stdc++.h>
using namespace std;
void build(int idx ,int low,int high,int arr[],int seg[],int orr){
    if (low == high)
    {
        seg[idx] = arr[low];
        return;
    }
    int mid = (low + high) >> 1;
    build(2*idx+1,low,mid,arr,seg,!orr);
    build(2*idx+2,mid+1,high,arr,seg,!orr);
    if(orr){
        seg[idx] = seg[2*idx+1] | seg[2*idx+2];
    }else{
        seg[idx] = seg[2*idx+1] ^ seg[2*idx+2];
    }
    

}
void update(int idx,int low,int high,int seg[],int orr,int i ,int val){
    if (low == high)
    {
        seg[idx] = val; 
        return;
    }
    int mid  = (low + high) >> 1;
    if(i <= mid){
        update(2*idx+1,low,mid,seg,!orr,i,val);
    }else{
        update(2*idx+2,mid+1,high,seg,!orr,i,val);
    }
    if(orr){
        seg[idx] = seg[2*idx+1] | seg[2*idx+2];
    }else{
        seg[idx] = seg[2*idx+1] ^ seg[2*idx+2];
    }
}
int main(){
    int n , q;
    cin >> n >> q;
    int element = pow(2,n);
    int arr[element];
    for(int i = 0 ;i< element ;i++){
        cin >> arr[i];        
    }
    int seg[4*element];
    if(n%2 == 0){
        build(0,0,element-1,arr,seg,0);    
    }else{
        build(0,0,element-1,arr,seg,1);    
    }

    while (q--)
    {
        int i,val;
        cin >> i >> val;
        i--; // for 0 based indexing 
        if(n%2 == 0){
            update(0,0,element-1,seg,0,i,val);
        }else{
            update(0,0,element-1,seg,1,i,val);

        }       
        cout << seg[0] << endl;
    }
    
}