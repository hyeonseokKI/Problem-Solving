/*
    Main Logic
        
        step 1 : 청소기 이동
            이동 거리가 가까운 "오염"된 격자 이동
            board[i][j] == -1 이거나 pos_board[i][j] != 0 이동 불가
            최소 이동 횟수 이므로, 최대 후보 4개
            위,왼,오른,아래 순으로 설정.


        step 2 : 청소

            4개의 방향 중 최대 값 선택, 같을 시 오,아,왼,위 순으로 선택
            청소 순서대로 정리됨.

        step 3 : 먼지 축척 
            board 가 -1, 0 이 아닌 부분만 +5

        step 4 : 먼지 확산
            board 가 -1 이 아니고 0인 부분에서 == 깨끗한 격자에서 
             4방향 격자의 먼지량 합 의 / 10 추가 
*/

#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int MX = 30 + 2;
const int MXK = 50 + 2;

int n, k, l;
int board[MX][MX];

int pos_board[MX][MX];
pair<int,int> id2pos[MXK];

int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};


void print_board(int arr[MX][MX]);
void print_cleaner(pair<int,int> arr[MXK]);
void cleaner_move(){

    int dist[MX][MX] = {};

    for(int i = 1 ; i<=k; i++){
        
        // 시작 좌표 설정
        int cur_x, cur_y;
        tie(cur_x,cur_y) = id2pos[i];
        
        if(board[cur_x][cur_y] > 0 ) continue;  // missing point
        for(int j = 1 ; j <=n; j++) fill(dist[j],dist[j]+n+1,-1);
        vector<pair<int,int>> dist_pos[MX * MX + 1] ;
        queue<pair<int,int>> q;
        dist[cur_x][cur_y] = 0;
        
        q.push({cur_x,cur_y});
        // 찾을때 보면, 먼지 없는 경우는 그냥 이동, 먼지 있는 경우는 스탑.
        while(!q.empty() ){
            auto cur = q.front(); q.pop();
            // cout << cur.X << ' ' <<cur.Y << '\n';
            for(int dir = 0 ; dir <4 ; dir++){
                int nx = cur.X + dx[dir];
                int ny = cur.Y + dy[dir];
                if(nx <= 0 || ny <= 0 || nx > n || ny > n ) continue;
                if(pos_board[nx][ny] != 0) continue;    // 청소기여부
                if(board[nx][ny] == -1) continue;   // 격자여부
                if(dist[nx][ny] != -1) continue; // 방문여부 


                q.push({nx,ny});
                dist[nx][ny] = dist[cur.X][cur.Y] + 1;
                // board[nx][ny] 가 먼지 있는 곳만
                if(board[nx][ny] == 0)  continue;
                dist_pos[dist[nx][ny]].push_back({nx,ny});
            }
            
        }

        // dist_pos 는 0이 아닌 먼지만 있는 곳만 있음.
        // for(int j = 1 ; j <= MX; j++){
        //     for(auto dp : dist_pos[j]){
        //         cout << dp.X << ' ' <<dp.Y << '\n';
        //     }
        // }
        // cout << '\n';

        for(int j = 1; j<= MX * MX; j++){
            if(dist_pos[j].empty()) continue;
            
            sort(dist_pos[j].begin(),dist_pos[j].end());
            
            // cout  << dist_pos[j][0].X << ' ' << dist_pos[j][0].Y << '\n';
            pos_board[dist_pos[j][0].X][dist_pos[j][0].Y] = pos_board[cur_x][cur_y];
            pos_board[cur_x][cur_y] = 0;
            // cout << id2pos[i].X << ' '  << id2pos[i].Y <<'\n';
            id2pos[i] = {dist_pos[j][0].X,dist_pos[j][0].Y};
            break;
        }


    }


}

