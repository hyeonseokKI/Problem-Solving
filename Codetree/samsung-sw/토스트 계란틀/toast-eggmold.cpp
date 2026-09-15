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
bool vis[MX][MX];

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
        for(int i = 0 ; i < n; i ++) fill(vis[i],vis[i]+n,0);
        
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                queue<pair<int,int>> q;
                vector<pair<int,int>> cand;
                int sum = 0;
                if(vis[i][j]) continue;
                
                q.push({i,j});
                vis[i][j]=1;
                sum += board[i][j];
                cand.push_back({i,j});

                while(!q.empty()){
                    auto cur = q.front(); q.pop();
                    for(int dir = 0 ; dir <4 ; dir++){
                        int nx = cur.X + dx[dir];
                        int ny = cur.Y + dy[dir];
                        if(nx < 0 || ny < 0 || nx >= n || ny >= n )continue;
                        if(vis[nx][ny]) continue;
                        int diff = abs(board[cur.X][cur.Y] - board[nx][ny]);
                        if(diff < l || diff > r) continue;
                        q.push({nx,ny});
                        vis[nx][ny] = 1;
                        sum += board[nx][ny];
                        cand.push_back({nx,ny});
                    }
                    
                }

                int tot = sum / (int)cand.size();
                for(auto& c : cand){
                    board[c.X][c.Y] = tot;                 
                }
                if(cand.size() > 1)  is_moved =true;
            }
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