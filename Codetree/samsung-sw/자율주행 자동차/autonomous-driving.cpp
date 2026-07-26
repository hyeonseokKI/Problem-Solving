/*
    문제 입,출력

    문제 방향
*/

#include<bits/stdc++.h>
using namespace std;

int n,m;
int d,x,y;
int board[52][52];
bool vis[52][52];
bool ismove;

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

int ans;

void debug_board(){
    cout << "cur x,y  : "  << x << ' ' << y << '\n';
    cout << "cur d : " << d << '\n';
    
    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < m; j ++){
            if(board[i][j] == 1) cout << "w ";
            else cout << vis[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';
}


bool go(){
    int cur_x = x;
    int cur_y = y;

    for(int dir = 0 ; dir < 4 ; dir ++){
        d = (d + 3) % 4;
        int nx = cur_x + dx[d ];
        int ny = cur_y + dy[d ];
        // cout << nx << ' ' <<ny << ' ' << (d+dir)%4<< '\n';
        if(nx < 0 || ny < 0 || nx >= n || ny >=m) continue;
        if(board[nx][ny] == 1) continue;
        if(vis[nx][ny]) continue;
        vis[nx][ny] = 1;
        x = nx;
        y = ny;
        return true;
    }
    // 후진 상황
    int bx = cur_x - dx[d] ;
    int by = cur_y - dy[d] ;
    // 후진 조차 못하는 상황 
    if(bx < 0 || by < 0 || bx >=n || by >=m) return false;
    if(board[bx][by] == 1) return false;

    x = bx;
    y = by;
    return true;
    
    


}

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);


    cin >> n >> m;
    cin >> x >> y >> d;
    

    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < m ; j ++){
            cin >> board[i][j];
        }
    }

    
    vis[x][y] = 1;
    
    while(1){
        ismove = go();
        if(!ismove) break;

        // debug_board();
    }


    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < m; j ++){
            if(vis[i][j]) ans++;
        }
    }
    cout << ans;


    
}
