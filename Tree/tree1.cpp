
/****************** Tree Data Structure ********************

  -------> A tree is a hierarchical data structure composed of nodes connected by edges. 
          Each node contains a value and references to its child nodes. 
          Trees are widely used for representing hierarchical relationships and optimizing search operations.


---------> Important Terminologies
-> Node: Basic unit containing data and references to children
-> Root: Top node of the tree
-> Leaf: Node with no children
-> Internal Node: Node with at least one child
-> Parent/Child: Relationship between connected nodes
-> Ancestor/Descendant: Nodes in path to root/leaves
-> Height: Length of path from node to deepest leaf
-> Depth: Length of path from node to root
-> Level: Number of edges from root to node
-> Balanced Tree: Height difference of subtrees ≤ 1
-> Binary Tree: Each node has at most 2 children
-> Binary Search Tree (BST): Left subtree < node < right subtree
-> Complete Tree: All levels filled except possibly last
-> Perfect Tree: All levels completely filled  



--------> Time Complexity Analysis:
Operation	Average (BST)	 Worst (BST)	  Balanced BST
Search	       O(log n)	      O(n)	            O(log n)
Insert	       O(log n)	      O(n)	            O(log n)
Delete	       O(log n)	      O(n)	            O(log n)
Traversal	   O(n)	          O(n)	            O(n)
Height	       O(log n)	      O(n)	            O(log n)
n = number of nodes in the BST

-------> Space Complexity
Perfect Binary Tree: O(2^h) where h is height
Balanced Binary Tree: O(n) where n is number of nodes
Skewed Tree: O(n) but behaves like linked list




---------> LeetCode Questions with pattern
Tree Traversal Patterns (DFS & BFS)                         LC Questions
Pattern 1: Tree BFS - Level Order Traversal                 102. Binary Tree Level Order Traversal, 103. Binary Tree Zigzag Level Order Traversal, 199. Binary Tree Right Side View, 515. Find Largest Value in Each Tree Row, 1161. Maximum Level Sum of a Binary Tree 
Pattern 2: Tree DFS - Recursive Preorder Traversal          100. Same Tree, 101. Symmetric Tree, 105. Construct Binary Tree from Preorder and Inorder Traversal, 114. Flatten Binary Tree to Linked List, 226. Invert Binary Tree, 257. Binary Tree Paths, 988. Smallest String Starting From Leaf 
Pattern 3: Tree DFS - Recursive Inorder Traversal           94. Binary Tree Inorder Traversal, 98. Validate Binary Search Tree, 173. Binary Search Tree Iterator, 230. Kth Smallest Element in a BST, 501. Find Mode in Binary Search Tree, 530. Minimum Absolute Difference in BST 
Pattern 4: Tree DFS - Recursive Postorder Traversal         104. Maximum Depth of Binary Tree, 110. Balanced Binary Tree, 124. Binary Tree Maximum Path Sum, 145. Binary Tree Postorder Traversal, 337. House Robber III, 366. Find Leaves of Binary Tree, 543. Diameter of Binary Tree, 863. All Nodes Distance K in Binary Tree, 1110. Delete Nodes And Return Forest, 2458. Height of Binary Tree After Subtree Removal Queries 
Pattern 5: Tree - Lowest Common Ancestor (LCA) Finding      235. Lowest Common Ancestor of a Binary Search Tree, 236. Lowest Common Ancestor of a Binary Tree 
Pattern 6: Tree - Serialization and Deserialization         297. Serialize and Deserialize Binary Tree, 572. Subtree of Another Tree, 652. Find Duplicate Subtrees




******************** Implementation **********************/

// 1. Basic Tree Node
/******************************************
-> val holds the integer value of the node.
-> left and right are pointers to the left and right children.
-> Two constructors are defined:
   - One for a node with no children (default nullptr).
   - One for a node with specified left and right child pointers.*/ 

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};


// 2. Binary Search Tree Implementation
/******************************************

*/
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

public:
    BST() : root(nullptr) {}

    void insert(int val) {
        if (!root) {
            root = new TreeNode(val);
            return;
        }

        TreeNode* curr = root;
        while (true) {
            if (val < curr->val) {
                if (!curr->left) {
                    curr->left = new TreeNode(val);
                    break;
                }
                curr = curr->left;
            } else {
                if (!curr->right) {
                    curr->right = new TreeNode(val);
                    break;
                }
                curr = curr->right;
            }
        }
    }

    TreeNode* search(int val) {
        TreeNode* curr = root;
        while (curr && curr->val != val) {
            if (val < curr->val)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr;
    }

    // Optional: helper to get the root (for external access)
    TreeNode* getRoot() {
        return root;
    }
};

int main() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    TreeNode* found = tree.search(5);
    if (found) cout << "Found: " << found->val << endl;
    else cout << "Not found" << endl;

    return 0;
}





/******************* Tree Traversal Techniques **********************/

// 1. Depth-First Search (DFS)
/************************************ */

#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);
    result.push_back(root->val);
    inorder(root->right, result);
}

void preorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorder(root->left, result);
    preorder(root->right, result);
}

void postorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorder(root->left, result);
    postorder(root->right, result);
    result.push_back(root->val);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    vector<int> in, pre, post;

    inorder(root, in);
    preorder(root, pre);
    postorder(root, post);

    // Now in, pre, post contain the traversal outputs respectively
}


// 2. Breadth-First Search (Level Order Traversal (BFS))
/*****************************************************************/

#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();
        vector<int> level;

        for (int i = 0; i < level_size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
    }

    return result;
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    vector<vector<int>> bfsResult = levelOrder(root);
    
    // Output result or process as needed
}
