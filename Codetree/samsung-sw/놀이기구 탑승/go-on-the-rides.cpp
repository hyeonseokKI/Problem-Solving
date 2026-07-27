/*
        1. 좋아하는 학생 4명을 set[x] 에 추가.

        2. 탑승할 구간 탐색.
            2.1. 그 구간에 먼저 타있는 곳 제외
            2.2. 좋아하는 친구가 많은 순 -> 빈칸 많은 순 -> 행 작은 순 -> 열 작은순 탑승

        3. 탑승한 후의 점수의 합은 scores에 인덱스를 활용.
            인접한 곳에 있는 친구들이 나를 좋아하는 친구들인지 cnt로 인덱스 접근.
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 20 + 2 ;
const int SMX = MX * MX ;
// int m = 4;

int n;
int x,n1,n2,n3,n4;

int arr[SMX];
set<int> se[SMX];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int board[MX][MX];

int scores[5] = {0,1,10,100,1000};
int ans;


void go(int cur_num){
    vector<tuple<int,int,int,int>> cand;


    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){
            // 이미 자리 차지.
            if(board[i][j]) continue;
            int e_cnt = 0;
            int f_cnt = 0;
            for(int dir = 0 ; dir < 4 ; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if(board[nx][ny] != 0 && se[cur_num].find(board[nx][ny]) != se[cur_num].end() ) f_cnt++;
                if(board[nx][ny] == 0) e_cnt++;
            }
            cand.push_back({f_cnt,e_cnt,i,j});
        }
    }

    // frind 많이 -> 비어있는 칸 많이 -> 행 번호 작은 위치 -> 열 번호 작은 위치
    sort(cand.begin(),cand.end(),[](const auto& a, const auto& b){

        if(get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
        if(get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
        if(get<2>(a) != get<2>(b)) return get<2>(a) < get<2>(b);
        return get<3>(a) < get<3>(b);
        
    });

    int r,c,f,e;
    tie(f,e,r,c)= cand[0];
    // cout << r << ' ' << c << ' ' << f << ' ' << e << '\n';
    board[r][c] = cur_num;



}



int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n;
    for(int i = 1; i <=n * n; i ++){
        cin >> arr[i] >> n1 >> n2 >> n3 >> n4;
        se[arr[i]].insert(n1);
        se[arr[i]].insert(n2);
        se[arr[i]].insert(n3);
        se[arr[i]].insert(n4);
    }
    // fill_board
    for(int i = 1 ; i <= n * n ; i ++){
        int cur_num = arr[i];
        go(cur_num);
    }
    

    // 0 1 2 3 4 -> 0 1 10 100 1000
    for(int i = 0; i < n ; i ++){
        for(int j = 0 ; j < n ; j ++){

            int cur_num = board[i][j];
            int cnt = 0;
            int tmp = 0;
            for(int dir = 0 ; dir < 4; dir++){
                int nx = i + dx[dir];
                int ny = j + dy[dir];
                if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
                if(se[cur_num].find(board[nx][ny]) == se[cur_num].end()) continue;
                cnt++;
            }
            
            ans += scores[cnt];

        }
    }
    cout << ans;
    




}


