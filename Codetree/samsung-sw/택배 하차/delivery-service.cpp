/*
    Main Logic

        1-index

        step 1 :상차 
            중력받아 아래로 이동. 이미 있는경우 위에 쌓기
            어떠한 택배들도 공간을 벗어나지 않음이 보장

        step2 : 하차 
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 50 + 2;
const int K_MX = 100 + 2;

int n,m;
tuple<int,int,int,int> ks[K_MX];
int board[MX][MX];
int k,w,h,c;
int r;
vector<int> ans;

void print_board(int arr[MX][MX]);


void down(){
    bool is_moved = true;
    while(is_moved){
        is_moved = false;

        for(int i = 1 ; i <K_MX; i ++){
            int h,w,c,r;
            tie(h,w,c,r) = ks[i];

            // if(h == 0) continue;
            if(board[r][c] != i) continue;
        
            if(r + h - 1 >= n) continue;
            
            bool is_valid = true;
            for(int j = c; j < c+w; j++){
                if(board[r+h][j] == 0 ) continue;
                is_valid = false;
                break;
            }

            if(is_valid){
                for(int j = c; j < c+w; j ++){
                    board[r+h][j] = i;
                    board[r][j] = 0;
                }

                ks[i] = {h,w,c,r+1};
                is_moved = true;
            }


        }


    }

    
}


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> m;

    // 택배 상차 
    for(int i = 0 ; i < m; i ++){
        cin >> k >> h >> w >> c;    // 번호,세로,가로,좌측 좌표
        // cout << k << ' ' << h << ' ' << w << ' ' << c << '\n';

        int min_h = MX;
        bool is_find = false;
        for(int cidx = c ; cidx < c + w; cidx++){
            int tmp_h = 0;
            for(int ridx = 1 ; ridx <= n; ridx++ ){
                if(board[ridx][cidx] != 0) break;
                tmp_h = ridx;
            }
            min_h = min(min_h,tmp_h);
        }
        // cout << min_h << '\n';

        // 하단으로 내리기
        for(int cidx = c; cidx < c + w ; cidx++){
            for(int ridx = min_h ; ridx > min_h-h; ridx--){ // 6,5
                board[ridx][cidx] = k;
            }
        }
        r = min_h - h + 1;
        ks[k] = {h,w,c,r};

    }

    // cout << get<3>(ks[1]) << '\n';

    // print_board(board);

    // 택배 하차.
    for(int cnt = 0 ; cnt < m ; cnt++){

        int h_size[K_MX] = {};
        set<int> se;
        for(int i = 1; i <= n ; i++){

            if(cnt % 2 == 0){
                for(int j = 1 ; j <= n; j ++){
                    if(board[i][j] == 0)  continue;
                    // cand[i] = board[i][j];
                    h_size[board[i][j]]++;  // 후보 길이 삽입
                    se.insert(board[i][j]); // 후보 번호 삽입
                    break;
                }
            } else{
        
                for(int j = n ; j >= 1; j --){
                    if(board[i][j] == 0)  continue;
                    // cand[i] = board[i][j];
                    h_size[board[i][j]]++;  // 후보 길이 삽입
                    se.insert(board[i][j]); // 후보 번호 삽입
                    break;
                }
            }

        }

        // cout << se.size() << '\n';
        int cur_exit = 0;
        int ch,cw,cc,cr;
        for(auto s : se ) {
            tie(ch,cw,cc,cr) = ks[s];
            if(h_size[s] == ch) {
                cur_exit = s;
                break;
            }
        }

        // 제거
        ans.push_back(cur_exit);
        for(int i = cr; i < cr+ch; i++ ){
            for(int j = cc; j < cc+cw; j++ ){
                // cout << i << ' ' << j << '\n';
                board[i][j] = 0 ;
            }
        }


        // 내리기 
        down();
        // break;
    // print_board(board);


    }
    // for(auto ca : cand) cout << ca << '\n';







    for(auto& a : ans ) cout << a << '\n';
    
}


void print_board(int arr[MX][MX]){
    for(int i = 1 ; i <= n ; i ++){
        for(int j = 1 ; j <= n ; j ++){

            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}