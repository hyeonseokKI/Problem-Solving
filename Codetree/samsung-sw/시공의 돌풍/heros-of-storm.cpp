/*
    Main Logic


        step 1 : 먼지 확산
            확산 가능 체크 - 돌풍 x, 범위 안에 있는지
            가능 갯수 * board 값 /2 -> board 에 반영
            해당 칸에 전파
            
        
        
        
        step 2 : 사공의 돌풍 방향 
            사공의 돌풍은 움직이지 않는다.
            먼지만 위는 반시계, 아래는 시계방향으로 이동 
*/

#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int MX = 50 + 2;

int n,m,t;
int board[MX][MX];
int ans;

// int up_dx[4] = {0, -1, 0, 1};
// int up_dy[4] = {1, 0, -1, 0};
// int down_dx[4] = {0, 1, 0, -1};
// int down_dy[4] = {1, 0, -1, 0};

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

// [0,r1.X], [r2.X,n-1]
int up_row_min = 0;
int up_row_max;     // 첫번쨰 행 인덱스 
int down_row_min;   // 두번째 행 인덱스
int down_row_max;   // n-1

vector<pair<int,int>> winds ;    // 0 : 윗, 1 : 아랫 좌표
void print_board(int arr[MX][MX]);
void print_winds(vector<pair<int,int>> arr);
void test_next_winds();


void next_pos_winds(){
    
        if(winds[0].X == up_row_max && winds[0].Y != m-1) winds[0].Y+=1;
        else if(winds[0].Y == m-1 && winds[0].X != 0 ) winds[0].X -= 1;
        else if(winds[0].X == up_row_min && winds[0].Y != 0) winds[0].Y -=1;
        else if(winds[0].Y == 0 && winds[0].X != up_row_max) winds[0].X +=1;

        // cout << winds[0].X << ' ' << winds[0].Y << '\n';

        if(winds[1].X == down_row_min && winds[1].Y != m-1) winds[1].Y +=1;
        else if(winds[1].Y == m-1 && winds[1].X != down_row_max) winds[1].X+=1;
        else if(winds[1].X == down_row_max && winds[1].Y != 0) winds[1].Y -= 1;
        else if(winds[1].Y == 0 && winds[1].X != down_row_min) winds[1].X -=1;

        // cout << winds[1].X << ' ' << winds[1].Y << '\n';
}

void dust_go(){

    int tmp[MX][MX] = {};

    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < m ; j ++){
            // if(board[i][j] == -1) continue;
            if(winds[0].X == i && winds[0].Y == j) continue;
            if(winds[1].X == i && winds[1].Y == j) continue;
            // cout << i << ' ' << j << '\n';
            int cur_val = board[i][j];
            int cur_gval = board[i][j] / 5 ;
            int cur_cnt = 0;
            for(int dir = 0 ; dir < 4; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                // if(board[nx][ny] == -1) continue;
                if(winds[0].X == nx && winds[0].Y == ny) continue;
                if(winds[1].X == nx && winds[1].Y == ny) continue;
                cur_cnt++;
                tmp[nx][ny] += cur_gval;
            }

            for(int k = 0 ; k < cur_cnt; k++) board[i][j] -= cur_gval;
        }
    }

        
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j <m; j++){
            board[i][j] += tmp[i][j];
        }
    }

}

void winds_go(){
    int tmp[MX][MX] = {};
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < m ; j ++){
            tmp[i][j] = board[i][j];
        }
    }


    for(int c = 1; c < m ; c++){
        board[up_row_max][c] = tmp[up_row_max][c-1];
    }
    for(int r = 0; r < up_row_max; r++){
        board[r][m-1] = tmp[r+1][m-1];
    }
    for (int c = 0 ; c < m - 1 ; c++){
        board[0][c] = tmp[0][c+1];
    }
    for(int r = 1; r < up_row_max; r++){
        board[r][0] = tmp[r-1][0];
    }
    

    for(int c = 1; c < m ; c++){
        board[down_row_min][c] = tmp[down_row_min][c-1];
    }

    // 4 5 
    for(int r = down_row_min+1; r <= down_row_max; r++){
        board[r][m-1] = tmp[r-1][m-1];
    }
    for (int c = 0 ; c < m - 1 ; c++){
        board[down_row_max][c] = tmp[down_row_max][c+1];
    }
    // 원래는 3 4  인데 어차피 지워질거니 4만 
    for(int r = down_row_min + 1; r < down_row_max; r++){
        board[r][0] = tmp[r+1][0];
    }
    
}

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> m >> t;

    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < m ; j ++){
            cin >> board[i][j];
            if(board[i][j] == -1) {
                winds.push_back({i,j});
                board[i][j] = 0;
            }
        }
    }
    // print_board(board);
    // print_winds(winds);

    // set ranges
    up_row_max = winds[0].X;
    down_row_min = winds[1].X;
    down_row_max = n-1;
    // 0,2 ,  3, 5
    // cout << up_row_min << ' ' << up_row_max << '\n' ;
    // cout << down_row_min << ' ' << down_row_max << '\n';

    // 올바르게 돌풍이 도는지 테스트
    // test_next_winds();




    // t 만큼 돌풍 
    for(int i = 1 ; i <=t; i ++){
        
        // 먼지 확산
        dust_go();


        // 돌풍 이동 
        // next_pos_winds();

        // // // 돌풍 해당칸 먼지 제거 
        // board[winds[0].X][winds[0].Y] = 0;
        // board[winds[1].X][winds[1].Y] = 0;

        // 돌풍 이동 
        winds_go();


        // print_board(board);
        
        // break;
    }




    // score 
    // ans += 2;   // 돌풍 -1 포함
    for(int i = 0 ; i <n; i++){
        for(int j = 0 ; j < m; j++){
            ans += board[i][j];
        }
    }


    cout << ans;
    
}




void print_board(int arr[MX][MX]){
    
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < m ; j ++){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';

}

void print_winds(vector<pair<int,int>> arr){
    
    for(auto & a : arr){
        cout << a.X << ' ' << a.Y << '\n';
    }
    cout << '\n';
}

void test_next_winds(){
    for(int i = 1; i <= 16; i++){
        if(winds[0].X == up_row_max && winds[0].Y != m-1) winds[0].Y+=1;
        else if(winds[0].Y == m-1 && winds[0].X != 0 ) winds[0].X -= 1;
        else if(winds[0].X == up_row_min && winds[0].Y != 0) winds[0].Y -=1;
        else if(winds[0].Y == 0 && winds[0].X != up_row_max) winds[0].X +=1;

        // cout << winds[0].X << ' ' << winds[0].Y << '\n';

        if(winds[1].X == down_row_min && winds[1].Y != m-1) winds[1].Y +=1;
        else if(winds[1].Y == m-1 && winds[1].X != down_row_max) winds[1].X+=1;
        else if(winds[1].X == down_row_max && winds[1].Y != 0) winds[1].Y -= 1;
        else if(winds[1].Y == 0 && winds[1].X != down_row_min) winds[1].X -=1;

        // cout << winds[1].X << ' ' << winds[1].Y << '\n';

    }

    
}