void clean_up(){
    // print_cleaner(id2pos);
    
    for(int i = 1 ; i <= k; i++){
        
        int cur_x,cur_y;
        tie(cur_x,cur_y) = id2pos[i];
        


            // 오른쪽, 아래쪽, 왼쪽, 위쪽의 점수 합의, 배열
        vector<pair<int,int>> dir_val;
        
        int up_val,down_val,left_val,right_val;
        int cur_val = min(20,board[cur_x][cur_y]);
        up_val = down_val = left_val = right_val = 0;
        // cout << up_val << '\n';
        if((cur_x - 1 >= 1 && cur_y >= 1 && cur_x - 1 <= n && cur_y <= n) && (board[cur_x-1][cur_y] != -1 )) up_val = min(20,board[cur_x-1][cur_y]);
        if((cur_x + 1 >= 1 && cur_y >= 1 && cur_x + 1 <= n && cur_y <= n) && (board[cur_x+1][cur_y] != -1 )) down_val = min(20,board[cur_x+1][cur_y]);
        if((cur_x >= 1 && cur_y + 1 >= 1 && cur_x <= n && cur_y + 1 <= n) && (board[cur_x][cur_y + 1] != -1 )) right_val = min(20,board[cur_x][cur_y + 1]);
        if((cur_x >= 1 && cur_y - 1>= 1 && cur_x <= n && cur_y - 1 <= n) && (board[cur_x][cur_y - 1] != -1 )) left_val = min(20,board[cur_x][cur_y - 1]);

        // 오 4, 아 3, 왼, 2, 위 1
        dir_val.push_back({cur_val + up_val + down_val + right_val,4});
        dir_val.push_back({cur_val + left_val + down_val + right_val,3});
        dir_val.push_back({cur_val + left_val + up_val + down_val,2});
        dir_val.push_back({cur_val + left_val + up_val + right_val,1}); 



        sort(dir_val.begin(),dir_val.end(),greater<>());
        // for(auto d : dir_val) cout << d.X << ' ' << d.Y << '\n';
        
        int sel_val,sel_dir ;
        tie(sel_val,sel_dir) = dir_val[0];

        // 청소 
        
        if(sel_dir == 4){
            board[cur_x][cur_y] = board[cur_x][cur_y] - min(20,board[cur_x][cur_y]);
            if((cur_x - 1 >= 1 && cur_y >= 1 && cur_x - 1 <= n && cur_y <= n) && (board[cur_x-1][cur_y] != -1 ))  board[cur_x-1][cur_y] =  board[cur_x-1][cur_y] - min(20,board[cur_x-1][cur_y]);
            if((cur_x + 1 >= 1 && cur_y >= 1 && cur_x + 1 <= n && cur_y <= n) && (board[cur_x+1][cur_y] != -1 )) board[cur_x+1][cur_y] =  board[cur_x+1][cur_y] - min(20,board[cur_x+1][cur_y]);
            if((cur_x >= 1 && cur_y + 1 >= 1 && cur_x <= n && cur_y + 1 <= n) && (board[cur_x][cur_y + 1] != -1 )) board[cur_x][cur_y+1] =  board[cur_x][cur_y+1]- min(20,board[cur_x][cur_y+1]);
            // if((cur_x >= 1 && cur_y - 1>= 1 && cur_x <= n && cur_y - 1 <= n) && (board[cur_x][cur_y - 1] != -1 )) board[cur_x][cur_y - 1] =  board[cur_x][cur_y - 1] - min(20,board[cur_x][cur_y - 1]); 

        } else if(sel_dir == 3){
            board[cur_x][cur_y] = board[cur_x][cur_y] - min(20,board[cur_x][cur_y]);
            if((cur_x + 1 >= 1 && cur_y >= 1 && cur_x + 1 <= n && cur_y <= n) && (board[cur_x+1][cur_y] != -1 )) board[cur_x+1][cur_y] =  board[cur_x+1][cur_y] - min(20,board[cur_x+1][cur_y]);
            if((cur_x >= 1 && cur_y + 1 >= 1 && cur_x <= n && cur_y + 1 <= n) && (board[cur_x][cur_y + 1] != -1 )) board[cur_x][cur_y+1] =  board[cur_x][cur_y+1]- min(20,board[cur_x][cur_y+1]);
            if((cur_x >= 1 && cur_y - 1>= 1 && cur_x <= n && cur_y - 1 <= n) && (board[cur_x][cur_y - 1] != -1 )) board[cur_x][cur_y - 1] =  board[cur_x][cur_y - 1] - min(20,board[cur_x][cur_y - 1]); 

        } else if(sel_dir == 2){
            board[cur_x][cur_y] = board[cur_x][cur_y] - min(20,board[cur_x][cur_y]);
            if((cur_x - 1 >= 1 && cur_y >= 1 && cur_x - 1 <= n && cur_y <= n) && (board[cur_x-1][cur_y] != -1 ))  board[cur_x-1][cur_y] =  board[cur_x-1][cur_y] - min(20,board[cur_x-1][cur_y]);
            if((cur_x + 1 >= 1 && cur_y >= 1 && cur_x + 1 <= n && cur_y <= n) && (board[cur_x+1][cur_y] != -1 )) board[cur_x+1][cur_y] =  board[cur_x+1][cur_y] - min(20,board[cur_x+1][cur_y]);
            if((cur_x >= 1 && cur_y - 1>= 1 && cur_x <= n && cur_y - 1 <= n) && (board[cur_x][cur_y - 1] != -1 )) board[cur_x][cur_y - 1] =  board[cur_x][cur_y - 1] - min(20,board[cur_x][cur_y - 1]); 

        } else if(sel_dir == 1){
            board[cur_x][cur_y] = board[cur_x][cur_y] - min(20,board[cur_x][cur_y]);
            if((cur_x - 1 >= 1 && cur_y >= 1 && cur_x - 1 <= n && cur_y <= n) && (board[cur_x-1][cur_y] != -1 ))  board[cur_x-1][cur_y] =  board[cur_x-1][cur_y] - min(20,board[cur_x-1][cur_y]);
            if((cur_x >= 1 && cur_y + 1 >= 1 && cur_x <= n && cur_y + 1 <= n) && (board[cur_x][cur_y + 1] != -1 )) board[cur_x][cur_y+1] =  board[cur_x][cur_y+1]- min(20,board[cur_x][cur_y+1]);
            if((cur_x >= 1 && cur_y - 1>= 1 && cur_x <= n && cur_y - 1 <= n) && (board[cur_x][cur_y - 1] != -1 )) board[cur_x][cur_y - 1] =  board[cur_x][cur_y - 1] - min(20,board[cur_x][cur_y - 1]); 
        }

    }



}


