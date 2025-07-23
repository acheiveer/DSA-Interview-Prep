
/****************** Backtracking Algorithm ********************

  -------> Backtracking is an algorithmic technique that considers searching every possible combination in order to solve a computational problem. 
           It builds candidates to the solution incrementally and abandons candidates ("backtracks") when it determines that the candidate cannot lead to a valid solution.


---------> Important Terminologies
-> Backtracking: Algorithmic technique to find all solutions by incrementally building candidates
-> State Space Tree: Tree representing all possible states
-> Pruning: Eliminating branches that can't lead to solution
-> Constraint: Condition that must be satisfied
-> Choice Point: Point where decision is made
-> Dead End: State that can't lead to solution
-> Solution Space: Set of all possible solutions
-> Feasible Solution: Solution satisfying all constraints
-> Optimal Solution: Best solution among feasible ones
-> Decision Tree: Tree showing all possible choices     



--------> Time Complexity Analysis:
Problem Type	Time Complexity	   Space Complexity
Subsets             O(2ⁿ)	           O(n)
Permutations	    O(n!)	           O(n)
N-Queens	        O(n!)	           O(n)
Sudoku	            O(9^(n*n))	       O(n*n)
Word Search	        O(4^(n*m))	       O(n*m)
Combination Sum	    O(2^n)	           O(n)

Where n is the input size or board dimension



---------> LeetCode Questions with pattern
Backtracking Patterns                                         LC Questions
Pattern 1: Backtracking - Subsets (Include/Exclude)           17. Letter Combinations of a Phone Number, 77. Combinations, 78. Subsets, 90. Subsets II 
Pattern 2: Backtracking - Permutations                        31. Next Permutation, 46. Permutations, 60. Permutation Sequence 
Pattern 3: Backtracking - Combination Sum                     39. Combination Sum, 40. Combination Sum II 
Pattern 4: Backtracking - Parentheses Generation              22. Generate Parentheses, 301. Remove Invalid Parentheses 
Pattern 5: Backtracking - Word Search / Path Finding in Grid  79. Word Search, 212. Word Search II, 2018. Check if Word Can Be Placed In Crossword 
Pattern 6: Backtracking - N-Queens / Constraint Satisfaction  37. Sudoku Solver, 51. N-Queens 
Pattern 7: Backtracking - Palindrome Partitioning             131. Palindrome Partitioning */





/*********************** Implementation Patterns **************************/

// 1. Basic Backtracking Template
/*****************************************
  ----> A modular and extensible structure for solving backtracking problems.

  ---->You can plug in custom logic for:
-> is_solution – when to save a result.
-> get_choices – generating available options.
-> is_valid – pruning invalid paths.
-> make_choice / undo_choice – state management */

#include <iostream>
#include <vector>
using namespace std;

// Function stubs to be defined for specific problems
bool is_solution(const vector<int>& current_state) {
    // Define your own condition
    return false;
}

vector<int> get_choices(const vector<int>& input, const vector<int>& current_state) {
    // Define how to get valid choices from input
    return {};
}

bool is_valid(int choice, const vector<int>& current_state) {
    // Define constraints or checks
    return true;
}

void make_choice(int choice, vector<int>& current_state) {
    current_state.push_back(choice);
}

void undo_choice(int choice, vector<int>& current_state) {
    current_state.pop_back();
}

// Generic backtracking function
void backtrack(const vector<int>& input, vector<int>& current_state, vector<vector<int>>& result) {
    if (is_solution(current_state)) {
        result.push_back(current_state);
        return;
    }

    for (int choice : get_choices(input, current_state)) {
        if (is_valid(choice, current_state)) {
            make_choice(choice, current_state);
            backtrack(input, current_state, result);
            undo_choice(choice, current_state);
        }
    }
}



// 2. Subset Generation
/*****************************************
  ----> Generate All Subsets (Power Set)
  ----> Try every possible subset using the start index to avoid duplicates.
        This is a standard combinatorics problem to generate the power set of a given set.

  ---->Time & Space Complexity:
Time: O(2^n) – each element has 2 choices (included or not)
Space: O(n) auxiliary stack + O(2^n * n) output space */

#include <iostream>
#include <vector>
using namespace std;

// Backtracking function to generate subsets
void backtrack(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& result) {
    result.push_back(path);  // Store current subset

    for (int i = start; i < nums.size(); ++i) {
        path.push_back(nums[i]);           // Make choice
        backtrack(nums, i + 1, path, result); // Recurse
        path.pop_back();                   // Undo choice
    }
}

