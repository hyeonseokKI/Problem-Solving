/*
    Main Logic
        1. 초기 특수영양제는 최하단 4개 영역 배치 
            특수영양제는 높이 1 증가 및 0인 곳 1로 만듦.

        2. 각 해당년도의 이동방향과 칸수 지정됨

        step 1 : 특수 영양제를 이동 규칙에 따라 이동 
        step 2 : 이동 시킨후 특수 영양제 제거 
        step 3 : 대각선 방향에서 1 이상이면 더 성장, 범위 넘어가면 포함x
        step 4 : 이전 특수 영양제 제외하고 기존 리브로수 높이 2인 애들 베어내서 
                특수 영양제로 만듦.
    
        
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 15 + 2;
const int DUMMY = -1;
int n,m;
int d,p;

int board[MX][MX];
bool special_good[MX][MX];

int dx[9] = {DUMMY, 0, -1, -1,  -1, 0,  1,  1,  1};
int dy[9] = {DUMMY, 1, 1,  0,  -1, -1, -1, 0,  1};

int cross_dx[4] = {-1,  1,  1,  -1};
int cross_dy[4] = {1,   1,  -1, -1};

int ans ;


void print_board();
void print_spec(int arr[MX][MX]);
int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n >> m;
    for(int i = 0 ; i < n; i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cin >> board[i][j];
        }
    }

    // 특수영양제 초기 설정 
    special_good[n-1][0] = 1;
    special_good[n-1][1] = 1;
    special_good[n-2][0] = 1;
    special_good[n-2][1] = 1;
    // print_spec();

    int cnt = 0;

    while(m--){
        cin >> d >> p;

        bool tmp[MX][MX] = {};

        // step 1
        for(int i = 0 ; i < n; i ++){
            for(int j = 0 ; j < n ; j ++){
                if(!special_good[i][j]) continue;

                int nx = i + dx[d] * p;
                int ny = j + dy[d] * p;

                nx += n;
                ny += n;
                nx %= n;
                ny %= n;
                tmp[nx][ny] = 1;
            }
        }

        // step 2 
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j < n ; j ++){
                if(!tmp[i][j]) continue;
                board[i][j]++;
            }
        }
        // step 3
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0; j < n ; j ++){
                if(!tmp[i][j]) continue;
                
                for(int dir = 0 ; dir <4 ; dir ++){
                    int nx = i + cross_dx[dir];
                    int ny = j + cross_dy[dir];
                    
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n ) continue;
                    if(board[nx][ny] == 0 ) continue;
                    board[i][j]++;
                }
            }
        }
        // print_board();

        // step 4
        bool tmp2[MX][MX] = {};

        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j < n ; j ++){
                if(tmp[i][j]) continue; // 이미 사용한 특수 영양제 제외
                if(board[i][j] < 2 ) continue; // 높이 2 미만 제외

                tmp2[i][j] = 1; // 다음 특수 영양제 설정
                board[i][j] -= 2;
            }
        }

        // debug
        // for(int i = 0 ; i < n; i ++){
        //     for(int j = 0 ; j < n ; j ++){
        //         cout << tmp[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';

        // for debug
        // cnt ++ ;
        // if(cnt == 3) break;
        

        // 특수영양제 갱신
        for(int i = 0 ; i < n ; i ++ ){
            for(int j = 0 ; j < n ; j ++){
                special_good[i][j] = tmp2[i][j];
            }
        }

        // print_board();
    }


    for(int i =0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            ans += board[i][j];
        }
    }

    cout << ans;
    
}

void print_board(){
    for(int i = 0 ; i < n; i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cout <<  board[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';

}
void print_spec(int arr[MX][MX]){
    for(int i = 0 ; i < n; i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cout <<  arr[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';

}
