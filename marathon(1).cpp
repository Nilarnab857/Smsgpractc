/*
A person is running a marathon of distance D with limited energy H.
He can change his pace every 1 km. Every pace consumes some amount of energy.
Given 5 paces in increasing order of time, i.e. time taken to run 1 km and energy consumed in 1km.
You need to find the least amount of time required to complete the marathon within the given amount of energy.
Paces are given such that the combination always completes the marathon.

Input format:
The first line contains the number of test cases T.
Each test case is given as follows:
- The first line of each test case contains the 2 integers D and H (D is the distance and H is the energy)
- The next 5 lines are as follows:
    - There are 3 integers (M, S and E) where: M is the minutes and S is the seconds required to run 1 km
      and E is the energy consumed in 1 km.

Output Format:
Print the following:
# followed by test case number followed by minimum time in mutes followed by seconds
Eg: #1 153 20

Eg: D = 30, H = 130
5 Paces: (M min S sec E energy)
4 50 7
5 0 5
5 10 4
5 20 3
5 30 2

Output: #1 153 20
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A large enough number to represent infinity (unreachable states)
const int INF = 1e9; 

struct Pace {
    int time_sec;
    int energy;
};

void solve(int test_case) {
    int D, H;
    cin >> D >> H;
    
    vector<Pace> paces(5);
    for (int i = 0; i < 5; ++i) {
        int m, s, e;
        cin >> m >> s >> e;
        paces[i] = {m * 60 + s, e}; 
    }

    // 2D DP Table: dp[distance][energy]
    // dp[d][h] stores the minimum time to run 'd' kilometers using exactly 'h' energy.
    // We create a grid of size (D + 1) rows and (H + 1) columns.
    vector<vector<int>> dp(D + 1, vector<int>(H + 1, INF));
    
    // Base case: 0 km distance using 0 energy takes 0 seconds.
    dp[0][0] = 0; 

    // Iterate through each kilometer from 1 to D
    for (int d = 1; d <= D; ++d) {
        
        // Iterate through all possible energy levels we could have used up to the PREVIOUS kilometer
        for (int h = 0; h <= H; ++h) {
            
            // If it was actually possible to reach the previous kilometer with 'h' energy
            if (dp[d - 1][h] != INF) { 
                
                // Try running the current kilometer using each of the 5 paces
                for (const auto& p : paces) {
                    
                    // Check if taking this pace keeps us within our total energy limit H
                    if (h + p.energy <= H) {
                        
                        // Calculate the new total energy
                        int new_energy = h + p.energy;
                        
                        // The time to reach distance 'd' with this new energy is either:
                        // 1. The time we already calculated for this state (if any)
                        // 2. The time from the previous state + the time this new pace takes
                        dp[d][new_energy] = min(dp[d][new_energy], dp[d - 1][h] + p.time_sec);
                    }
                }
            }
        }
    }

    // Find the minimum time across all possible energy expenditures for the FINAL distance D
    int min_time = INF;
    for (int h = 0; h <= H; ++h) {
        min_time = min(min_time, dp[D][h]);
    }

    // Convert back to minutes and seconds
    cout << "#" << test_case << " " << min_time / 60 << " " << min_time % 60 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        for (int i = 1; i <= T; ++i) {
            solve(i);
        }
    }
    return 0;
}

#include <iostream>
using namespace std;

class Pace
{
public:
    int index;
    int time;
    int energy;
    Pace() {}
    Pace(int index, int time, int energy) : index(index), time(time), energy(energy) {}
};

int solve(int remainingD, int remainingH, int index, Pace paces[5], int curTime, int minTime)
{
    if (remainingD < 0)
        return (int)1e9;
    if (remainingD == 0)
    {
        if (remainingH < 0)
            return (int)1e9;
        return curTime;
    }
    if (remainingH < 0)
        return (int)1e9;
    if (index >= 5)
        return (int)1e9;

    for (int distance = 0; distance <= remainingD; distance++)
    {
        int time = curTime + solve(remainingD - distance,
                                   remainingH - (paces[index].energy * distance),
                                   index + 1,
                                   paces,
                                   paces[index].time * distance,
                                   minTime);
        minTime = min(minTime, time);
    }
    return minTime;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    for (int testCase = 1; testCase <= t; testCase++)
    {
        int D, H;
        cin >> D >> H;

        Pace paces[5];
        for (int i = 0; i < 5; i++)
        {
            int minv, sec, energy;
            cin >> minv >> sec >> energy;
            paces[i] = Pace(i, minv * 60 + sec, energy);
        }

        int minTime = (int)1e9;
        minTime = solve(D, H, 0, paces, 0, minTime);

        cout << "#" << testCase << " " << minTime / 60 << " " << minTime % 60 << "\n";
    }

    return 0;
}
