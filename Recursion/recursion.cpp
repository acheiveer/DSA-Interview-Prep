
/********************* Recursion in Programming 🔁 **********************
    
    Recursion is a programming concept where a function solves a problem by calling itself with smaller instances of the same problem.
    It's a powerful technique for solving problems that can be broken down into smaller, similar sub-problems.



-------> Important Terminologies

1. Base Case: Condition where recursion stops
2. Recursive Case: Function calling itself
3. Call Stack: Memory storing function calls
4. Stack Frame: Memory for single function call
5. Recursion Depth: Number of recursive calls
6. Direct Recursion: Function calls itself directly
7. Indirect Recursion: Function A calls B, B calls A
8. Tail Recursion: Recursive call is last operation
9. Tree Recursion: Multiple recursive calls
10.Nested Recursion: Recursive parameter is recursive



-------> Types of Recursion

1. Linear Recursion: One recursive call per function
2. Binary Recursion: Two recursive calls per function
3. Multiple Recursion: Multiple recursive calls
4. Mutual Recursion: Functions calling each other
5. Nested Recursion: Parameter is recursive call



------->Time and Space Complexity Analysis:
Type	      Time Complexity	     Space Complexity
Linear	            O(n)	           O(n)
Binary	            O(2^n)	           O(n)
Tail	            O(n)	            O(1)*
Tree	            O(branches^depth)	O(depth)
Nested	             Varies	            O(depth)

*Note: O(1) space for tail recursion only with proper optimization (not available in Python)



-------->> Practice Problems by Difficulty

--->Easy
-> Power of Three (LC #326)
-> Fibonacci Number (LC #509)
-> Reverse String (LC #344)

----> Medium
-> Generate Parentheses (LC #22)
-> Pow(x, n) (LC #50)
-> Subsets (LC #78)
-> Letter Combinations of a Phone Number (LC #17)

----->Hard
-> N-Queens (LC #51)
-> Regular Expression Matching (LC #10)
-> Sudoku Solver (LC #37)


******************** Implementation Patterns *********************/

// 1. Basic Linear Recursion
/************************************/
#include <iostream>
using namespace std;

// Basic linear recursion: Factorial
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

// Basic linear recursion: Fibonacci
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}



// 2. Tail Recursion: 
/************************************************
-------> Recursive calls made at the end of the function, allowing compiler optimization (in some languages like Scheme, not always in C++).

Factorial (Tail): Uses an accumulator to carry result down the recursion stack.
Fibonacci (Tail): Uses two variables to carry current and next Fibonacci values.

Time Complexity:
Factorial: O(n)
Fibonacci: O(n)

Space Complexity:
Optimally can be O(1) if compiler does tail-call optimization; otherwise, O(n)*/

#include <iostream>
using namespace std;

// Tail-recursive factorial
int factorial_tail(int n, int accumulator = 1) {
    if (n <= 1)
        return accumulator;
    return factorial_tail(n - 1, n * accumulator);
}

// Tail-recursive Fibonacci
int fibonacci_tail(int n, int a = 0, int b = 1) {
    if (n == 0)
        return a;
    return fibonacci_tail(n - 1, b, a + b);
}



// 3. Binary Recursion (Divide and Conquer)
/****************************************************
-----> merge_sort implementation

Binary Recursion – Divide the array into halves recursively and merge sorted halves.

Time Complexity: O(nlogn)
Space Complexity: O(n) – Due to creation of subarrays

Use Case: Efficient, stable sorting algorithm for large datasets. Suitable when stability is needed.*/
#include <bits/stdc++.h>
using namespace std;

// Merge two sorted arrays
vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> result;
    int i = 0, j = 0;
    // Merge step
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    // Append remaining elements
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    return result;
}

// Merge sort using binary recursion
vector<int> merge_sort(const vector<int>& arr) {
    if (arr.size() <= 1)
        return arr;

    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

int main() {
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 6};
    vector<int> sorted = merge_sort(arr);
    cout << "Sorted array: ";
    for (int num : sorted)
        cout << num << " ";
    cout << endl;
    return 0;
}



// 4. Tree Recursion
/***********************************
 ----> A recursive function that calls itself more than once per call, forming a tree-like structure of recursive calls.

1. Binary String Generation
Use Case: Useful for generating combinations, subsets, etc.
Time Complexity: (2^n)

2. String Permutations
Use Case: Classical backtracking/recursion problem for interviews.
Time Complexity: O(n!) */

#include <iostream>
using namespace std;

