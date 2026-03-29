/*
https://www.careercup.com/question?id=14989765
http://ideone.com/oXdBaF

Given a 2 D matrix where 1 represent the places where the frog can jump and 0 represent the empty spaces,
the frog can move freely in horizontal direction (on 1’s only) without incurring any cost (jump). 
A vertical jump from a given point of the matrix to other point on the matrix can be taken (on 1’s only) 
with cost as the number of jumps taken.
Given a source and destination, the frog has to reach the destination minimizing the cost (jump).
*/

// 01 dijkstra optimisation of dijkstra using deque
#include <bits/stdc++.h>
using namespace std;

// Adjusted to 105 to prevent Memory Limit Exceeded (MLE)
const int maxN = 105; 

int n, sx, sy, tx, ty;
int arr[maxN][maxN];
int dist[maxN][maxN];

// Indices: 0=Up, 1=Right, 2=Down, 3=Left
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

bool isValid(int r, int c) {
    return (r >= 0 && r < n && c >= 0 && c < n);
}

void dijstra01() {
    // 1. Initialize all distances to infinity
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INT_MAX;
        }
    }

    // 2. Setup the Deque
    deque<pair<int, int>> dq;
    dq.push_front({sx, sy});
    dist[sx][sy] = 0;

    // 3. Main 0-1 BFS Loop
    while (!dq.empty()) {
        auto it = dq.front();
        dq.pop_front();
        
        int r = it.first;
        int c = it.second;

        // Early exit: If we reached the target, we can stop exploring
        if (r == tx && c == ty) break;

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Check if within bounds AND is a valid lily pad (1)
            if (isValid(nr, nc) && arr[nr][nc] == 1) {
                
                // Determine cost: 
                // i = 0 (Up) and i = 2 (Down) cost 1 jump.
                // i = 1 (Right) and i = 3 (Left) cost 0 jumps.
                int jumpCost = (i == 0 || i == 2) ? 1 : 0;

                // Relaxation Step: If we found a cheaper way to this cell
                if (dist[r][c] + jumpCost < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + jumpCost;
                    
                    // 0-1 BFS Magic:
                    if (jumpCost == 0) {
                        dq.push_front({nr, nc}); // Free horizontal move -> Front
                    } else {
                        dq.push_back({nr, nc});  // Costly vertical move -> Back
                    }
                }
            }
        }
    }
    
    // Output the minimum jumps required
    cout << dist[tx][ty] << "\n";
}

void solve() {
    cin >> n >> sx >> sy >> tx >> ty;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    
    // Call the function
    dijstra01();
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
