/*
https://www.geeksforgeeks.org/samsung-interview-experience-set-39-campus-r-d-noida/
https://www.careercup.com/page?pid=samsung-interview-questions

A Doctor travels from a division to other division where divisions are connected like a graph(directed graph) and 
the edge weights are the probabilities of the doctor going from that division to other connected division but the 
doctor stays 10mins at each division now there will be given time and had to find the division in which he will be 
staying by that time and is determined by finding division which has high probability.

Input is number of test cases followed by the number of nodes, edges, time after which we need to find the division 
in which he will be there, the edges starting point, end point, probability.

Note: If he reaches a point where there are no further nodes then he leaves the lab after 10 mins and the traveling 
time is not considered and during that 10min at 10th min he will be in next division, so be careful

2
6 10 40 
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5
6 10 10 
1 2 0.3 1 3 0.7 3 3 0.2 3 4 0.8 2 4 1 4 5 0.9 4 4 0.1 5 6 1.0 6 3 0.5 6 6 0.5

6 0.774000  
3 0.700000
*/


#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void solve() {
    int n, E, endtime;
    cin >> n >> E >> endtime;
    
    // Fixed the missing semicolon and renamed for clarity
    int steps = endtime / 10; 
    
    // Graph using 0-based indexing
    vector<vector<pair<int, double>>> adj(n);
    for(int i = 0; i < E; i++) {
        int u, v;
        double P;
        cin >> u >> v >> P;
        adj[u-1].push_back({v-1, P}); 
    }
    
    // dp[t][u] stores the probability of being at node 'u' at time step 't'
    vector<vector<double>> dp(steps + 1, vector<double>(n, 0.0));
    dp[0][0] = 1.0; // Starts at Node 1 (which is index 0)
    
    // DP Transitions
    for(int t = 0; t < steps; t++) {
        for(int u = 0; u < n; u++) {
            // Optimization: Only process if there's a > 0 chance of being here
            if (dp[t][u] > 0.0) { 
                for(auto it : adj[u]) {
                    int v = it.first;
                    double P = it.second;
                    // Push probability forward to the next step
                    dp[t+1][v] += (dp[t][u] * P);
                }
            }
        }
    }
    
    // Find the max probability in the final step
    double max_prob = 0.0;
    int best_node = 0;
    
    for(int u = 0; u < n; u++) {
        if(dp[steps][u] > max_prob) {
            max_prob = dp[steps][u];
            best_node = u;
        }
    }
    
    // Output: Convert 0-indexed node back to 1-indexed for the answer
    cout << (best_node + 1) << " " << fixed << setprecision(6) << max_prob << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

#include<iostream>
using namespace std;

void docProb(double **graph, int nodes, int time, int curNode, double p, double *answer){
	if(time <= 0){
		answer[curNode] += p;
		return;
	}

	for(int i=1; i<=nodes; i++){
		if(graph[curNode][i] != 0){
			p *= graph[curNode][i];
			docProb(graph, nodes, time - 10, i, p, answer);
			p /= graph[curNode][i];	
		}
	}

}

int main(){
	int t;
	cin >> t;
	while(t--){
		int nodes, edges, time;
		cin >> nodes >> edges >> time;
		
		double **arr = new double*[nodes]; 
		for(int i=1; i<=nodes; i++){
			arr[i] = new double[nodes];
			for(int j=1; j<=nodes; j++){
				arr[i][j] = 0;
			}
		}

		int from, to;
		double prob;
		for(int i=0; i<edges; i++){
			cin >> from >> to >> prob;
			arr[from][to] = prob;
		}

		/* Initalise answer and function call */
		double answer[nodes] = {0.0};
		docProb(arr, nodes, time, 1, 1.0, answer);
		
		/* Select max Probability node */
		double finalProb = 0.0;
		int finalDivison = 0;
		
		for(int i=1; i<=nodes; i++){
			if(answer[i] > finalProb){
				finalProb = answer[i];
				finalDivison = i;
			}
		}
		cout << finalDivison << " " << finalProb << "\n";
	}
	return 0;
}
