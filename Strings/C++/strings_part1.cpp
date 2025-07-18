/*
String Algorithms and Techniques: 

String manipulation and pattern matching are fundamental concepts in computer science.
A strong understanding of string algorithms is essential for tasks such as text processing, pattern recognition, and various real-world applications, including text editors, compilers, and search engines.

Important Terminologies:
->String:         Sequence of characters
->Substring:      Contiguous sequence within string
->Subsequence:    Characters in order (not necessarily contiguous)
->Prefix:         Beginning part of string
->Suffix:         Ending part of string
->Pattern:        String to search for
->Text:           String to search in
->Palindrome:     Reads same forward and backward
->Anagram:        Same characters in different order
->Rolling Hash:   Hash that updates efficiently
->Edit Distance:  Minimum operations to transform string


String Properties
->Immutability: Strings may be immutable (language dependent)
->Indexing: Zero-based access to characters
->Length: Number of characters
->Character Set: ASCII, Unicode, etc.
->Case Sensitivity: Upper vs lowercase


Time Complexity Analysis
Operation	          Average Case	Worst Case
Access	                O(1)	      O(1)
Search	                O(n)	      O(n)
Insert/Delete           O(n)	      O(n)
Concatenate	            O(n+m)	      O(n+m)
Pattern Match (Naive)	O(nm)	      O(nm)
Pattern Match (KMP)	    O(n+m)	      O(n+m)
Rabin-Karp	            O(n+m)	      O(nm)

Where:
n = length of text
m = length of pattern


String Manipulation Patterns 
                                                                    LeetCode Questions
Pattern 1: String - Palindrome Check (Two Pointers / Reverse)       9. Palindrome Number, 125. Valid Palindrome, 680. Valid Palindrome II 
Pattern 2: String - Anagram Check (Frequency Count/Sort)            49. Group Anagrams, 242. Valid Anagram
Pattern 3: String - Roman to Integer Conversion                     13. Roman to Integer 
Pattern 4: String - String to Integer (atoi)                        8. String to Integer (atoi) 
Pattern 5: String - Multiply Strings (Manual Simulation)            43. Multiply Strings 
Pattern 6: String - Matching - Naive / KMP / Rabin-Karp 2           8. Find the Index of the First Occurrence in a String, 214. Shortest Palindrome, 686. Repeated String Match, 796. Rotate String, 3008. Find Beautiful Indices in the Given Array II 
Pattern 7: String - Repeated Substring Pattern Detection            459. Repeated Substring Pattern 

******************************************************************************************************************************
Implementation Patterns:

1. String Matching (KMP Algorithm): 
************************************** */

// KMP is used for string pattern matching. It efficiently finds all occurrences of a pattern string in a text string in linear time, O(n + m), where:

// n is the length of the text
// m is the length of the pattern
// It avoids unnecessary comparisons by precomputing a helper array called LPS (Longest Prefix which is also Suffix).


#include <bits/stdc++.h>
using namespace std;

// Equivalent of compute_lps(pattern) in C++
vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int length = 0; // length of the previous longest prefix suffix

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // fallback
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Equivalent of kmp_search(text, pattern) in C++
vector<int> kmpSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> lps = computeLPS(pattern);
    vector<int> indices;

    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            indices.push_back(i - j); // match found
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return indices;
}

// Example usage
int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    vector<int> result = kmpSearch(text, pattern);

    cout << "Pattern found at indices: ";
    for (int index : result) {
        cout << index << " ";      // answer - 10
    }
    cout << endl;

    return 0;
}



/* 
2. Rabin-Karp Algorithm
***************************************
Rabin-Karp uses a rolling hash to search for the pattern in the text.
It is efficient for multiple pattern searches and usually runs in average O(n + m) time.

->Hash the pattern and the initial window of the text.
->Slide the window over the text one character at a time:
                -Recalculate the hash in O(1) using rolling hash.
                -If the hash matches, compare strings (to avoid collisions).


Advantages of Rabin-Karp:
-Good for multiple pattern matching (reuse hashes).
-Efficient with rolling hash: avoids recalculating whole substring hash.


*/
#include <bits/stdc++.h>
using namespace std;

#define d 256 // number of characters in input alphabet (ASCII)

// Rabin-Karp algorithm
vector<int> rabinKarp(const string& text, const string& pattern, int q) {
    int n = text.length();
    int m = pattern.length();
    vector<int> result;

    if (m > n) return result;

    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    int p = 0; // hash value for pattern
    int t = 0; // hash value for text window

    // Calculate initial hash values for pattern and first window
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (int i = 0; i <= n - m; i++) {
        // If hash matches, check characters one by one
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                result.push_back(i);
        }

        // Calculate hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // If t becomes negative, convert it to positive
            if (t < 0)
                t += q;
        }
    }

    return result;
}

