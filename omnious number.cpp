/*
https://www.geeksforgeeks.org/samsung-interview-experience-set-40-campus-white-box-testing/
https://www.geeksforgeeks.org/samsung-rd-sri-noida-on-campus-interview-experience/
https://code.hackerearth.com/01ac52j?key=b462f0a802c8c1faf1d87f2b1353b9ce

Company  A  is discarding product numbers that contain few specific digits a specific number of time or 
more than that. You are given a range and you need to find product numbers that are possible.

Example-

Range: 24 to 12943

Numbers that should not come: 1, 3, 5
Number of times these number should not occur: 3 or more

In above case all two digit numbers are valid.

In three digit: 111, 113, 115, 311, 331, 333, 511, 533, 555 are not valid.

In four digit: All the numbers containing above 3 digit numbers are not valid.

Eg: 11223 is not valid, 11222 is valid.
*/

#include <iostream>
using namespace std;

int numberOminous(int a, int b, int k, int *delNos, int n){
    int count = 0;
    for(int i = a; i <= b; i++){
        int temp = i;
        int digitArray[10] = {0};

        while(temp){
            digitArray[temp%10]++;
            temp /= 10;
        }
        
        int rougeK = 0;
        for(int i=0; i<n; i++){
            rougeK += digitArray[delNos[i]];
        }

        if(rougeK < k){
            count++;
        }

    }
    return count;
}

int main() {
    int a, b, k;
    cin >> a >> b >> k;
    int n;
    cin >> n;
    int *delNos = new int[n];
    for(int i=0; i<n; i++){
        cin >> delNos[i];
    }

    cout << numberOminous(a, b, k, delNos, n) << "\n";

    return 0;
}

DIGIT DP SOLUTION FOR LARGE R
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// Global settings based on the problem
int K; 
bool is_bad[10]; // is_bad[d] is true if 'd' is a restricted digit

// The DP Cache: dp[index][bad_count][tight][leading_zero]
// Max digits ~20, Max K ~20, tight (2), leading_zero (2)
long long dp[20][20][2][2];
string current_limit_string;

// The core recursive function
long long digit_dp(int idx, int bad_count, bool tight, bool leading_zero) {
    // Base Case: If we've placed all digits
    if (idx == current_limit_string.length()) {
        return (bad_count < K) ? 1 : 0;
    }

    // Pruning: If we've already hit or exceeded K bad digits, this timeline is dead
    if (bad_count >= K) {
        return 0;
    }

    // Return cached result if we have been in this exact state before
    if (dp[idx][bad_count][tight][leading_zero] != -1) {
        return dp[idx][bad_count][tight][leading_zero];
    }

    long long total_valid_numbers = 0;

    // Determine the maximum digit we can place in this slot
    int limit = tight ? (current_limit_string[idx] - '0') : 9;

    // Try placing every digit from 0 up to our limit
    for (int d = 0; d <= limit; d++) {
        
        // 1. Calculate next 'tight' state
        bool next_tight = tight && (d == limit);
        
        // 2. Calculate next 'leading_zero' state
        bool next_leading_zero = leading_zero && (d == 0);
        
        // 3. Calculate next 'bad_count'
        int next_bad_count = bad_count;
        if (is_bad[d]) {
            // CRUCIAL: Only count '0' as bad if it is NOT a leading zero padding
            if (!(d == 0 && leading_zero)) {
                next_bad_count++;
            }
        }

        // Move to the next digit slot
        total_valid_numbers += digit_dp(idx + 1, next_bad_count, next_tight, next_leading_zero);
    }

    // Cache the result before returning
    return dp[idx][bad_count][tight][leading_zero] = total_valid_numbers;
}

// Wrapper function to reset DP table and start the recursion
long long solve(string limit_str) {
    current_limit_string = limit_str;
    memset(dp, -1, sizeof(dp));
    
    // Start at index 0, 0 bad digits, tight = true, leading_zero = true
    return digit_dp(0, 0, true, true);
}

// Helper function to check if a specific string manually satisfies the condition
bool isValidNumber(string num) {
    int bad_count = 0;
    for (char c : num) {
        if (is_bad[c - '0']) {
            bad_count++;
        }
    }
    return bad_count < K;
}

int main() {
    // 1. Setup the rules
    string L = "24";
    string R = "12943";
    K = 3;
    
    memset(is_bad, false, sizeof(is_bad));
    is_bad[1] = true;
    is_bad[3] = true;
    is_bad[5] = true;

    // 2. Calculate Answer: [0, R] - [0, L] + check(L)
    long long ansR = solve(R);
    long long ansL = solve(L);
    long long final_answer = ansR - ansL + (isValidNumber(L) ? 1 : 0);

    cout << "Valid numbers between " << L << " and " << R << ": " << final_answer << "\n";

    return 0;
}
