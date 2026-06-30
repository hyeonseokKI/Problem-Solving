#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

int n, m;
int board[10][10];
bool vis[10][10];
pair<int, int> points[100];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int ans;

void solve(int curX, int curY, int t_idx) {
    if(curX == points[t_idx].X && curY == points[t_idx].Y){
        if(t_idx == m -1){
            ans++;
            return;
        }
        t_idx++;
    }

    for(int dir = 0 ; dir < 4 ; dir ++){
        int nx = curX + dx[dir];
        int ny = curY + dy[dir];
        if(nx <= 0 || ny <= 0 || nx > n || ny > n) continue;
        if(board[nx][ny]) continue;
        if(vis[nx][ny])continue;
        
        vis[nx][ny] = 1;
        solve(nx,ny,t_idx);
        vis[nx][ny] = 0;
    }


}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        cin >> points[i].X >> points[i].Y;
    }

    vis[points[0].X][points[0].Y] = 1;
    solve(points[0].X, points[0].Y, 1);

    cout << ans;
    
    return 0;
}