int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";
    int q = 101; // a prime number for modulo

    vector<int> matches = rabinKarp(text, pattern, q);

    cout << "Pattern found at indices: ";
    for (int idx : matches)
        cout << idx << " ";   // answer - 10
    cout << endl;

    return 0;
}

/*
When to Use Which?

Use KMP if you want:
1. A guaranteed linear time algorithm
2. No false positives
3. Matching a single pattern

Use Rabin-Karp if you want:
1. To search multiple patterns at once
2. A simpler implementation in some practical cases
3.Are okay with potential hash collisions (and willing to verify)
*/



/*
3. Palindrome Check
***************************************
-> Check if a string is a palindrome (ignoring non-alphanumeric characters and case)
-> Find the longest palindromic substring
*/
#include <bits/stdc++.h>
using namespace std;

// Function to check if a string is a palindrome
bool is_palindrome(const string& s) {
    string filtered;
    for (char c : s) {
        if (isalnum(c)) {
            filtered += tolower(c);
        }
    }

    int left = 0, right = filtered.size() - 1;
    while (left < right) {
        if (filtered[left] != filtered[right])
            return false;
        left++;
        right--;
    }
    return true;
}

// Helper function to expand around center
int expandAroundCenter(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

// Function to find the longest palindromic substring
string longest_palindrome_substring(const string& s) {
    if (s.empty()) return "";
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); ++i) {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = max(len1, len2);

        if (len > end - start) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }
    return s.substr(start, end - start + 1);
}

// Example usage
int main() {
    string input = "A man, a plan, a canal: Panama";

    cout << "Is palindrome (cleaned): " << (is_palindrome(input) ? "Yes" : "No") << endl;
    cout << "Longest palindromic substring: " << longest_palindrome_substring(input) << endl;

    return 0;
}



/*
4. Anagram Detection
***************************************
-> Anagram Detection (using unordered_map)
-> Finding All Anagrams of a Pattern in a String (Sliding Window + Hash Map)
*/

#include <bits/stdc++.h>
using namespace std;

// Helper function to build character frequency map
unordered_map<char, int> buildCounter(const string& s) {
    unordered_map<char, int> counter;
    for (char c : s) {
        counter[c]++;
    }
    return counter;
}
// Function to check if two strings are anagrams
bool are_anagrams(const string& s1, const string& s2) {
    return buildCounter(s1) == buildCounter(s2);
}
// Function to find all starting indices of anagrams of p in s
vector<int> find_all_anagrams(const string& s, const string& p) {
    vector<int> result;
    unordered_map<char, int> p_count = buildCounter(p);
    unordered_map<char, int> window_count;

    for (int i = 0; i < s.size(); ++i) {
        // Add current character to window
        window_count[s[i]]++;

        // Shrink the window if it's larger than p
        if (i >= p.size()) {
            char to_remove = s[i - p.size()];
            window_count[to_remove]--;
            if (window_count[to_remove] == 0) {
                window_count.erase(to_remove);
            }
        }
        // Check if current window is an anagram of p
        if (window_count == p_count) {
            result.push_back(i - p.size() + 1);
        }
    }
    return result;
}

// Example usage
int main() {
    string s1 = "listen", s2 = "silent";
    cout << "Are anagrams: " << (are_anagrams(s1, s2) ? "Yes" : "No") << endl;

    string s = "cbaebabacd", p = "abc";
    vector<int> indices = find_all_anagrams(s, p);
    cout << "Anagram indices: ";
    for (int index : indices) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}



/*
5. String Compression
*****************************************
*/
#include <bits/stdc++.h>
using namespace std;

int compress(vector<char>& chars) {
    int write = 0, anchor = 0;

    for (int read = 0; read < chars.size(); ++read) {
        // If this is the last character or the next character is different
        if (read + 1 == chars.size() || chars[read + 1] != chars[read]) {
            chars[write++] = chars[anchor];  // Write the character

            if (read > anchor) {  // If the group has more than 1 character
                int count = read - anchor + 1;
                string count_str = to_string(count);
                for (char digit : count_str) {
                    chars[write++] = digit;
                }
            }
            anchor = read + 1;
        }
    }
    return write;
}

// Example usage
int main() {
    vector<char> chars = {'a','a','b','b','c','c','c'};
    int newLength = compress(chars);

    cout << "Compressed characters: ";
    for (int i = 0; i < newLength; ++i) {
        cout << chars[i];
    }
    cout << "\nNew length: " << newLength << endl;     
    return 0;
}
// For input: {'a','a','b','b','c','c','c'}
// It will output: a2b2c3 and New length: 6

