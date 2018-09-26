#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
  public:
    /* 1. Two Sum
    Given an array of integers, return indices of the two numbers such that they add up to a specific target.

    You may assume that each input would have exactly one solution, and you may not use the same element twice.

    Example:

    Given nums = [2, 7, 11, 15], target = 9,

    Because nums[0] + nums[1] = 2 + 7 = 9,
    return [0, 1].
    */
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> index;
        for (size_t i = 0; i < nums.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < nums.size(); ++j)
            {
                if (nums[i] + nums[j] == target)
                {
                    index.push_back(i);
                    index.push_back(j);
                    return index;
                }
            }
        }
        return index;
    }

    /* 3. Longest Substring Without Repeating Characters
    Given a string, find the length of the longest substring without repeating characters.

    Example 1:

    Input: "abcabcbb"
    Output: 3 
    Explanation: The answer is "abc", which the length is 3.
    Example 2:

    Input: "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.
    Example 3:

    Input: "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3. 
                Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
    */
   int lengthOfLongestSubstring(string s) {
        int maxLength = 0;
        size_t startIdx = 0;
        
        for (size_t endIdx = 0; endIdx < s.size(); ++ endIdx) {
            int index = -1;
            for (size_t id = startIdx; id < endIdx; ++ id) {
                if (s[id] == (int)s[endIdx]) {
                    index = id;
                    break;
                }
            }
            if (index >= 0) {   // repeated, move the start/end index
                startIdx = index + 1;
            } else {    // new character, move the end index
                if ((int)endIdx - (int)startIdx + 1 > maxLength) {
                    maxLength = endIdx - startIdx + 1;
                }
            }
        }
        return maxLength;
    }
    int lenghtOfLongestSubstring_radix(string s) {
        const size_t charSize = sizeof(char) * 256;
        int charLoc[charSize];
        for (size_t i = 0; i < charSize; ++ i) {
            charLoc[i] = -1;
        }
        int maxLength = 0;
        size_t startIdx = 0;

        for (size_t endIdx = 0; endIdx < s.size(); ++ endIdx) {
            if(charLoc[(int)s[endIdx]] >= 0) {
                for (size_t id = startIdx; (int)id < charLoc[(int)s[endIdx]]; ++ id) {
                    charLoc[(int)s[id]] = -1;
                }
                startIdx = charLoc[(int)s[endIdx]] + 1;
                charLoc[(int)s[endIdx]] = endIdx;

            } else {
                charLoc[(int)s[endIdx]] = endIdx;
                if((int)endIdx - (int)startIdx + 1 > maxLength) {
                    maxLength = (int)endIdx - (int)startIdx + 1;
                }
            }
        }
        return maxLength;
    }

    // 4. Median of Two Sorted Arrays
    /*
    There are two sorted arrays nums1 and nums2 of size m and n respectively.

    Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

    You may assume nums1 and nums2 cannot be both empty.

    Example 1:

    nums1 = [1, 3]
    nums2 = [2]

    The median is 2.0
    Example 2:

    nums1 = [1, 2]
    nums2 = [3, 4]

    The median is (2 + 3)/2 = 2.5
    */
   void mergeSort(const vector<int>& nums1, const vector<int>& nums2, vector<int>& merged) {
       merged.clear();
       merged.reserve(nums1.size() + nums2.size());

       size_t id1 = 0;
       size_t id2 = 0;
       while(id1 < nums1.size() && id2 < nums2.size()) {
           if(nums1[id1] <= nums2[id2]) {
               merged.push_back(nums1[id1]);
               ++ id1;
           } else {
               merged.push_back(nums2[id2]);
               ++ id2;
           }
       }
       for(; id1 < nums1.size(); ++ id1) {
           merged.push_back(nums1[id1]);
       }
       for(; id2 < nums2.size(); ++ id2) {
           merged.push_back(nums2[id2]);
       }
   }
    double findMedianSortedArrays_merge(const vector<int>& nums1, const vector<int>& nums2) {
        vector<int> merged;
        mergeSort(nums1, nums2, merged);
        const size_t medianId = merged.size() / 2;
        if (merged.size() % 2) {
            return merged[medianId];
        } else {
            return (merged[medianId -1] + merged[medianId]) / 2.0;
        }
    }
    double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
        if (nums1.size() == 0) {
            if (nums2.size() % 2) {
                return nums2[nums2.size() / 2];
            } else {
                return (nums2[nums2.size()/2 - 1] + nums2[nums2.size() / 2]) / 2.0;
            }
        } else if (nums2.size() == 0) {
            return findMedianSortedArrays(nums2, nums1);
        }
        if (nums1.size() == 1 && nums2.size() == 1) {
            return (nums1[0] + nums2[0]) / 2.0;
        } else if (nums1.size() == 1) {
            const size_t totalSize = nums2.size() + 1;
            if (totalSize % 2) {
                const size_t medianIdx = totalSize / 2;
                if (nums1[0] <= nums2[medianIdx]) {
                    return max(nums1[0], nums2[medianIdx -1]);
                } else {
                    return nums2[medianIdx];
                }
            } else {
                const size_t medianIdx[2] = {totalSize / 2 - 1, totalSize / 2};
                int medianNum1 = nums2[medianIdx[0]];
                int medianNum2 = nums2[medianIdx[1]];
                if (nums1[0] < medianNum1) {
                    medianNum2 = medianNum1;
                    medianNum1 = max(nums1[0], nums2[medianIdx[0] - 1]);
                } else if (medianNum1 <= nums1[0] && nums1[0] <= medianNum2) {
                    medianNum2 = nums1[0];
                }
                return (medianNum1 + medianNum2) / 2.0;
            }
        } else if (nums2.size() == 1) {
            return findMedianSortedArrays(nums2, nums1);
        } else {
            const size_t medianId1 = nums1.size() / 2;
            const size_t medianId2 = nums2.size() / 2;
            const int medianNum1 = nums1[medianId1];
            const int medianNum2 = nums2[medianId2];
            if (medianNum1 <= medianNum2) {
                if (nums1.size() % 2 == 0 && nums2.size() % 2 == 0 && nums1[medianId1 - 1] > nums2[medianId2 - 1]) {
                    return (nums1[medianId1 - 1] + nums1[medianId1]) / 2.0;
                } else {
                    int removeSize = 0;
                    if (nums1.size() % 2 && nums2.size() % 2) {
                        removeSize = min(medianId1 - 0, nums2.size() - 1 - medianId2);
                    } else {
                        removeSize = min(medianId1 - 0, nums2.size() -1 - medianId2 + 1);
                    }
                    vector<int> removedNum1(nums1.begin() + removeSize, nums1.end());
                    vector<int> removedNum2(nums2.begin(), nums2.end() - removeSize);
                    return findMedianSortedArrays(removedNum1, removedNum2);
                }
            } else {
                return findMedianSortedArrays(nums2, nums1);
            }
        }
    }

    // 5. Longest Palindromic Substring
    /*
    Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

    Example 1:

    Input: "babad"
    Output: "bab"
    Note: "aba" is also a valid answer.
    Example 2:

    Input: "cbbd"
    Output: "bb"
    */
    string longestPalindrome(string s) {
        // insert a placeholder between any two charaters, then there is (2n -1) elements.
        // compute length[i] = the longest palidrome with the ith element as middle element
        int middle_id = 0;
        int max_count = 0;
        
        const int string_size = s.size();
        const int array_size = string_size * 2 - 1;
        for (int id = 0; id < array_size; ++ id)
        {
            int count = 0;
            if (id % 2) // the placeholder is the middle element
            {
                const int max_compare_size = min(id / 2 + 1, string_size - 1 - id / 2 );
                for (int k = 0; k < max_compare_size; ++ k) 
                {
                    const int pre_id = (id -1) / 2 - k;
                    const int post_id = (id + 1) / 2 + k;
                    if (s[pre_id] != s[post_id])
                    {
                        break;
                    }
                    count += 2;
                }
            }
            else
            {
                count = 1;
                const int max_compare_size = min(id / 2, string_size - 1 - id / 2);
                for (int k = 0; k < max_compare_size; ++ k)
                {
                    const int pre_id = id / 2 - k - 1;
                    const int post_id = id / 2 + k + 1;
                    if (s[pre_id] != s[post_id])
                    {
                        break;
                    }
                    count += 2;
                }
            }
            if (count > max_count)
            {
                middle_id = id;
                max_count = count;
            }
        }
        
        const int palid_start_id = (middle_id % 2) ? (middle_id / 2 - max_count / 2 + 1) : (middle_id / 2 - (max_count - 1) / 2);
        return string(s, palid_start_id, max_count);
    }

    // 6. ZigZag Conversion
    /*
    The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

    P   A   H   N
    A P L S I I G
    Y   I   R
    And then read line by line: "PAHNAPLSIIGYIR"

    Write the code that will take a string and make this conversion given a number of rows:

    string convert(string s, int numRows);
    Example 1:

    Input: s = "PAYPALISHIRING", numRows = 3
    Output: "PAHNAPLSIIGYIR"
    Example 2:

    Input: s = "PAYPALISHIRING", numRows = 4
    Output: "PINALSIGYAHRPI"
    Explanation:

    P     I    N
    A   L S  I G
    Y A   H R
    P     I
    */
    string convert(string s, int numRows) {
        if (numRows == 1) 
        {
            return s;
        }

        const int str_size = s.size();
        const int row_0_len = str_size / (2 * numRows - 2) + 1;
        string ret_str;
        ret_str.reserve(str_size);
        for (int row_id = 0; row_id < numRows; ++ row_id)
        {
            string str_row_id;
            if (0 == row_id || numRows -1 == row_id) 
            {
                for (int id  = 0; id <= row_0_len; ++ id)
                {
                    const int index = (2 * numRows - 2) * id + row_id;
                    if (index < str_size) 
                    {
                        str_row_id += s[index];
                    }
                }
            } else 
            {
                for (int id = 0; id <= row_0_len; ++ id)
                {
                    const int mid_id = (2 * numRows - 2) * id;
                    const int pre_id = mid_id - row_id;
                    const int post_id = mid_id + row_id;
                    if (pre_id >= 0 && pre_id < str_size)
                    {
                        str_row_id += s[pre_id];
                    }
                    if (post_id >= 0 && post_id < str_size)
                    {
                        str_row_id += s[post_id];
                    }
                }
            }
            ret_str += str_row_id;
        }
        return ret_str;
    }

    // 7. Reverse Integer
    /*
    Given a 32-bit signed integer, reverse digits of an integer.
    Example 1:
    Input: 123
    Output: 321

    Example 2:
    Input: -123
    Output: -321

    Example 3:
    Input: 120
    Output: 21
    Note:
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. 
    For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.
    */
    int reverse(int x) {
        if (x == -2147483648) {return 0;}
        int retValue = 0;
        const int sign = (x >=0) ? 1 : -1;
        int value = (sign == 1) ? x : (-x);
        while (value) {
            const double tempValue = (double)retValue * 10 + (value % 10);
            if (tempValue > 2147483647) {
                return 0;
            }
            retValue = retValue * 10 + (value % 10);
            value /= 10;
        }
        return retValue * sign;
    }

    // 8. String to Integer (atoi)
    /*
    Implement atoi which converts a string to an integer.

    The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

    The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

    If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

    If no valid conversion could be performed, a zero value is returned.

    Note:

    Only the space character ' ' is considered as whitespace character.
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, intMax (2^31 − 1) or intMin (−2^31) is returned.
    Example 1:

    Input: "42"
    Output: 42
    Example 2:

    Input: "   -42"
    Output: -42
    Explanation: The first non-whitespace character is '-', which is the minus sign.
                Then take as many numerical digits as possible, which gets 42.
    Example 3:

    Input: "4193 with words"
    Output: 4193
    Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
    Example 4:

    Input: "words and 987"
    Output: 0
    Explanation: The first non-whitespace character is 'w', which is not a numerical 
                digit or a +/- sign. Therefore no valid conversion could be performed.
    Example 5:

    Input: "-91283472332"
    Output: -2147483648
    Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
                Thefore intMin (−2^31) is returned.
    */
    int myAtoi(string str) {
        double numValue = 0;
        const size_t strLen = str.size();
        size_t validStartId = 0;
        while (validStartId < strLen && str[validStartId] == ' ') {
            ++ validStartId;
        }
        if (validStartId >= strLen) {
            return 0;
        }
        const char firstChar = str[validStartId];
        if (firstChar != '+' && firstChar != '-' && (firstChar < '0' || firstChar > '9')) {
            return 0;
        }

        const int intMax = 2147483647;
        const int intMin = -2147483648;
        const int sign = (firstChar == '-') ?  -1 : 1;
        const size_t numStartId = (firstChar >= '0' && firstChar <= '9') ? validStartId : validStartId + 1;
        for (size_t si = numStartId; si < strLen && (str[si] >= '0' && str[si] <= '9'); ++ si) {
            numValue = numValue * 10 + (str[si] - '0');
            if (sign * numValue < intMin) {
                return intMin;
            } else if (sign * numValue > intMax) {
                return intMax;
            }
        }
        return int(sign * numValue);
    }

    // 9. Palindrome Number
    /*
    Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

    Example 1:

    Input: 121
    Output: true
    Example 2:

    Input: -121
    Output: false
    Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
    Example 3:

    Input: 10
    Output: false
    Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
    Follow up:

    Coud you solve it without converting the integer to a string?
    */
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        }
        const int origValue = x;
        int reverseValue = 0;
        while (x) {
            reverseValue = reverseValue * 10 + x % 10;
            x /= 10;
        }
        if (origValue == reverseValue) {
            return true;
        } else {
            return false;
        }
    }

    // 10. Regular Expression Matching
    /*
    Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

    '.' Matches any single character.
    '*' Matches zero or more of the preceding element.
    The matching should cover the entire input string (not partial).

    Note:

    s could be empty and contains only lowercase letters a-z.
    p could be empty and contains only lowercase letters a-z, and characters like . or *.
    Example 1:

    Input:
    s = "aa"
    p = "a"
    Output: false
    Explanation: "a" does not match the entire string "aa".
    Example 2:

    Input:
    s = "aa"
    p = "a*"
    Output: true
    Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
    Example 3:

    Input:
    s = "ab"
    p = ".*"
    Output: true
    Explanation: ".*" means "zero or more (*) of any character (.)".
    Example 4:

    Input:
    s = "aab"
    p = "c*a*b"
    Output: true
    Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".
    Example 5:

    Input:
    s = "mississippi"
    p = "mis*is*p*."
    Output: false
    */
    bool isMatch(string s, string p) {
        const size_t strSize = s.size();
        const size_t patSize = p.size();
        size_t strIdx = 0;
        size_t patIdx = 0;
        while (strIdx < strSize && patIdx < patSize) {
            if (p[patIdx] >= 'a' && p[patIdx] <= 'z') {
                if (s[strIdx] == p[patIdx]) {
                    if (patIdx + 1 < patSize && p[patIdx + 1] == '*') {
                        if (isMatch(string(begin(s) + strIdx + 1, end(s)), string(begin(p) + patIdx, end(p))) ||
                            isMatch(string(begin(s) + strIdx, end(s)), string(begin(p) + patIdx + 2, end(p))) ) {
                                return true;
                            } else {
                                return false;
                            }
                    
                    } else {
                        ++ strIdx;
                        ++ patIdx;
                    }
                } else {
                    if (patIdx + 2 < patSize && p[patIdx + 1] == '*') {
                        patIdx += 2;
                    } else {
                        return false;
                    }
                }
            } else if (p[patIdx] == '.') {
                if (patIdx + 1 < patSize && p[patIdx + 1] == '*') {
                    if (isMatch(string(begin(s) + strIdx + 1, end(s)), string(begin(p) + patIdx, end(p))) ||
                        isMatch(string(begin(s) + strIdx, end(s)), string(begin(p) + patIdx + 2, end(p))) ) {
                            return true;
                        } else {
                            return false;
                        }
                } else {
                    ++ strIdx;
                    ++ patIdx;
                }
            } else if (p[patIdx] == '*') {
                if (patIdx == 0){
                    return false;
                }
                if (p[patIdx - 1] == '.' || p[patIdx - 1] == s[strIdx]) {
                    size_t matchEnd = strIdx;
                    if (p[patIdx - 1] == '.') {
                        matchEnd = strSize;
                    } else {
                        while (matchEnd < strSize && s[matchEnd] == p[patIdx - 1]) {
                            ++ matchEnd;
                        }
                    }
                    string subPattern(begin(p) + patIdx + 1, end(p));
                    for (size_t subStrStartIdx = strIdx; subStrStartIdx <= matchEnd; ++ subStrStartIdx) {
                        string subStr(begin(s) + subStrStartIdx, end(s));
                        if (isMatch(subStr, subPattern)) {
                            return true;
                        }
                    }
                    return false;
                } else {
                    ++ patIdx;
                }
            } else {
                return false;
            }
        }
        
        if (strIdx == strSize) {
            if (patIdx == patSize) {
                return true;
            }
            if (patIdx + 1 < patSize && p[patIdx + 1] == '*') {
                return isMatch("", string(begin(p) + patIdx +2, end(p)));
            }
        }
        
        return false;
    }
};


