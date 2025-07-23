/*
    Stack Data Structure:

    A stack is a fundamental data structure that follows the Last-In-First-Out (LIFO) principle.
    Think of it like a stack of plates - you can only add or remove plates from the top.

***Important Terminologies:-
1. Stack: A LIFO (Last-In-First-Out) data structure
2. Push: Operation to add an element to the top of stack
3. Pop: Operation to remove the top element from stack
4. Peek/Top: Operation to view the top element without removing it
5. Stack Overflow: When trying to push to a full stack
6. Stack Underflow: When trying to pop from an empty stack
7. MinStack: Stack with O(1) minimum element access
8. Monotonic Stack: Stack maintaining increasing/decreasing order


****Time Complexity Analysis:-
Operation	Average Case	Worst Case
Push	        O(1)	      O(1)
Pop	            O(1)	      O(1)
Peek	        O(1)	      O(1)
Search	        O(n)	      O(n)
isEmpty	        O(1)	      O(1)

***Space Complexity:-
Basic Stack: O(n) where n is number of elements
MinStack:    O(n) for maintaining minimum values
Call Stack:  O(h) where h is recursion depth


Leetcode Questions with patterns:

Stack Patterns                                           Questions
Pattern 1: Stack - Valid Parentheses Matching            20. Valid Parentheses, 32. Longest Valid Parentheses, 921. Minimum Add to Make Parentheses Valid, 1249. Minimum Remove to Make Valid Parentheses, 1963. Minimum Number of Swaps to Make the String Balanced 
Pattern 2: Stack - Monotonic Stack                       402. Remove K Digits, 496. Next Greater Element I, 503. Next Greater Element II, 739. Daily Temperatures, 901. Online Stock Span, 907. Sum of Subarray Minimums, 962. Maximum Width Ramp, 1475. Final Prices With a Special Discount in a Shop, 1673. Find the Most Competitive Subsequence 
Pattern 3: Stack - Expression Evaluation (RPN/Infix)     150. Evaluate Reverse Polish Notation, 224. Basic Calculator, 227. Basic Calculator II, 772. Basic Calculator III 
Pattern 4: Stack - Simulation / Backtracking Helper      71. Simplify Path, 394. Decode String, 735. Asteroid Collision 
Pattern 5: Stack - Min Stack Design                      155. Min Stack 
Pattern 6: Stack - Largest Rectangle in Histogram        84. Largest Rectangle in Histogram, 85. Maximal Rectangle
*/

// ************* Implementation **************

// 1. Basic Stack Implementation 
/***********************************/
#include <bits/stdc++.h>
using namespace std;
class Stack {
private:
    vector<int> items;  // change `int` to a template if needed

public:
    void push(int item) {
        items.push_back(item);
    }

    int pop() {
        if (!is_empty()) {
            int top = items.back();
            items.pop_back();
            return top;
        }
        throw out_of_range("Pop from empty stack");
    }

    int peek() const {
        if (!is_empty()) {
            return items.back();
        }
        throw out_of_range("Peek at empty stack");
    }

    bool is_empty() const {
        return items.empty();
    }

    size_t size() const {
        return items.size();
    }
};

// 2. MinStack Implementation
/*************************************************/
// MinStack is a special type of stack that, in addition to standard push() and pop() operations, also allows you to retrieve the minimum element in the stack in constant time O(1).

#include <bits/stdc++.h>
using namespace std;
class MinStack {
private:
    std::stack<int> stack;
    std::stack<int> minStack;
public:
    // Push element onto stack
    void push(int val) {
        stack.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    // Pop element from stack
    void pop() {
        if (!stack.empty()) {
            if (stack.top() == minStack.top()) {
                minStack.pop();
            }
            stack.pop();
        }
    }
    // Get the top element
    int top() {
        if (!stack.empty())
            return stack.top();
        return INT_MIN; // or throw an exception
    }
    // Retrieve the minimum element in the stack
    int getMin() {
        if (!minStack.empty())
            return minStack.top();
        return INT_MIN; // or throw an exception
    }
};




/****************** Common Applications **************************/

// 1. Expression Evaluation
/*************************************/
// This function evaluates a Reverse Polish Notation (RPN) expression (also called postfix expression), which is a way of writing expressions without using parentheses.
#include <iostream>
using namespace std;

int evaluateRPN(vector<string>& tokens) {
    stack<int> stk;

    for (const string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int b = stk.top(); stk.pop();
            int a = stk.top(); stk.pop();
            if (token == "+") stk.push(a + b);
            else if (token == "-") stk.push(a - b);
            else if (token == "*") stk.push(a * b);
            else if (token == "/") stk.push(a / b); // integer division
        } else {
            stk.push(stoi(token)); // convert string to int
        }
    }
    return stk.top();
}



