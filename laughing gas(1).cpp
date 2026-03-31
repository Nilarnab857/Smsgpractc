//https://www.cnblogs.com/kingshow123/p/practicec1.html
//my sol
#include <bits/stdc++.h>
using namespace std;

int n, m, sr, sc;
const int maxN = 105;
int a[maxN][maxN];

int dr[4]  = {-1, 0, 1, 0};
int dc[4]  = { 0, 1, 0, -1};

bool valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

int maxtimebfs() {
    int maxtime = 0;
    
    queue<pair<pair<int,int>, int>> q;
    vector<vector<int>> vis(n, vector<int>(m, 0));
    
    q.push({{sr, sc}, 0});
    vis[sr][sc] = 1;
    
    while(!q.empty()) {
        auto it = q.front();
        q.pop();
        int r = it.first.first;
        int c = it.first.second;
        
        int cnt = it.second;
        maxtime = max(maxtime, cnt);
        
        for(int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // FIX 1: Check for == 1 (people), not 0 (empty space)
            if(valid(nr, nc) && !vis[nr][nc] && a[nr][nc] == 1) {
                // FIX 2: Mark as visited IMMEDIATELY to prevent queue flooding
                vis[nr][nc] = 1; 
                q.push({{nr, nc}, cnt + 1});
            }  
        }
    }
    
    return maxtime;
}

// FIX 3: Pass the current test case number to handle output format
void solve(int caseNum) {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    cin >> sr >> sc;
    
    // FIX 4: Convert 1-based coordinates from input to 0-based for C++ arrays
    sr--; 
    sc--;
    
    int maxtime = maxtimebfs();
    
    // FIX 3 (continued): Print required "Case #T" format
    cout << "Case #" << caseNum << "\n" << maxtime << "\n";
}

int main() {
    int tt;
    cin >> tt;
    // Keep track of the test case number
    for(int i = 1; i <= tt; i++) {
        solve(i);
    }
    return 0;
}


#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>

using namespace std;
typedef struct
{
    int x;
    int y;
    int level;
}data;
int mv[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
//int mv[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};

int main()
{
    //freopen("test.txt","r",stdin);
    int T;
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        int n,m;
        int r,c;
        cin>>n>>m;
        int a[m+1][n+1];
        memset(a,0,sizeof(int)*m*n);
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                cin>>a[i][j];
            }
        }

        cin>>r>>c;
        data d,d1,d2;
        queue<data> qt;
        int tmx,tmy,tml;
        d.x = c;
        d.y = r;
        d.level = 1;
        qt.push(d);
        a[d.x][d.y] = 2;
        while(!qt.empty())
        {
            d1 = qt.front();
            qt.pop();
            for(int k=0; k<4; k++)
            {
                tmx = d1.x + mv[k][0];
                tmy = d1.y + mv[k][1];
                tml = d1.level + 1;
                if(a[tmx][tmy] == 1)
                {
                    d2.x = tmx;
                    d2.y = tmy;
                    d2.level = tml;
                    a[d2.x][d2.y] = 2;
                    qt.push(d2);
                }
            }
        }
        cout<<"Case #"<<t<<endl;
        cout<<tml-1<<endl;
    }
    //cout << "Hello world!" << endl;
    return 0;
}