void dust_add(){

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <=n ; j++){
            if(board[i][j] == -1 ) continue;
            if(board[i][j] == 0) continue;
            board[i][j] += 5;
        }
    }
}
void dust_poll(){
    
    int tmp[MX][MX] ={};
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(board[i][j] == -1) continue; // 물건 위치 제외
            if(board[i][j] != 0) continue;  // 먼지 격자 제외
            
            int sum_val = 0;
            for(int dir = 0 ; dir < 4; dir ++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx <= 0 || ny <= 0 || nx > n || ny > n ) continue;
                if(board[nx][ny] == -1) continue;   // 물건 위치 제외
                if(board[nx][ny] == 0) continue;    // 빈 격자 제외 
                sum_val += board[nx][ny] ;
                // int poll_val = board[nx][ny] / 10;
            }
            tmp[i][j] = sum_val / 10;

        }
    }

    // 확산

    for(int i = 1 ; i <=n ; i++){
        for(int j = 1 ; j<=n; j++){
            board[i][j] += tmp[i][j];
        }
    }


}

void print_ans(){

    int ans = 0;
    for(int i = 1 ; i <= n ; i++){
        for(int j= 1 ; j <= n ; j++){
            if(board[i][j] == -1) continue;
            ans += board[i][j];
        }
    }
    cout << ans << '\n';
}


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> k >> l;

    for(int i = 1; i <=n;i++){
        for(int j = 1 ; j<=n;j++){
            cin >> board[i][j];
        }
    }
    
    for(int i = 1 ; i <=k; i++){
        int x,y;
        cin >> x >> y;
        pos_board[x][y] = i;
        id2pos[i] = {x,y};
    }


    // test print
    // print_board(board);
    // print_cleaner(id2pos);

    while(l--){


        // print_cleaner(id2pos);
        cleaner_move();
        // print_cleaner(id2pos);

        clean_up();
        // print_board(board);

        dust_add();
        // print_board(board);

        dust_poll();
        print_ans();

        // print_board(board);
        // break;  // test
    }
    
}


void print_board(int arr[MX][MX]){
    
    cout <<"######## print_board ########\n";
    for(int i = 1; i <=n;i++){
        for(int j = 1 ; j<=n;j++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    cout <<"###############################\n";

    cout << '\n';
}

void print_cleaner(pair<int,int> arr[MXK]){
    cout <<"######## print_cleaner ########\n";
    
    for(int i = 1 ; i <=k ;i++){
        cout << arr[i].X << ' ' << arr[i].Y << '\n';
    }
    cout <<"###############################\n\n";

}