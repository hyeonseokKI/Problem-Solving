/*
    문제 입,출력

    문제 방향

        1. 
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

int ans;
void ans_test();
void print_board(int arr[MX][MX]);


void go(int cur_num){
    // int mx_friend = 0;
    // int mx_cnt = 0;
    // vector<pair<int,int>> cand;


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
        if(get<3>(a) != get<3>(b)) return get<3>(a) < get<3>(b);
        
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

    // for(int i = 1 ; i <= n * n ; i ++){
    //     cout << arr[i] << ' ';
    //     for(auto s : se[arr[i]]){
    //         cout << s << ' ';
    //     }
    //     cout << '\n';
    // }


    // fill_board
    for(int i = 1 ; i <= n * n ; i ++){
        int cur_num = arr[i];
        // cout << cur_num << '\n';
        go(cur_num);


        // print_board(board);
    }
    
    // ans_test();

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
            
            if(cnt == 0) tmp = 0;
            else if(cnt == 1 ) tmp = 1;
            else if(cnt == 2) tmp = 10;
            else if(cnt == 3) tmp = 100;
            else if(cnt == 4) tmp = 1000;
            ans += tmp;

            // cout << "i, j, cnt : " << i << ' ' << j << ' ' << cnt << '\n';
        }
    }
    cout << ans;
    

    // tuple_test;
    // tuple<int,int,int,int> t = {1,2,3,4};
    // cout << get<3>(t) << ' ';



}




void ans_test(){


    board[0][0] = 1;
    board[0][1] = 6;
    board[0][2] = 4;

    board[1][0] = 8;
    board[1][1] = 3;
    board[1][2] = 7;

    board[2][0] = 9;
    board[2][1] = 2;
    board[2][2] = 5;

}

void print_board(int arr[MX][MX]){

    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n; j ++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }

    cout << '\n';
}