int main()
{
    // 1. Two Sum
    /*
    vector<int> test_vec{2, 7, 19, 9};
    vector<int> ret_vec;
    ret_vec = Solution().twoSum(test_vec, 9);

    cout << "[" << ret_vec[0] << ", " << ret_vec[1] << "]" << endl;
    */

    // 3. Longest Substring Without Repeating Characters
    /*
    const string s = "pwwkew";
    cout << " the longest substring length of string \"" << s
         << "\" is " << Solution().lenghtOfLongestSubstring_radix(s)
         << endl;
    */

    // 4. Median of Two Sorted Arrays
    //cout << Solution().findMedianSortedArrays(vector<int>{1, 3}, vector<int>{2, 4}) << endl;

    // 5. Longest Palindromic Substring
    /*
    cout << Solution().longestPalindrome(string("cbbd")) << endl;
    */

    // 6. ZigZag Conversion
    //cout << Solution().convert("PAYPALISHIRING", 3) << endl;

    // 7. Reverse Integer 
    //cout << Solution().reverse(1534236469) << endl;

    // 8. String to Integer (atoi) 
    //cout << Solution().myAtoi("-91283472332") << endl;

    // 9. Palindrome Number
    //cout << Solution().isPalindrome(121) << endl;

    // 10. Regular Expression Matching
    cout << Solution().isMatch("", "c*c*") << endl;

    system("pause");
    return 0;
}
