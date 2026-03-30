/*
https://blog.csdn.net/lihenair/article/details/17227667
http://www.mamicode.com/info-detail-995985.html
https://www.oipapio.com/cn/article-8650635
https://blog.csdn.net/broadCE/article/details/47959227
--------------------------------------------------------
There is a maze that has one entrance and one exit. Jewels are placed in passages of the maze. 
You want to pick up the jewels after getting into the maze through the entrance and before getting 
out of it through the exit. You want to get as many jewels as possible, but you don’t want to take 
the same passage you used once.

When locations of a maze and jewels are given, find out the greatest number of jewels you can get 
without taking the same passage twice, and the path taken in this case.

Input
There can be more than one test case in the input file. The first line has T, the number of test cases.
Then the totally T test cases are provided in the following lines (T ≤ 10 ).

In each test case, In the first line, the size of the maze N (1 ≤ N ≤ 10) is given. 
The maze is N×N square-shaped. From the second line through N lines, information of the maze is given.
“0” means a passage, “1” means a wall, and “2” means a location of a jewel. The entrance is located 
on the upper-most left passage and the exit is located on the lower-most right passage. 
There is no case where the path from the entrance to the exit doesn’t exist.

Output
From the first line through N lines, mark the path with 3 and output it. In N+1 line, output the 
greatest number of jewels that can be picked up. Each test case must be output separately as a empty.
*/
#include <bits/stdc++.h>
using namespace std;

int n;
const int maxN = 11;
int grid[maxN][maxN];

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

// FIX: Replaced the 'dir' array with variables to store the best global state
int max_coins = -1;
vector<int> best_path;

bool valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

// FIX: Changed return type to void, and pass the current path sequence
void f(int r, int c, vector<vector<int>>& vis, int coins, vector<int>& current_path) {
    // Base Case: Reached the exit
    if (r == n - 1 && c == n - 1) {
        int final_coins = coins + (grid[r][c] == 2);
        // FIX: If this path yielded more coins, save it as the new best
        if (final_coins > max_coins) {
            max_coins = final_coins;
            best_path = current_path;
        }
        return;
    }
    
    vis[r][c] = 1;
    
    // Add coin if current cell has a jewel
    int new_coins = coins + (grid[r][c] == 2);
    
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        
        // FIX: Added '!vis[nr][nc]' to prevent infinite recursion bouncing between 2 cells
        if (valid(nr, nc) && grid[nr][nc] != 1 && !vis[nr][nc]) {
            current_path.push_back(i); // Record the direction taken
            
            f(nr, nc, vis, new_coins, current_path); // FIX: Added missing semicolon
            
            current_path.pop_back();   // Backtrack the direction
        }
    }
    
    // FIX: Backtrack the visited state of THIS cell before returning
    vis[r][c] = 0;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    
    // Reset global tracking variables for each test case
    max_coins = -1;
    best_path.clear();
    
    vector<vector<int>> vis(n, vector<int>(n, 0));
    vector<int> current_path;
    
    // Start the DFS
    f(0, 0, vis, 0, current_path);
    
    // FIX: Reconstruct the path using the saved best_path sequence
    int r = 0, c = 0;
    grid[r][c] = 3; // Mark entrance
    
    for (int direction : best_path) {
        r += dr[direction];
        c += dc[direction];
        grid[r][c] = 3; // Mark the rest of the path
    }
    
    // FIX: Match the required output format exactly
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << "\n";
    }
    
    // N+1 line: greatest number of jewels, followed by an empty line
    cout << max_coins << "\n\n";
}

int main() {
    // Optimize I/O
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
