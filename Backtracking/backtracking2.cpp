
/*********************** Common Techniques **************************/

// 1. State Management
/*****************************************
  ----> Managing state is a foundational technique in backtracking, and what written represents one of the core patterns: tracking current progress (choices) and used elements (used set).
  ----> Maintain a snapshot of the current state to decide whether to proceed, prune, or backtrack. */

#include <vector>
#include <unordered_set>

class State {
private:
    std::vector<int> choices;
    std::unordered_set<int> used;

public:
    // Make a choice: Add to choices and mark as used
    void make_choice(int choice) {
        choices.push_back(choice);
        used.insert(choice);
    }

    // Undo the last choice: Remove from choices and used set
    void undo_choice() {
        if (!choices.empty()) {
            int choice = choices.back();
            choices.pop_back();
            used.erase(choice);
        }
    }

    // Check if a choice is valid (not used yet)
    bool is_valid(int choice) const {
        return used.find(choice) == used.end();
    }

    // Optional: Access current choices
    const std::vector<int>& get_choices() const {
        return choices;
    }
};

/*-----> Explanations

choices: Maintains the current sequence of decisions made.
used: Keeps track of elements already included to avoid repetition.
make_choice: Simulates committing to a decision.
undo_choice: Helps backtrack the previous decision (important in recursion).
is_valid: Helps prune invalid paths early in the search space.

---> Use Cases in DSA
1. Backtracking problems like:
    --Permutations without repetition
    --N-Queens
    --Sudoku Solver
2. DFS with path tracking (e.g., word search or graph traversal with constraints)
3. Generating combinations or subsets while avoiding duplicates


Q.  Generate all permutations of a list of distinct integers, and we'll use the State class for managing choice */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// State class to manage choices and used elements
class State {
private:
    vector<int> choices;
    unordered_set<int> used;

public:
    void make_choice(int choice) {
        choices.push_back(choice);
        used.insert(choice);
    }

    void undo_choice() {
        int choice = choices.back();
        choices.pop_back();
        used.erase(choice);
    }

    bool is_valid(int choice) const {
        return used.find(choice) == used.end();
    }

    const vector<int>& get_choices() const {
        return choices;
    }
};

// Backtracking function to generate permutations
void backtrack(State& state, vector<int>& nums, vector<vector<int>>& result) {
    if (state.get_choices().size() == nums.size()) {
        result.push_back(state.get_choices());
        return;
    }

    for (int num : nums) {
        if (state.is_valid(num)) {
            state.make_choice(num);             // Choose
            backtrack(state, nums, result);     // Explore
            state.undo_choice();                // Unchoose (backtrack)
        }
    }
}

int main() {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result;
    State state;

    backtrack(state, nums, result);

    // Output the result
    cout << "Permutations of [1, 2, 3]:" << endl;
    for (const auto& perm : result) {
        for (int n : perm)
            cout << n << " ";
        cout << endl;
    }

    return 0;
}




// 1. Pruning Optimization
/*****************************************
  ----> This is the "Combination Sum II" problem where each number in candidates can be used at most once, and we aim to find all unique combinations that sum to a given target.
  ----> *This is used for problems like "Combination Sum II" where:
        1. You must find combinations that sum to a target
        2. Each number may be used at most once
        3. Input can have duplicates, so you need to skip over duplicates to avoid duplicate results.*/
        #include <iostream>
#include <vector>
#include <algorithm>

void backtrack_with_pruning(const std::vector<int>& candidates, int target, std::vector<int>& path, int start, std::vector<std::vector<int>>& result) {
    if (target < 0) return; // Prune paths that exceed the target
    if (target == 0) {
        result.push_back(path);
        return;
    }

    for (int i = start; i < candidates.size(); ++i) {
        // Skip duplicates
        if (i > start && candidates[i] == candidates[i - 1])
            continue;

        // Prune if current number is too large
        if (candidates[i] > target)
            break;

        path.push_back(candidates[i]);
        backtrack_with_pruning(candidates, target - candidates[i], path, i + 1, result);
        path.pop_back();
    }
}

std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
    std::sort(candidates.begin(), candidates.end()); // Important for skipping duplicates and pruning
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    backtrack_with_pruning(candidates, target, path, 0, result);
    return result;
}

int main() {
    std::vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    std::vector<std::vector<int>> results = combinationSum2(candidates, target);

    std::cout << "Combinations that sum to " << target << ":\n";
    for (const auto& combo : results) {
        for (int num : combo)
            std::cout << num << " ";
        std::cout << "\n";
    }

    return 0;
}




/*
-----> Edge Cases to Consider

-> Empty input
-> Single element input
-> Duplicate elements
-> No solution exists
-> Multiple solutions
-> Maximum recursion depth
-> Large input size
-> All elements same
-> Negative numbers
-> Boundary conditions



-------> Common Pitfalls

-> Not handling base cases
-> Incorrect state management
-> Missing pruning opportunities
-> Infinite recursion
-> Memory overflow
-> Not copying state properly
-> Incorrect constraint checking
-> Inefficient pruning



-----> Interview Tips

-> Identify problem constraints
-> Draw state space tree
-> Consider pruning opportunities
-> Handle base cases properly
-> Manage state carefully
-> Consider optimization techniques
-> Test with small examples
-> Analyze time complexity
-> Consider space optimization
-> Discuss trade-offs
*/