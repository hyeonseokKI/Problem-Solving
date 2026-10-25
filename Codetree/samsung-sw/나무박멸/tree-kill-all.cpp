    /*
    Main Logic

        step 0. 고려사항
            제초제는 기한이 있고, 제초제가 남아있으면, 나무가 성장 및 번식을 할 수 없다.

        step 1. 나무의 성장

        step 2. 나무의 번식

        step 3. 제초제 위치 선정 

        step 4. 제초제 뿌리는 작업 


*/
#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int MX = 20 + 2;
int n,m,k,c;


int board[MX][MX];
int herb[MX][MX];
int ans;

void print_board(int arr[MX][MX]);

void grow_up(){

    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n; j ++){
            if(board[i][j] == 0) continue;  // 빈 곳이면 패스 
            if(board[i][j] == -1) continue; //벽이면 패스 
            if(herb[i][j] > 0) continue; // 제초제면 패스
            // cout << board[i][j] << ' ';
            int dx[4] = {1,0,-1,0};
            int dy[4] = {0,1,0,-1};
            int cnt = 0;
            for(int dir = 0 ; dir <4 ; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx < 0 || ny < 0 || nx >=n || ny >= n) continue; // 범위 검사
                // if(board[nx][ny] == 0) continue;  // 빈 곳이면 패스 
                // if(board[nx][ny] == -1) continue; //벽이면 패스 
                // if(board[nx][ny] == ? ) continue; // 제초제면 패스
                if(board[nx][ny] > 0) cnt++;
            }

            board[i][j] += cnt;
            
        }
    }


}

void spread(){


    // 업데이트 후반영
    int tmp[MX][MX] = {};
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            tmp[i][j] = board[i][j];
        }
    }


    for(int i = 0 ; i < n ; i ++){
        for(int j = 0; j < n ; j ++){
            if(board[i][j] == 0) continue;
            if(board[i][j] == -1) continue;
            if(herb[i][j] > 0) continue;
            int dx[4] = {1,0,-1,0};
            int dy[4] = {0,1,0,-1};
            // int cnt = 0;
            vector<pair<int,int>> cands;

            for(int dir = 0 ; dir < 4;  dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx < 0 || ny < 0 || nx >=n || ny >= n) continue; // 범위 검사
                if(board[nx][ny] == 0 && herb[nx][ny] == 0) cands.push_back({nx,ny});
            }

            int cnt = cands.size();
            if(cnt == 0) continue;
            int t_sum = board[i][j] / cnt;
            // cout << "t_sum : " << t_sum << '\n';
            
            for(auto cand : cands){
                tmp[cand.X][cand.Y] += t_sum;
                // cout <<  tmp[cand.X][cand.Y] << ' ';
                // cout << cand.X << ' ' << cand.Y << ' ' << t_sum << '\n';
            }
        }
    }


    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            board[i][j] = tmp[i][j];
        }
    }

}
void spray_down(){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j++){
                if(herb[i][j] > 0) herb[i][j]--;
            }
        }
}


// k = 1 
// {-1,-1,1,1} 
// {-1,1,-1,1}
// k = 2
// {-1,-1,1,1,-2,-2,2,2} 
// {-1,1,-1,1,-2,2,-2,2}
int b_dx[4] = {-1,-1,1,1};
int b_dy[4] = {-1,1,-1,1};
pair<int,int> select_kill(){

    int calc_board[MX][MX]={};
    int max_sum = 0;
    pair<int,int> pos = {-1,-1};

    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n; j ++){
            if(board[i][j] <= 0) continue;
            calc_board[i][j] = board[i][j];
            for(int dir = 0 ; dir < 4 ; dir++){
                for(int dist = 1 ; dist <= k ; dist++){
                    int nx = i + b_dx[dir] * dist;
                    int ny = j + b_dy[dir] * dist;
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n) break;
                    if(board[nx][ny] <= 0) break;
                    calc_board[i][j] += board[nx][ny];
                }
            }
            // 같은 수라면 먼저 탐색한 작은 행, 작은 열을 유지
            if(calc_board[i][j] > max_sum){
                max_sum = calc_board[i][j];
                pos = {i,j};
            }
        }
    }
    return pos;
}


void spray_kill(pair<int,int> pos){
    if(pos.X == -1) return;

    ans += board[pos.X][pos.Y];
    board[pos.X][pos.Y] = 0;
    herb[pos.X][pos.Y] = c;

    for(int dir = 0 ; dir < 4 ; dir++){
        for(int dist = 1 ; dist <= k ; dist++){
            int nx = pos.X + b_dx[dir] * dist;
            int ny = pos.Y + b_dy[dir] * dist;
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) break;
            herb[nx][ny] = c;
            // 빈칸과 벽까지 뿌리되, 그 뒤로는 전파하지 않음
            if(board[nx][ny] <= 0) break;
            ans += board[nx][ny];
            board[nx][ny] = 0;
        }
    }
}


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);


    cin >> n >> m >> k >> c;

    for(int i = 0 ; i < n; i ++){
        for(int j = 0 ; j < n ; j ++){
            cin >> board[i][j];
        }
    }
    // print_board(board);
    

    while(m--){


        // step 1 나무의 성장
        grow_up();

        // step 2. 나무의 번식
        spread();

        // 올해 번식까지 막은 뒤 줄여야 이후 c년 동안 유지됨
        spray_down();

        // step 3. 제초제 위치 선정 
        pair<int,int> pos = select_kill();

        // step 4. 제초제 뿌리는 작업
        spray_kill(pos);
    }







    cout << ans;
}


void print_board(int arr[MX][MX]){
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j++){
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';
}
