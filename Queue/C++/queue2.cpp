
/******************* Common Applications of Queue ***********************

1. BFS Implementation
***************************************/
#include <bits/stdc++.h>
using namespace std;

void bfs(const unordered_map<int, vector<int>>& graph, int start) {
    unordered_set<int> visited;
    queue<int> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        cout << vertex << " ";

        for (int neighbor : graph.at(vertex)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}


/* 2. Sliding Window Maximum
******************************************
using a deque, which maintains indices for efficient maximum lookups
The deque holds indices, not values.

It ensures:
-> The front always holds the index of the max element in the current window.
-> Elements out of the window's range are removed from the front.
-> Elements smaller than the current one are removed from the back (they can't be max anymore).*/
#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
    deque<int> window;
    vector<int> result;

    for (int i = 0; i < nums.size(); ++i) {
        // Remove indices outside the current window
        while (!window.empty() && window.front() < i - k + 1) {
            window.pop_front();
        }

        // Remove indices of all elements smaller than current element
        while (!window.empty() && nums[window.back()] < nums[i]) {
            window.pop_back();
        }

        // Add current index
        window.push_back(i);

        // Add the max element to result once the window is of size k
        if (i >= k - 1) {
            result.push_back(nums[window.front()]);
        }
    }

    return result;
}





/******************* Common Patterns ***********************

1. Level Order Traversal (using a queue)
***************************************/
#include <bits/stdc++.h>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
    val = x;
    left = nullptr;
    right = nullptr;
    }
};

vector<vector<int>> levelOrderTraversal(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level;

        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        result.push_back(level);
    }
    return result;
}


/*2. Task Scheduling
**************************************
The task_scheduling function referring to solves the Task Scheduler problem, where we need to schedule tasks with a cooldown period (n).
Q. What problem does it solve?
Ans - Given a list of tasks (like ["A", "A", "A", "B", "B", "B"]) and a cooldown n, 
      the goal is to return the minimum time (in units) to finish all tasks such that same tasks are at least n units apart. */
#include <bits/stdc++.h>
using namespace std;
int taskScheduling(const vector<char>& tasks, int n) {
    unordered_map<char, int> counter;

    for (char task : tasks) {
        counter[task]++;
    }

    int max_freq = 0;
    for (auto& pair : counter) {
        max_freq = max(max_freq, pair.second);
    }

    int max_freq_tasks = 0;
    for (auto& pair : counter) {
        if (pair.second == max_freq) {
            max_freq_tasks++;
        }
    }

    return max((int)tasks.size(), (max_freq - 1) * (n + 1) + max_freq_tasks);
}





/*Edge Cases to Consider:

-> Empty queue operations
-> Queue with single element
-> Queue reaching maximum capacity
-> Circular queue wrap-around
-> Priority conflicts in priority queue
-> Deque operations at both ends
-> Multiple elements with same priority



Common Pitfalls:

-> Not handling empty queue
-> Incorrect circular queue indexing
-> Memory leaks in custom implementations
-> Not maintaining FIFO order
-> Inefficient array-based implementation*/