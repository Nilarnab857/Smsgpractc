/*
https://www.careercup.com/question?id=5677905146281984
https://github.com/arjunsk/samsung_interview/blob/master/wormhole.cpp
https://gist.github.com/gunpreet34/b58c38b3556271059182244676ba06a1
https://hack.codingblocks.com/contests/c/782/870
https://discuss.codingblocks.com/t/test-case-of-minimum-time-traversal-problem/12944

http://ideone.com/Sbx7MA
*/

/*
There is one spaceship. X and Y co-odinate of source of spaceship and destination spaceship is given.
There are N number of warmholes; each warmhole has 5 values. First 2 values are starting co-ordinate
of warmhole and after that value no. 3 and 4 represents ending co-ordinate of warmhole and last 5th 
value is represents cost to pass through this warmhole. Now these warmholes are bi-directional. Now 
the to go from (x1,y1) to (x2,y2) is abs(x1-x2)+abs(y1-y2). The main problem here is to find minimum 
distance to reach spaceship from source to destination co-ordinate using any number of warm-hole. 
It is ok if you wont use any warmhole.
*/#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

// A simple structure to hold coordinates
struct Point {
    int x, y;
};

// Helper to calculate Manhattan distance
int getManhattan(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int main() {
    int t;
    if (!(cin >> t)) return 0;
    
    int tNo = 0;
    while (t--) {
        int n;
        cin >> n;
        
        Point src, dst;
        cin >> src.x >> src.y >> dst.x >> dst.y;
        
        // 1. COLLECT ALL NODES
        vector<Point> nodes;
        nodes.push_back(src); // Node 0 is Source
        
        vector<int> wormholeCosts(n);
        for (int i = 0; i < n; i++) {
            Point p1, p2;
            int cost;
            cin >> p1.x >> p1.y >> p2.x >> p2.y >> cost;
            
            nodes.push_back(p1); // Node 2i + 1
            nodes.push_back(p2); // Node 2i + 2
            wormholeCosts[i] = cost;
        }
        
        nodes.push_back(dst); // Node 2N + 1 is Destination
        
        int V = nodes.size();
        
        // 2. CONSTRUCT THE GRAPH (Adjacency List)
        // pair<target_node, edge_weight>
        vector<vector<pair<int, int>>> adj(V);
        
        // Add walking edges between ALL pairs of nodes
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                int dist = getManhattan(nodes[i], nodes[j]);
                adj[i].push_back({j, dist});
                adj[j].push_back({i, dist}); // Graph is undirected
            }
        }
        
        // Add the special Wormhole edges
        for (int i = 0; i < n; i++) {
            int u = 2 * i + 1; // End 1 of wormhole i
            int v = 2 * i + 2; // End 2 of wormhole i
            int cost = wormholeCosts[i];
            
            // We add the shortcut edge. Dijkstra will automatically prefer this 
            // over the walking edge if 'cost' is smaller.
            adj[u].push_back({v, cost});
            adj[v].push_back({u, cost});
        }
        
        // 3. APPLY DIJKSTRA'S ALGORITHM
        vector<int> min_dist(V, 1e9); // Initialize distances to "infinity"
        min_dist[0] = 0; // Distance to Source is 0
        
        // Min-Heap priority queue: stores {current_distance, node_index}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            // Optimization: Ignore stale pairs in the priority queue
            if (d > min_dist[u]) continue;
            
            // Check all neighbors
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                // Relaxation step
                if (min_dist[u] + weight < min_dist[v]) {
                    min_dist[v] = min_dist[u] + weight;
                    pq.push({min_dist[v], v});
                }
            }
        }
        
        tNo++;
        // The answer is the shortest distance to the Destination node
        cout << "#" << tNo << " : " << min_dist[V - 1] << "\n";
    }
    
    return 0;
}

// #include<iostream>
// using namespace std;

// int n, a[2001][6];
 
// int min(int x , int y){
//     return(x>=y) ? y : x ;
// }

// int abs(int x){
// 	return (x > 0) ? x : -x ;
// }

// int dist(int x1 , int y1 , int x2 , int y2){
// 	return abs(x2-x1) + abs(y2 - y1);
// }

// void wormhole ( int x1 , int y1 , bool *visited , int &ans , int val ) {
// 	if ( x1 == a[n+1][0] && y1 == a[n+1][1] ){
// 		ans = min ( ans , val);
// 	    return ;
// 	}
	    
// 	for ( int i = 1 ; i <= n + 1 ;i++) {
// 		if (!visited[i]) {
// 	    	visited[i] = true ;
	    	 	 
// 	    	//entry
// 	    	wormhole ( a[i][2] , a[i][3] , visited , ans , val + dist ( x1 , y1 , a[i][0] , a[i][1] ) + a[i][4]);
	    	
// 	    	//exit
// 	    	wormhole ( a[i][0] , a[i][1] , visited , ans , val + dist ( x1 , y1 , a[i][2] , a[i][3] ) + a[i][4]);
	    	 	 
// 	    	visited[i] = false;
// 		}
// 	}	
// }

// int main(){
//     int t;	cin >> t ;
//     for (int i = 1; i <= t ; i++){
// 		cin >> n;
// 	    int sx, sy, dx,dy;
// 		cin>>sx>>sy>>dx>>dy; 
		 
// 		a[0][0] = sx ; a[0][1] = sy ; a[0][2] = sx ; a[0][3] = sy ; a[0][4] = 0 ;
		 
//         for ( int i = 1 ; i <= n ;i++ ){
// 			cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3] >> a[i][4];
// 		}	
		 
//         a[n+1][0] = dx ; a[n+1][1] = dy ; a[n+1][2] = dx ; a[n+1][3] = dy ; a[n+1][4] = 0 ;
         
//         int ans ;  
//         bool visited[n+2] = { false };

//         ans = dist (a[0][0] , a[0][1] , a[n+1][0] , a[n+1][1]);        
//         visited[0] = true ;
           
//         wormhole(sx ,sy , visited , ans , 0);
          
//         cout << "#" << i << " : " << ans << endl;
//   	}
//   return 0;
// }