// 2. Parentheses Matching
/**************************************/
// This function checks if a given string of parentheses/brackets is balanced and valid.
#include <bits/stdc++.h>
using namespace std;

// Method - 1 
bool isValidParentheses(const string& s) {
    stack<char> stk;
    unordered_map<char, char> pairs = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    for (char ch : s) {
        if (ch == '(' || ch == '{' || ch == '[') {
            stk.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (stk.empty() || stk.top() != pairs[ch]) {
                return false;
            }
            stk.pop();
        }
    }
    return stk.empty();
}

// Method - 2
bool isValidParentheses(const string& s) {
    stack<char> st;
    for (char ch : s) {
        if(st.empty()){
            st.push(ch);
        }else if((ch==')' && st.top()=='(') || (ch=='}' && st.top()=='{') || (ch==']' && st.top()=='[')){
            st.pop();
        }else{
            st.push(ch);
        }
    }
    return st.empty();
}



/******************** Common Patterns **********************/

// 1. Monotonic Stack Pattern 
/*******************************************/
// This is a classic Monotonic Stack problem.
// It efficiently finds the next greater element to the right of each element in an array in O(n) time.
#include <bits/stdc++.h>
using namespace std;

vector<int> nextGreaterElement(const vector<int>& nums) {
    vector<int> result(nums.size(), -1);
    stack<int> stk;  // stores indices

    for (int i = 0; i < nums.size(); ++i) {
        while (!stk.empty() && nums[i] > nums[stk.top()]) {
            result[stk.top()] = nums[i];
            stk.pop();
        }
        stk.push(i);
    }
    return result;
}


// 2. Calculator Pattern
/**********************************************/
// calculate() function that uses a stack to handle expressions with +, -, and parentheses

#include <bits/stdc++.h>
using namespace std;

int calculate(const string& s) {
    stack<int> stk;
    int result = 0;
    int num = 0;
    int sign = 1; // 1 for '+', -1 for '-'

    for (size_t i = 0; i <= s.length(); ++i) {
        char ch = (i < s.length()) ? s[i] : '+'; // to process last number

        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if (ch == '+' || ch == '-') {
            result += sign * num;
            num = 0;
            sign = (ch == '+') ? 1 : -1;
        } else if (ch == '(') {
            // Push current result and sign onto stack
            stk.push(result);
            stk.push(sign);
            // Reset result and sign for the new sub-expression
            result = 0;
            sign = 1;
        } else if (ch == ')') {
            result += sign * num;
            num = 0;
            int prev_sign = stk.top(); stk.pop();
            int prev_result = stk.top(); stk.pop();
            result = prev_result + prev_sign * result;
        }
    }
    return result;
}

// eg.  cout << calculate("1 + (2 - (3 + 4))") << endl;    // Output: -4





/*
Edge Cases to Consider:

->Empty stack operations
->Stack with single element
->Stack reaching maximum capacity
->Invalid input formats
->Nested expressions
->Multiple valid solutions
->Negative numbers in calculations


Common Pitfalls:

->Forgetting to handle empty stack
->Not considering operator precedence
->Incorrect handling of negative numbers
->Stack overflow in recursion
->Not clearing stack between test cases




Interview Tips:

->Always validate input constraints
->Consider time/space complexity requirements
->Handle edge cases explicitly
->Use built-in implementations when allowed
->Consider stack variations (min stack, monotonic stack)
->Test your solution with boundary conditions
*/
