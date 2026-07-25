#include <stdio.h>
#include <stdlib.h>
int main(){

    // time complexity: O(n^2)
    // It fails for large inputs, as it has a time complexity of O(n^2). A more efficient approach would be to use a sliding window technique to achieve O(n) time complexity.

    // for time complexity: O(n)
    int longest_block(int*a,int n,long long L){
        int best=0;
        int left=0;
        int sum=0;
       
        for (int right=0;right<n;right++){
            sum+=a[right];
            while (sum>L){
                sum-=a[left];
                left++;
            }
            if (right-left+1>best){
                best=right-left+1;
            }
        }
        return best;
    }
}

// In this code, we use a sliding window approach to find the longest contiguous subarray whose sum is less than or equal to L. We maintain two pointers, left and right, to represent the current window of elements being considered. As we iterate through the array with the right pointer, we add the current element to the sum. If the sum exceeds L, we move the left pointer to the right until the sum is less than or equal to L again. We keep track of the maximum length of valid windows found during this process.
 