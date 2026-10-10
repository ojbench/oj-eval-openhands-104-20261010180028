#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; // n columns, m rows
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> grid(m, vector<int>(n));
    pair<int,int> start{-1,-1}, home{-1,-1};
    vector<pair<int,int>> umbrellas;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int v;cin>>v;grid[i][j]=v;
            if(v==2) start={i,j};
            else if(v==3) home={i,j};
            else if(v==4) umbrellas.emplace_back(i,j);
        }
    }
    const int INF = 1e9;
    auto bfs = [&](pair<int,int> src){
        vector<vector<int>> dist(m, vector<int>(n, INF));
        deque<pair<int,int>> dq;
        dist[src.first][src.second]=0;
        dq.push_back(src);
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        while(!dq.empty()){
            auto [x,y]=dq.front(); dq.pop_front();
            for(auto &d:dirs){
                int nx=x+d[0], ny=y+d[1];
                if(nx<0||nx>=m||ny<0||ny>=n) continue;
                if(grid[nx][ny]==1) continue; // blocked
                if(dist[nx][ny]==INF){
                    dist[nx][ny]=dist[x][y]+1;
                    dq.emplace_back(nx,ny);
                }
            }
        }
        return dist;
    };
    if(start.first==-1||home.first==-1||umbrellas.empty()){
        cout<<-1<<"\n";
        return 0;
    }
    auto distStart = bfs(start);
    auto distHome = bfs(home);
    long long ans=LLONG_MAX;
    for(auto &p:umbrellas){
        int d1=distStart[p.first][p.second];
        int d2=distHome[p.first][p.second];
        if(d1==INF||d2==INF) continue;
        ans=min(ans, (long long)d1+d2);
    }
    if(ans==LLONG_MAX) cout<<-1<<"\n";
    else cout<<ans<<"\n";
    return 0;
}
