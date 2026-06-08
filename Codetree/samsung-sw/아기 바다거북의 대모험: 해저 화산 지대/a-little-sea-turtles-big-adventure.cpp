/*
    Main Logic

        1. 바다 거북이 이동
            board : 0 이동 가능 1 산호초, 2 거북이, 3 죽은 거북이  4  화산 
            
            1번 거북이 부터 각각 bfs 돌려서 n-1,m-1 까지 도달 가능한지 확인
            가능하면 depth가 가장 작은 것들 중 
                우(→), 하(↓), 좌(←), 상(↑) 순으로 이동

        step 2. 화산 압력 증가
            모든 화산 압력 증가시키기

        step 3. 화산 분출 + 연쇄


        ! 거북이 이동 경로 따로 저장 
*/

#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int MX_TURN = 100;
const int MX_N = 20 + 2;
const int MX_M = 10 + 2;
const int MX_K = 10 + 2;

const int READY = 1;
const int DEAD = 2;
const int ARRIVE = 3;

int n,m,k;
int turn ;
int board[MX_N][MX_N];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

pair<int,int> turtle_id [MX_M];  
int turtle_idx [MX_N][MX_N];
int turtle_state[MX_M];     // 상태확인

pair<int,int> mf_val[MX_N][MX_N];
pair<int,int> mf_idx[MX_K];
bool mf_isexist[MX_N][MX_N];
int mf_board[MX_N][MX_N];

int ans[MX_M];

void print_board(){
        for(int i = 0; i < n ;i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';

}

pair<int,int> move(int  idx){
    int cx,cy;
    tie(cx,cy) = turtle_id[idx];
    bool is_find = false;
    vector<tuple<int,int,int>> path;
    queue<pair<int,int>> q;
    int dist[n+1][n+1] = {};
    for(int i = 0 ; i < n ; i++) fill(dist[i],dist[i]+n,-1);

    q.push({n-1,n-1});
    dist[n-1][n-1] = 0;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        path.push_back({cur.X,cur.Y,dist[cur.X][cur.Y]});
        for(int dir = 0 ; dir < 4; dir++){
            int nx = cur.X + dx[dir];
            int ny = cur.Y + dy[dir];
            if(nx == cx && ny == cy) {
                dist[nx][ny] = dist[cur.X][cur.Y] + 1;
                is_find = true;
                // break;
            }
            if(nx < 0 || ny < 0 || nx >= n || ny >=n) continue;
            if(dist[nx][ny] != -1) continue;
            // if(board[nx][ny] == 1 || board[nx][ny] == 2 || board[nx][ny] == 3  ) continue;
            if(board[nx][ny]) continue;
            q.push({nx,ny});
            dist[nx][ny] = dist[cur.X][cur.Y] + 1;
        }
    }

    

    if(dist[cx][cy] == -1)return {-1,-1};   // is_find == false
    
    //     cout << dist[cx][cy+1] << '\n';
    //     cout << dist[cx+1][cy] << '\n';
    //     cout << dist[cx][cy-1] << '\n';
    //     cout <<  dist[cx-1][cy] << '\n';

    // for(int i = 0 ; i < n ; i ++ ){
    //     for(int j = 0 ; j < n ; j++){
    //         cout << dist[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    pair<int,int> best_way = {-1,-1};
    int mn = 0x3f3f3f3f;
    vector<pair<int,int>> cand;

    // 우(→), 하(↓), 좌(←), 상(↑) 순으로 검색
    for(int i = 0 ; i < 4; i ++){
        int nx = cx + dx[i];
        int ny = cy + dy[i];
        if(nx < 0 || ny < 0 || nx >= n || ny >=n) continue;

        if(dist[nx][ny] == -1) continue;
        if(mn > dist[nx][ny]) {
            best_way = {nx, ny}; 
            mn = dist[nx][ny];
        }
        // if(mn > dist[nx][ny]) {best_way = {nx,ny}; mn = dist[nx][ny];}
        // else if(mn == dist[nx][ny] && best_way.Y < ny ) {best_way = {nx,ny}; mn = dist[nx][ny];}
        // else if(mn == dist[nx][ny] && best_way.X < nx ) {best_way = {nx,ny}; mn = dist[nx][ny];}
        
    }
    return best_way;
    // // 우(→), 하(↓), 좌(←), 상(↑) 순으로 이동
    // if(cy+1 < n && dist[cx][cy+1] != -1 ) return {cx,cy+1};
    // else if(cx+1 < n && dist[cx+1][cy] != -1) return {cx+1,cy};
    // else if(cy-1 >=0 && dist[cx][cy-1] != -1) return {cx,cy-1};
    // else if(cx-1 >=0 && dist[cx-1][cy] != -1) return {cx-1,cy};




    
}


