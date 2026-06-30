#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

int n,m;
int board[10][10];
bool vis[10][10];
pair<int,int> points[100];
vector<pair<int,int>> paths[100'001];
int idx;
vector<pair<int,int>> path;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int ans;
void solve(int curX, int curY){
    path.push_back({curX,curY});
    if(curX == points[m-1].X && curY == points[m-1].Y) {
        for(auto p : path) paths[idx].push_back({p.X,p.Y});
        idx++;
        return;
    }
    
    for(int dir = 0 ; dir < 4 ; dir ++){
        int nx = curX + dx[dir];
        int ny = curY + dy[dir];
        if(nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
        if(board[nx][ny]) continue;
        if(vis[nx][ny]) continue;
        vis[nx][ny] = 1;
        solve(nx,ny);
        vis[nx][ny] = 0;
        path.pop_back();
    }

}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    
    for(int i = 1 ; i <=n ; i++){
        for(int j = 1 ; j <=n; j ++){
            cin >> board[i][j];
        }
    }

    for(int i = 0 ; i < m ; i ++){
        cin >> points[i].X >> points[i].Y;
    }

    // for(int i = 0 ; i < m ; i ++){
    //     cout << points[i].X << ' ' <<  points[i].Y << '\n';
    // }

    vis[points[0].X][points[0].Y] = 1;
    solve(points[0].X,points[0].Y);


    // for(int i = 0 ; i < idx ; i ++){
    //     for(auto ps : paths[i]) cout << ps.X << ' ' << ps.Y << "  ";
    //     cout << '\n';
    // }


    // 1 ~ m - 1 까지 안에 들어가 있는지 확인 
    for(int i = 0; i < idx  ; i ++){
        int idx2 = 1;
        pair<int,int> cur = points[idx2] ;
        int cnt = 1;
        for(int j = 0 ; j < paths[i].size(); j ++){
            if(paths[i][j].X == cur.X &&  paths[i][j].Y == cur.Y){
                cnt ++;
                cur = points[++idx2]; 
            }
            // if(point)
        }
        // cout << cnt << '\n';

        if(cnt == m) ans ++;
        // cout << '\n';

    }



    cout << ans;
    // cout << "TEST\n";
    
    return 0;
}