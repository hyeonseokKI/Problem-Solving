/*
    Main Logic
        
*/
// 1642


#include<bits/stdc++.h>
using namespace std;

#define X first
#define Y second 

const int MX = 50 + 2;
const int MX_VALUE = 0x3f3f3f3f;
int n,m;

int board[MX][MX];
vector<pair<int,int>> persons;
vector<pair<int,int>> hos;

int ans = MX_VALUE;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n >> m;
    for(int i = 0 ; i < n ; i ++ ){
        for(int j = 0 ; j < n ; j ++){
            cin >> board[i][j];

            if(board[i][j] == 1) persons.push_back({i,j});
            else if(board[i][j] == 2) hos.push_back({i,j});
        }
    }

    vector<int> sel(hos.size(),1);
    for(int i = 0 ; i < m ; i ++) sel[i] = 0;

    do{
        // for(auto v : sel) cout << v << ' ';
        // cout << '\n';
        
        int tmp_ans = 0 ;
        for(auto person : persons){
            int tmp_val = MX_VALUE;
            for(int i = 0 ; i < sel.size(); i ++){
                if(sel[i]) continue;
                int x,y;
                tie(x,y) = hos[i];
                int tmp_dist = abs(x - person.X) + abs(y - person.Y);
                tmp_val = min(tmp_val, tmp_dist);
            }
            tmp_ans += tmp_val;
        }
        ans = min(ans, tmp_ans);

    } while(next_permutation(sel.begin(),sel.end()));



    cout << ans ;

    
}