void turtle_move(){
    for(int i = 1; i <= m ; i ++){
        
        if(turtle_state[i] != READY) continue;    // 이동 가능한 후보들만(화석,도착 제외)
        int nxt_r,nxt_c;
        tie(nxt_r,nxt_c) = move(i);


        // cout << i << ' ' << nxt_r << ' ' << nxt_c << '\n' << '\n';
        if(nxt_r == -1) continue;   // 이동 불가
        

       
        board[turtle_id[i].X][turtle_id[i].Y] = 0;
        turtle_idx[turtle_id[i].X][turtle_id[i].Y] = 0;
        turtle_id[i].X = nxt_r;
        turtle_id[i].Y = nxt_c;
        board[turtle_id[i].X][turtle_id[i].Y] = 2;
        turtle_idx[turtle_id[i].X][turtle_id[i].Y] = i;

        

        if(turtle_id[i].X == n -1 && turtle_id[i].Y == n -1){
             turtle_state[i] = ARRIVE;
             board[n-1][n-1] = 0;
             ans[i] = turn;
        }
        

    }


}





    queue<pair<int,int>> magmaQ;
int test_idx;
void magma_up(){
    test_idx++;
    for(int i = 0 ; i < k ; i ++){
        int r,c;
        tie(r , c) = mf_idx[i] ;
        mf_val[r][c].X += 10;
        
        if(mf_val[r][c].X >= mf_val[r][c].Y) { 
            magmaQ.push({r,c});}
    }
}

vector<pair<int,int>> explored_magma;

bool magma_explore(){
    if(magmaQ.empty()) return 0;
    
    bool vis[MX_N][MX_N] = {};
    while(!magmaQ.empty()){
        auto cur = magmaQ.front(); magmaQ.pop();

        if(vis[cur.X][cur.Y]) continue;
        vis[cur.X][cur.Y] = 1;
        mf_board[cur.X][cur.Y] += mf_val[cur.X][cur.Y].Y;

        explored_magma.push_back({cur.X,cur.Y});
        for(int dir = 0 ; dir < 4; dir++){
            int nx = cur.X,ny = cur.Y;
            int nval = mf_val[cur.X][cur.Y].Y; 
            
            while(1){
                nx  += dx[dir]; ny += dy[dir];
                nval /=2;
                if (nval == 0) break;
                if(nx < 0 || ny < 0 || nx >= n || ny >=n) break;
                if(board[nx][ny] == 1) break;
                // 열기 전파
                mf_board[nx][ny] += nval;
                // 연쇄 반응
                if(vis[nx][ny] == 0  &&mf_isexist[nx][ny] && mf_board[nx][ny] + mf_val[nx][ny].X >= mf_val[nx][ny].Y) {
                    magmaQ.push({nx,ny});
                }
            }
        }
    }
    // 바다거북의 위기(화석화)
    for(int i = 0 ; i < n ; i++ ){
        for(int j = 0 ; j < n ; j ++){
            if(mf_board[i][j] >= 20 && board[i][j] == 2){
                board[i][j] = 3;
                turtle_state[turtle_idx[i][j]]  = DEAD;
                // cout<< "TEST : " << i << ' ' << j << ' ' << turtle_idx[i][j]<< '\n'; 
            }
        }
    }


    // for(int i = 0 ; i < n ; i ++){
    //     for(int j = 0 ; j < n ; j++){
    //         cout << mf_board[i][j] << ' ';
    //     }
    //     cout << '\n';
    // } cout << '\n';

    // print_board();
    return 1;
}
void magma_reset(){

    for(auto ex : explored_magma)   mf_val[ex.X][ex.Y].X = 0;
    explored_magma.clear();
    for(int i = 0 ; i < n ; i ++ )fill(mf_board[i],mf_board[i]+n,0);
    
}



int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n >> m >> k;
    // fill(ans,ans+n,0);
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j++){
            cin >> board[i][j];
        }
    }
    
    for(int i = 1; i <= m; i ++) {
        cin >> turtle_id[i].X  >> turtle_id[i].Y;
        turtle_state[i] = READY;
        board[turtle_id[i].X][turtle_id[i].Y] = 2;
        turtle_idx[turtle_id[i].X][turtle_id[i].Y] = i;
    }
    

    
    for(int i = 0 ; i < k ; i ++){
        int r,c,mft;
        cin >> r >> c >> mft ;
        mf_val[r][c] = {0,mft};
        mf_idx[i] = {r,c};
        // board[r][c] = 4;
        mf_isexist[r][c] =1;
    }
    //여기 까지 검증 완료.
    
    // for(int turn = 1; turn <= MX_TURN; turn++){
        turn = 0;
        while(turn <= MX_TURN){
        turn++;
        // print_board();
        turtle_move();

        magma_up();
        
        
        bool is_explore = magma_explore();

        // print_board();

        // // 분출하지 않으면 넘어감.
        if(!is_explore)  continue; 

        // cout << turn << '\n';
        magma_reset();

         
        
        // if(turn == 10)break;
    }

    
    for(int i = 1; i <= m ; i ++ ) {
        if(turtle_state[i] == ARRIVE)cout << ans[i] << '\n';
        else cout << -1 << '\n';
    }
}

