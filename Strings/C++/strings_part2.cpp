/*
Common Techniques:
***********************************************************************************

1. Sliding Window:
*************************/
#include <bits/stdc++.h>
using namespace std;

int longest_substring_without_repeating(const string& s) {
    unordered_map<char, int> char_index;
    int max_length = 0, start = 0;

    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (char_index.count(c) && char_index[c] >= start) {
            start = char_index[c] + 1;
        } else {
            max_length = max(max_length, i - start + 1);
        }
        char_index[c] = i;
    }

    return max_length;
}

// Example usage
int main() {
    string input = "abcabcbb";
    cout << "Length of longest substring without repeating: "
         << longest_substring_without_repeating(input) << endl;
    return 0;
}


/*
2. Two Pointers
****************************/
#include <bits/stdc++.h>
using namespace std;

void reverse_string(vector<char>& s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

// Example usage
int main() {
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    reverse_string(s);

    cout << "Reversed string: ";
    for (char c : s) {
        cout << c;
    }
    cout << endl;
    return 0;
}



/*
Edge Cases to Consider:
-------------------------------------
1. Empty string
2. Single character string
3. All same characters
4. Special characters
5. Unicode characters
6. Whitespace
7. Case sensitivity
8. Very long strings
9. Pattern longer than text
10. Overlapping patterns



Common Pitfalls:
--------------------------------------
1. Not handling empty strings
2. Incorrect case handling
3. Buffer overflow
4. Unicode issues
5. Inefficient concatenation
6. Memory leaks
7. Off-by-one errors
8. Incorrect boundary checks


Advanced Topics:
1.String Matching Algorithms:
      -Boyer-Moore
      -Aho-Corasick
2. Suffix Arrays/Trees:
       -Construction
       -Applications
3. Regular Expressions:
       -Pattern compilation
       -Efficient matching
4. Unicode Handling:
        -Normalization
        -Collation
5. String Distance Metrics:
        -Levenshtein
        -Hamming



Interview Tips:

1. Clarify string properties
2. Consider case sensitivity
3. Handle special characters
4. Check for constraints
5. Consider space optimization
6. Use built-in functions wisely
7. Test with edge cases
8. Consider performance
9. Handle invalid input
10.Think about scalability        
*/
