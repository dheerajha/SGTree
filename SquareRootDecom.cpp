#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class SquareRootDecom
{
    vector<int> arr,block;
    int blockSize;
public:
    SquareRootDecom(const vector<int>& input){
        arr = input;
        int n = arr.size();
        blockSize = sqrt(n) + 1;
        block.resize(blockSize,0);

        for(int i = 0 ; i < n;i++){
            block[i/blockSize] += arr[i];
        }
    }

    int query(int l,int r){
        int sum = 0;
        while (l <= r)
        {
            if(l % blockSize == 0 &&  l + blockSize - 1 <= r){
                sum += block[l / blockSize];
                l += blockSize;
            }else{
                sum += arr[l];
                ++l;
            }
        }
        return sum;
    }
   
    void update(int idx,int val){
        int blockIdx = idx / blockSize;
        block[blockIdx] += val - arr[idx];
        arr[idx] = val;
    }

};

int main() {
    vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // Example array
    SquareRootDecom sqrtDS(input);

    cout << "Sum of range [2, 6]: " << sqrtDS.query(2, 6) << endl; // 3+4+5+6+7 = 25

    sqrtDS.update(3, 10); // arr[3] = 10 instead of 4

    cout << "After update, sum of range [2, 6]: " << sqrtDS.query(2, 6) << endl; // 3+10+5+6+7 = 31

    return 0;
}
