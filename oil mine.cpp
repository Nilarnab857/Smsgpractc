/*
https://www.careercup.com/question?id=5740719907012608
https://stackoverflow.com/questions/39673898/divide-array-into-k-contiguos-partitions-such-that-sum-of-maximum-partition-is-m/39675396
http://ideone.com/r60yH4 - Sameer Code
https://www.careercup.com/question?id=5730470801702912
*/

/*
There is an island surrounded by oil mines. You will be given n companies and m oil mines having values.
You have to distribute the mines to "n" companies in fair manner. Remember the companies can have oil 
mines adjacent to each other and not in between of each others.After distributing them compute the 
difference of oil mines from the company getting highest and company getting lowest. This number 
should be minimum.(then only the distribution can be termed as fair).

Input 
2 
2 4 
6 13 10 2 
2 4 
6 10 13 2 

output 
5 
1
*/
#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int best_answer;

// pre: prefix sum array
// cur: the index we are starting the current chunk from
// formed: number of companies we have assigned chunks to so far
// curmax / curmin: tracking the highest/lowest sums in this specific timeline
// end_limit: the absolute last index we can use (since we start from different points in the circle)
// n: total companies needed
void f(const vector<int>& pre, int cur, int formed, int curmax, int curmin, int end_limit, int n) {
    // OPTIMIZED BASE CASE: 
    // If we only have 1 company left to form (meaning formed == n - 1), 
    // they MUST take whatever mines are left over. We don't need a loop for this.
    if (formed == n - 1) {
        // Calculate the sum of all remaining mines up to the end_limit
        int last_chunk_sum = pre[end_limit] - pre[cur - 1];
        
        int final_max = max(curmax, last_chunk_sum);
        int final_min = min(curmin, last_chunk_sum);
        
        // Update global answer
        best_answer = min(best_answer, final_max - final_min);
        return;
    }

    // "Save some for later" limit
    int remaining_companies = n - formed;
    // We must leave at least 1 mine for each company that comes after us
    int limit = end_limit - (remaining_companies - 1); 

    for (int i = cur; i <= limit; i++) {
        // O(1) sum calculation using prefix sums
        int chunk_sum = pre[i] - pre[cur - 1];
        
        int next_max = max(curmax, chunk_sum);
        int next_min = min(curmin, chunk_sum);
        
        // Recurse for the next company, starting from index i + 1
        f(pre, i + 1, formed + 1, next_max, next_min, end_limit, n);
    }
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // Use 1-based indexing, size is 2 * m + 1 to hold the unrolled array
    vector<int> a(2 * m + 1, 0);
    vector<int> pre(2 * m + 1, 0);

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        a[i + m] = a[i]; // Unroll the circle: duplicate the array
    }

    // Build the prefix sum array
    for (int i = 1; i <= 2 * m; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    // Reset best_answer for each testcase
    best_answer = INT_MAX;

    // Try every valid linear starting point in the circle
    // A valid sequence is always exactly 'm' mines long
    for (int start = 1; start <= m; start++) {
        int end_limit = start + m - 1; // The final index for this specific start point
        
        // Start recursion: formed = 0, initial max = incredibly small, initial min = incredibly large
        f(pre, start, 0, INT_MIN, INT_MAX, end_limit, n);
    }

    cout << best_answer << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt;
    if (cin >> tt) {
        while (tt--) {
            solve();
        }
    }
    return 0;
}