// Tree Recursion: Print all binary strings of length n
void print_binary_strings(int n, string str = "") {
    if (str.length() == n) {
        cout << str << endl;
        return;
    }

    print_binary_strings(n, str + "0");
    print_binary_strings(n, str + "1");
}

// Tree Recursion: Generate all permutations of a string
void generate_permutations(string str, string prefix = "") {
    if (str.length() == 0) {
        cout << prefix << endl;
        return;
    }

    for (int i = 0; i < str.length(); i++) {
        string rem = str.substr(0, i) + str.substr(i + 1);
        generate_permutations(rem, prefix + str[i]);
    }
}

int main() {
    int n = 3;
    cout << "All binary strings of length " << n << ":\n";
    print_binary_strings(n);

    string s = "abc";
    cout << "\nAll permutations of \"" << s << "\":\n";
    generate_permutations(s);

    return 0;
}


// 5. Memoization with Recursion
/***********************************
------> Memoization (Top-Down Dynamic Programming):
1. Stores the result of each subproblem to avoid repeated computation.
2. Uses unordered_map (or vector if size is fixed) to cache intermediate results.

Time Complexity:
----> O(n) — each fibonacci(n) is computed only once
----> O(n) space for memo table */

#include <iostream>
#include <unordered_map>
using namespace std;

// Memoized Fibonacci using recursion
int fibonacci_memo(int n, unordered_map<int, int>& memo) {
    if (memo.find(n) != memo.end())
        return memo[n];

    if (n <= 1)
        return n;

    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo);
    return memo[n];
}

int main() {
    int n = 10;
    unordered_map<int, int> memo;
    cout << "Fibonacci(" << n << ") = " << fibonacci_memo(n, memo) << endl;
    return 0;
}




/******************** Common Techniques ********************

 1. Backtracking Template 
 *************************************
   ----> Used in problems like: Combination Sum, Subset Sum, Word Search, N-Queens, etc.
   ----> Try every option → backtrack if it doesn’t work

Time Complexity:
Worst case: exponential O(2^n), depending on branching factor and depth
Efficient pruning is key to optimization */

#include <iostream>
#include <vector>
using namespace std;

// Backtracking function
void backtrack(vector<int>& candidates, int target, vector<int>& path, vector<vector<int>>& results) {
    if (target < 0)
        return;
    if (target == 0) {
        results.push_back(path);
        return;
    }

    for (int i = 0; i < candidates.size(); i++) {
        path.push_back(candidates[i]);
        // Allow reuse of the same element, so pass candidates from i (not i+1)
        vector<int> newCandidates(candidates.begin() + i, candidates.end());
        backtrack(newCandidates, target - candidates[i], path, results);
        path.pop_back();
    }
}

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> results;
    vector<int> path;

    backtrack(candidates, target, path, results);

    cout << "Combinations that sum to " << target << ":\n";
    for (const auto& comb : results) {
        for (int num : comb) {
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}



/* 2. Tree Traversal
******************************************
---> Pre-order Traversal (Root → Left → Right)
---> Base structure for other DFS traversals (in-order, post-order)
---> Recursion over binary tree nodes*/

#include <iostream>
using namespace std;

// Definition of a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x){
        val = x;
        left = nullptr;
        right = nullptr;
    } 
};

// Pre-order Tree Traversal
void tree_traversal(TreeNode* root) {
    if (!root)
        return;

    // Pre-order: Visit -> Left -> Right
    cout << root->val << " ";
    tree_traversal(root->left);
    tree_traversal(root->right);
}

int main() {
    // Creating a sample tree:
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    cout << "Pre-order Traversal: ";
    tree_traversal(root);  // Output: 1 2 4 5 3
    cout << endl;

    return 0;
}








/*--->Edge Cases to Consider:

1. Base case not reached
2. Stack overflow
3. Negative or zero input
4. Empty input
5. Single element input
6. Maximum recursion depth
7. Circular dependencies
8. Duplicate calculations
9. Large input causing deep recursion
10. Memory constraints


---->Common Pitfalls:

1. Missing base case
2. Incorrect base case
3. Infinite recursion
4. Not handling edge cases
5. Inefficient recursive solution
6. Stack overflow
7. Redundant calculations
8. Memory leaks



----> Interview Tips:
1. Always identify base cases first
2. Consider time/space complexity
3. Look for recursive patterns
4. Consider iterative alternatives
5. Handle edge cases explicitly
6. Use visualization for complex cases
7. Consider memoization
8. Test with small examples
9. Discuss optimization possibilities
10. Consider stack limitations
*/
