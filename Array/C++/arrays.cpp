/* Arrays in Data Structures and Algorithms

Arrays - Arrays are the fundamental data structures that stores elements in contiguous memory location. They are the building block for many
        data structures and Alorithms.

Some Terminologies: 
           1. Array: Collection of elements stored at contiguous memory location
           2. SubArray: Contiguous element with in an array (e.g [1,2,3] in [1,2,3,4])
           3. SubSequence: Non-Contiguous element maintaining relative order (e.g [1,3,4] in [1,2,3,4])
           4. Bitonic Array: Array which first increase and decreases (e.g., [1,3,5,4,2])
           5. Circular Array: Array where we consider the first element as next to the last element


Time Complexity Analysis:
Operation	Average Case	Worst Case
Access	        O(1)	    O(1)
Search	        O(n)	    O(n)
Insertion	    O(n)	    O(n)
Deletion	    O(n)	    O(n)
Sort	       O(n log n)	O(n²)

Space Complexity:
Linear Arrays: O(n) where n is the size of array
2D Arrays:     O(m×n) where m and n are dimensions

*****************************************************************************
Commom Techniques:

1. Two Pointer: Used when dealing with soretd arrays or pairs in arrays
                                                                                LeetCode Questions
              Pattern 1: Two Pointers - Converging (Sorted Array Target Sum) :  1. Two Sum, 11. Container With Most Water, 15. 3Sum, 16. 3Sum Closest, 18. 4Sum, 167. Two Sum II - Input Array Is Sorted, 349. Intersection of Two Arrays, 881. Boats to Save People, 977. Squares of a Sorted Array, 259. 3Sum Smaller
              Pattern 2: Two Pointers - Fast & Slow (Cycle Detection):          141. Linked List Cycle, 202. Happy Number, 287. Find the Duplicate Number, 392. Is Subsequence, 
              Pattern 3: Two Pointers - Fixed Separation (Nth Node from End):   19. Remove Nth Node From End of List, 876. Middle of the Linked List, 2095. Delete the Middle Node of a Linked List 
              Pattern 4: Two Pointers - In-place Array Modification:            26. Remove Duplicates from Sorted Array, 27. Remove Element, 75. Sort Colors, 80. Remove Duplicates from Sorted Array II, 283. Move Zeroes, 443. String Compression, 905. Sort Array By Parity, 2337. Move Pieces to Obtain a String, 2938. Separate Black and White Balls 
              Pattern 5: Two Pointers - String Comparison with Backspaces:      844. Backspace String Compare 
              Pattern 6: Two Pointers - Expanding From Center (Palindromes):    5. Longest Palindromic Substring, 647. Palindromic Substrings Pattern 7: Two Pointers - String Reversal 151. Reverse Words in a String, 344. Reverse String, 345. Reverse Vowels of a String, 541. Reverse String II
*/

//1. Two Sum
#include<bits/stdc++.h>
using namespace std;
class solution{
    public:
    vector<int> twoSum(vector<int>& nums, int target){
        int left=0;
        int right=nums.size()-1;
        while(left<right){
            int curr_sum = nums[left]+nums[right];
            if(curr_sum==target){
                return {left,right};
            }else if(curr_sum<target){
                left++;
            }else{
                right--;
            }
        }
        return {};
    }
};

/*Note: Make sure nums is sorted, as the two-pointer technique only works correctly on sorted arrays.
  Note: If the original input isn't sorted and you need original indices, you'd need a different approach (like a hashmap or sorting with tracking indices)


2. Sliding Window: Useful for problems involving contiguous subarrays.
                   Pattern 1: Sliding Window - Fixed Size (Subarray Calculation)    346. Moving Average from Data Stream, 643. Maximum Average Subarray I, 2985. Calculate Compressed Mean, 3254. Find the Power of K-Size Subarrays I, 3318. Find X-Sum of All K-Long Subarrays I 
                   Pattern 2: Sliding Window - Variable Size (Condition-Based)      3. Longest Substring Without Repeating Characters, 76. Minimum Window Substring, 209. Minimum Size Subarray Sum, 219. Contains Duplicate II, 424. Longest Repeating Character Replacement, 713. Subarray Product Less Than K, 904. Fruit Into Baskets, 1004. Max Consecutive Ones III, 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit, 1493. Longest Subarray of 1's After Deleting One Element, 1 1658. Minimum Operations to Reduce X 
                   Pattern 3: Sliding Window - Monotonic Queue for Max/Min          239. Sliding Window Maximum, 862. Shortest Subarray with Sum at Least K, 1696. Jump Game VI 
                   Pattern 4: Sliding Window - Character Frequency Matching         438. Find All Anagrams in a String, 567. Permutation in String  */

#include<bits/stdc++.h>
using namespace std;
class solution{
    public:
    int maxSumSubarray(const vector<int>& nums, int k) {
    // Calculate the sum of the first 'k' elements
    int window_sum = accumulate(nums.begin(), nums.begin() + k, 0);
    int max_sum = window_sum;

    for (int i = 0; i < nums.size() - k; ++i) {
        window_sum = window_sum - nums[i] + nums[i + k];
        max_sum = std::max(max_sum, window_sum);
    }

    return max_sum;
   }
};     



// 3.Prefix Sum: Optional for range queries and cumulative computation
#include<bits/stdc++.h>
using namespace std;
class solution{
    public:
    vector<int> buildPrefixSum(const vector<int>& nums) {
    vector<int> prefix(nums.size() + 1, 0);
    
    for (int i = 0; i < nums.size(); ++i) {
        prefix[i + 1] = prefix[i] + nums[i];
    }

    return prefix;
   }
};     


/* 4. Kadane's Algorithm: For maximum subArray problem
                        (used to find the maximum sum of a contiguous subarray in a one-dimensional array of numbers (can be positive, negative, or both)
                        time complexity of O(n) and space complexity of O(1).*/

#include<bits/stdc++.h>
using namespace std;
class solution{
    public:
   int kadane(const vector<int>& nums) {
    int max_sum = nums[0];
    int current_sum = nums[0];

    for (size_t i = 1; i < nums.size(); ++i) {
        current_sum = max(nums[i], current_sum + nums[i]);
        max_sum = max(max_sum, current_sum);
    }

    return max_sum;
}

};              


/*
Edge Cases to Consider:
->Empty array
->Array with single element
->Array with all negative values
->Array with duplicates
->Array with overflow potential
->Sorted vs unsorted arrays
->Circular array scenarios
*/
