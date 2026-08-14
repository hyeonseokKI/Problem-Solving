/*
    Main Logic

        ? 회전을 안했을경우, 전파가 되는지

        1. N : 1 , S : 0 
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 4 + 1;

int board[MX][8];
int k,m,d;

int ans;
void print_board(int arr[MX][8]);
void rot_test();
int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    for(int i = 1 ; i <= 4; i ++){
        for(int j = 0 ; j < 8; j ++){
            char c;
            cin >> c;
            board[i][j] = c - '0';
        }
    }

    cin >> k;
    while(k--){
        cin >> m >> d;

        int rot_dir[5] = {};
        rot_dir[m] = d;

        // -> 방향 1,2 / 2,3 / 3,4
        for(int i = m ; i < 4; i ++){
            if(board[i][2] == board[i+1][6]) break;
            rot_dir[i+1] = rot_dir[i] * -1;
        }
        // <- 방향 4,3 / 3,2/ 2,1
        for(int i = m ; i >=2; i--){
            if(board[i][6] == board[i-1][2]) break;
            rot_dir[i-1] = rot_dir[i] * -1;
        }
        


        for(int i = 1 ; i <= 4; i ++) {
            if(rot_dir[i] == 0 ) continue;

            // 시계방향
            if(rot_dir[i] == 1){
                int tmp = board[i][7] ;
                for(int j = 7; j >= 1; j --)    board[i][j] = board[i][j-1];
                board[i][0] = tmp;
            } 
            // 반시계방향 
            else{
                int tmp = board[i][0];
                for(int j = 0 ; j < 7; j ++ ) board[i][j] = board[i][j+1];
                board[i][7] = tmp;
            }
        }

    // print_board(board);

    }
    // rot_test;
    // rot_test();



    int scores[5] = {0,1,2,4,8};
    for(int i = 1 ; i <= 4; i ++ ){
        ans += scores[i] * board[i][0];
    }

    cout << ans;
}

void rot_test(){

    int test[8] = {};
    int tmp[8],tmp2[8];

    for(int i = 0 ; i < 8; i ++ ) {
        test[i] = board[1][i];
        tmp[i] = board[1][i];
        tmp2[i] = board[1][i];
    }
    cout << "before : " << '\n';
    for(int i = 0 ; i < 8; i ++ ) {
        cout << test[i] << ' ';
    }
    cout << '\n';

    cout << "after cw : " << '\n';
    int tt = tmp[7];
    for(int i = 7 ; i >= 1 ; i --){
        tmp[i] = tmp[i-1];
    }
    tmp[0] = tt;
    for(int i = 0; i < 8; i ++ ) cout << tmp[i] << ' ';
    cout << '\n';


    cout << "after ccw : " << '\n';
    int tt2 = tmp2[0];
    for(int i = 0 ; i < 7; i ++ ) tmp2[i] = tmp2[i+1];
    tmp2[7] = tt2;
    for(int i = 0 ; i < 8; i ++ )  cout << tmp2[i] << ' ';
    cout << '\n';
}

void print_board(int arr[MX][8]){


    for(int i = 1 ; i <= 4 ; i ++){
        for(int j = 0 ; j < 8; j ++){
            cout << board[i][j] << ' ';
        }

        cout << '\n';
    }

    cout << '\n';

}