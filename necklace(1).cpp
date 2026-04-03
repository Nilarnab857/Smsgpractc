/*
Given n (1 to 100000)
And a string of size 2n

Where string is made of characters R and B showing the beads of a nacklace which are of two types red and blue respective.
The nacklace has a knot in the middle, between nth and n+1 th bead
You can't move a bead across that knot
You have to find the min number of beads to be removed to make count of blue and red beads same in the necklace
You can remove beads from both the end of the necklace

Ex:
2 RRRR, ans: 4
3 RRBRBR, ans: 2
3 RBBBBB, ans: 6
*/




#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin >> s;
    int n = s.size() / 2;
    
    string left_half = s.substr(0, n);
    string right_half = s.substr(n, n);
    
    // 1. Initialize to -1 so we know which balances are actually unreachable
    vector<int> balances(2 * n + 1, -1);
    
    // 2. Base case: a prefix of length 0 has a balance of 0
    balances[n] = 0; 
    
    int running = 0;
    for(int i = 0; i < right_half.size(); i++){
        running += ((right_half[i] == 'R') ? 1 : -1);
        balances[running + n] = i + 1;
    }
    
    int ans = 0;
    
    // 3. Handle the case where the left suffix is empty (length 0)
    if (balances[n] != -1) {
        ans = max(ans, balances[n]);
    }
   
    running = 0;
    for(int i = left_half.size() - 1; i >= 0; i--){
        running += ((left_half[i] == 'R') ? 1 : -1);
        
        // Only update if the required balance actually exists in the right half
        if (balances[n - running] != -1) {
            ans = max(ans, (n - i) + balances[n - running]);
        }
    }
    
    // 4. Print minimum removed (total beads minus max kept)
    cout << (2 * n) - ans << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int tt;
    if (cin >> tt) {
        while(tt--){
            solve();
        }
    }
    return 0;
}

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int solve(string s, int n)
{
    unordered_map<int, int> mpp;
    mpp[0] = -1;
    int balance = 0;
    int maxLen = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == 'R')
        {
            balance--;
        }
        else
        {
            balance++;
        }

        if (mpp.find(balance) != mpp.end())
        {
            if (i >= n && mpp[balance] < n)
            {
                int len = i - mpp[balance];
                maxLen = max(maxLen, len);
            }
        }
        else
        {
            mpp[balance] = i;
        }
    }
    return s.length() - maxLen;
}

int main(int argc, char const *argv[])
{
    int testCases;
    cin >> testCases;

    for (int i = 0; i < testCases; i++)
    {
        int n;
        string s;
        cin >> n;
        cin >> s;

        int res = solve(s, n);
        cout << "#" << i << " " << res << endl;
    }
    return 0;
}
