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
// bool vis[MX][MX];
int dist[MX][MX];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

bool is_moved;
int ans;
void print_board(int arr[MX][MX]);

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> l >> r;

    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < n ; j ++ ){
            cin >> board[i][j];
        }
    }



    while(true){
        is_moved = false;
        for(int i = 0 ; i < n; i ++) fill(dist[i],dist[i]+n,-1);
        int idx = 0;
        vector<pair<int,int>> g_idx[MX*MX];
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                queue<pair<int,int>> q;

                if(dist[i][j] != -1) continue;
                q.push({i,j});
                g_idx[idx].push_back({i,j});
                dist[i][j]=idx++;

                while(!q.empty()){
                    auto cur = q.front(); q.pop();
                    for(int dir = 0 ; dir <4 ; dir++){
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if(nx < 0 || ny < 0 || nx >= n || ny >= n )continue;
                        if(dist[nx][ny] != -1) continue;
                        int diff = abs(board[cur.X][cur.Y] - board[nx][ny]);
                        if(diff < l || diff > r) continue;
                        q.push({nx,ny});
                        dist[nx][ny] = dist[cur.X][cur.Y];
                        g_idx[dist[cur.X][cur.Y]].push_back({nx,ny});

                    }
                    
                }

            }
        }

        for(int i = 0 ; i < idx; i++){
            if(g_idx[i].size() <= 1) continue;

            int tot = 0;
            for(auto& cur : g_idx[i]){
                tot += board[cur.X][cur.Y];
            }
            tot /= g_idx[i].size();
            for(auto& cur : g_idx[i]){
                board[cur.X][cur.Y] = tot;
            }

            is_moved = true;


        }

        // print_board(board);

        if(!is_moved) break;
        ans++;
    

    }




    




    cout << ans;
    
}


void print_board(int arr[MX][MX]){

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';


}