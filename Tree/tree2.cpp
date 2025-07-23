
/******************* Common Techniques **********************/

// 1. Lowest Common Ancestor (LCA)
/************************************ 
 -----> The Lowest Common Ancestor (LCA) of two nodes p and q in a binary tree is the lowest 
        (i.e., deepest) node that has both p and q as descendants (a node can be a descendant of itself).

------> How It Works (Step-by-Step)
1. Base Cases:
   -> If the root is nullptr, return nullptr.
   -> If the root matches either p or q, return the root.

2. Recursive Search:
   -> Call the function recursively on the left and right subtrees.

3. LCA Determination:
   -> If both recursive calls return non-null values, it means p and q are found on different sides, so the current root is the LCA.
   -> If only one is non-null, propagate that result upwards.

------> Key Properties:
   -> Works on any binary tree (not just BST).
   -> Time complexity: O(N), where N is the number of nodes.
   -> Space complexity: O(H) due to recursion stack, where H is the tree height. */


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q)
        return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right)
        return root;

    return left ? left : right;
}
   


// 2. Path Sum
/***********************************
----> This function checks whether there's any root-to-leaf path in a binary tree such that the sum of the node values equals targetSum.

---->Step-by-Step:
1. Base Case 1: If the root is nullptr, return false — no path exists.
2. Base Case 2 (Leaf Check):
    -> If the current node is a leaf node (no children), check if its value equals the remaining targetSum.
3. Recursive Step:
    -> Subtract the current node's value from the targetSum, and recursively check in left and right subtrees.


----->Use Cases
1.Common coding interview problem.
2. Used in decision trees to check if certain cumulative values are achievable.
3. Can be extended to return all such paths (e.g., using backtracking).    


----->Complexity
Time Complexity: O(N), where N is the number of nodes — each node is visited once.
Space Complexity: O(H), where H is the height of the tree (due to recursion stack).    */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;

    // If it's a leaf node
    if (!root->left && !root->right)
        return root->val == targetSum;

    // Recurse on left and right subtrees
    return hasPathSum(root->left, targetSum - root->val) ||
           hasPathSum(root->right, targetSum - root->val);
}


// 3. Tree Validation
/***********************************
----> This function checks whether a given binary tree is a valid Binary Search Tree (BST).

---->BST Conditions:
1. For every node:
    -> All values in the left subtree must be strictly less than the node's value.
    -> All values in the right subtree must be strictly greater than the node's value.
2. This is enforced using range limits (minVal and maxVal) that change as recursion proceeds.

-----> Flow:
1. Start with the range (-∞, ∞).
2. As we go left, we update the maxVal to the current node's value.
3. As we go right, we update the minVal to the current node's value.
4. At each step, we check if the current node violates the range constraints

----->Use Cases
1. Validate if a binary tree is a BST — crucial in interview questions.
2. Used in binary search tree rebalancing algorithms or database indexing systems.
3. Useful in unit testing of tree-based algorithms. 


----->Complexity
Time Complexity: O(N), where N is the number of nodes — each node is visited once.
Space Complexity: O(H), where H is the height of the tree (recursion stack).    */

#include<bits/stdc++.h>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool isValidBST(TreeNode* root, long minVal = LONG_MIN, long maxVal = LONG_MAX) {
    if (!root) return true;

    if (root->val <= minVal || root->val >= maxVal)
        return false;

    return isValidBST(root->left, minVal, root->val) &&
           isValidBST(root->right, root->val, maxVal);
}





/* -----> Edge Cases to Consider:

-> Empty tree
-> Single node tree
-> Complete binary tree
-> Perfect binary tree
-> Skewed tree (left/right)
-> Duplicate values
-> Negative values
-> Maximum/minimum values
-> Unbalanced tree
-> Tree with cycles (invalid)



------> Common Pitfalls

-> Not handling null nodes
-> Incorrect recursion base cases
-> Stack overflow in deep trees
-> Not considering duplicates
-> Assuming balanced tree
-> Incorrect BST validation
-> Memory leaks in deletion



-------> Interview Tips

-> Clarify tree type and properties
-> Consider recursive vs iterative approaches
-> Analyze space complexity (recursion stack)
-> Handle edge cases explicitly
-> Use helper functions for complex logic
-> Consider in-place vs new tree solutions
-> Test with small examples first
-> Draw the tree for visualization



------> Real-World Applications

-> File Systems: Directory structure
-> HTML DOM: Web page structure
-> Database Indexing: B-trees and variants
-> Compiler Design: Abstract syntax trees
-> Network Routing: Routing tables
-> AI/Game Theory: Decision trees
-> Compression: Huffman coding

*/