// Wrapper function
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    backtrack(nums, 0, path, result);
    return result;
}

int main() {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = subsets(nums);

    cout << "All subsets:\n";
    for (const auto& subset : result) {
        cout << "[";
        for (int num : subset) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    return 0;
}



// 3. Permutation Generation
/*****************************************
  ----> Permutation Generation code using backtracking with a used array:
  ----> Backtracking with a visited array to avoid reusing elements.
        Generates all n! permutations of the given array.

  ---->Time & Space Complexity:
Time: O(n!) – for all permutations
Space: O(n) recursion depth + O(n!) result storage */

#include <iostream>
#include <vector>
using namespace std;

// Backtracking function to generate permutations
void backtrack(vector<int>& nums, vector<bool>& used, vector<int>& path, vector<vector<int>>& result) {
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (used[i])
            continue;

        used[i] = true;
        path.push_back(nums[i]);
        backtrack(nums, used, path, result);
        path.pop_back();
        used[i] = false;
    }
}

// Wrapper function
vector<vector<int>> permutations(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    backtrack(nums, used, path, result);
    return result;
}

int main() {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = permutations(nums);

    cout << "All permutations:\n";
    for (const auto& perm : result) {
        cout << "[";
        for (int num : perm) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    return 0;
}


// 4. N-Queens Problem
/*****************************************
  ----> Backtracking with safety checks for placing queens on an NxN board.
  ----> Carefully verifies column and both diagonals for each new row.
        Final solutions are stored as vector of strings.

  ---->Time & Space Complexity:
Time: O(n!) – worst case, backtracking all placements
Space: O(n^2) - for the board + result storage */

#include <bits/stdc++.h>
using namespace std;

// Check if it's safe to place a queen at board[row][col]
bool is_safe(const vector<string>& board, int row, int col, int n) {
    // Check same column
    for (int i = 0; i < row; ++i)
        if (board[i][col] == 'Q')
            return false;

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
        if (board[i][j] == 'Q')
            return false;

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
        if (board[i][j] == 'Q')
            return false;

    return true;
}

// Backtracking function
void solve(int row, vector<string>& board, vector<vector<string>>& result, int n) {
    if (row == n) {
        result.push_back(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (is_safe(board, row, col, n)) {
            board[row][col] = 'Q';       // Make choice
            solve(row + 1, board, result, n); // Recurse
            board[row][col] = '.';       // Undo choice
        }
    }
}

// Wrapper function
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    solve(0, board, result, n);
    return result;
}

int main() {
    int n = 4;
    vector<vector<string>> solutions = solveNQueens(n);

    cout << "Total solutions for " << n << "-Queens: " << solutions.size() << "\n\n";
    for (const auto& solution : solutions) {
        for (const string& row : solution) {
            cout << row << "\n";
        }
        cout << "\n";
    }
    return 0;
}



// 5. Combination Sum
/*****************************************
  ----> finds all unique combinations where elements can be reused (like in Leetcode Problem 39)
  ----> Backtracking with repetition allowed (candidate numbers can be reused).
        Avoids duplicates by starting the loop from the current index.

  ---->Time & Space Complexity:
Time: Exponential in worst case, depending on depth and branching factor.
Space: O(k) for recursion stack (k = depth) and result storage. */

#include <bits/stdc++.h>
using namespace std;

// Backtracking function
void backtrack(vector<int>& candidates, int start, int target, vector<int>& path, vector<vector<int>>& result) {
    if (target < 0)
        return;
    if (target == 0) {
        result.push_back(path);
        return;
    }

    for (int i = start; i < candidates.size(); ++i) {
        path.push_back(candidates[i]);                       // Choose
        backtrack(candidates, i, target - candidates[i], path, result); // Recurse
        path.pop_back();                                     // Undo
    }
}

// Wrapper function
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> path;
    sort(candidates.begin(), candidates.end());  // Optional optimization
    backtrack(candidates, 0, target, path, result);
    return result;
}

int main() {
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;

    vector<vector<int>> result = combinationSum(candidates, target);

    cout << "Combinations that sum to " << target << ":\n";
    for (const auto& comb : result) {
        cout << "[";
        for (int num : comb) {
            cout << num << " ";
        }
        cout << "]\n";
    }

    return 0;
}
