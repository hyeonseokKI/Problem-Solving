/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int MX = 50 + 2;

int n,l,r;
int board[MX][MX];
int dist[MX][MX];   // -1 : 방문 x , 

int dx[4]= {1,0,-1,0};
int dy[4]= {0,1,0,-1};

bool is_moved = true;
int ans;

void print_board(int arr[MX][MX]);

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> l >> r;
    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cin >> board[i][j];
        }
    }

    // print_board(board);  // debug


    while(1){
        is_moved = false;
        
        int idx = 1;

        for(int i = 0 ; i < n ; i++ ) fill(dist[i],dist[i]+MX,-1);
        vector<pair<int,int>> g_num[MX*MX];
        for(int i = 0 ; i < n ; i ++ ){
            for(int j = 0 ; j < n ; j ++){
                if(dist[i][j] != -1) continue;  // 방문했다면 패스
                
                queue<pair<int,int>> q; 
                q.push({i,j});
                g_num[idx].push_back({i,j});
                dist[i][j] = idx++;
                while(!q.empty()){
                    auto cur = q.front(); q.pop();
                    for(int dir = 0 ; dir < 4 ; dir++){
                        int nx = cur.X + dx[dir] ;
                        int ny = cur.Y + dy[dir];
                        if(nx < 0 || ny < 0 || nx >= n || ny >= n ) continue;
                        if(dist[nx][ny] != -1) continue;
                        if(abs(board[cur.X][cur.Y] - board[nx][ny]) < l ) continue;
                        if(abs(board[cur.X][cur.Y] - board[nx][ny]) > r ) continue;
                        q.push({nx,ny});                        
                        dist[nx][ny] = dist[cur.X][cur.Y];
                        g_num[dist[cur.X][cur.Y]].push_back({nx,ny});
                        is_moved = true;
                    }
                }

            }
        }

        // 계란 옮기기 , 소숫점 버림

        for(int i = 1; i < idx; i ++){
            int tmp = 0 ;
            
            for(auto &v : g_num[i]){
                tmp += board[v.X][v.Y];
            }
            tmp /= g_num[i].size();

            for(auto &v : g_num[i]){
                board[v.X][v.Y] = tmp;
            }
            // cout << tmp  << '\n';


        }
        // print_board(board);
        // break;
        if(!is_moved) break;
        ans++;
    }


    cout << ans ;
    
}


void print_board(int arr[MX][MX]){
    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
}