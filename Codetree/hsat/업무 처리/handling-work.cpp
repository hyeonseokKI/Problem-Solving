/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = (1 << 12);
int h,k,r,x;
queue<int> q[MX][2];

const int ROOT = 0; // 0 - indexed 선언. 
int ans;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> h >> k >> r;

    int leaf_st = (1 << h) - 1;
    int leaf_en = (1 << (h+1)) - 1  ;       // [st,en)
    // cout << leaf_st << ' ' << leaf_en << '\n';

    for(int i = leaf_st ; i < leaf_en; i ++) {    
        for(int j = 0; j < k; j ++){
            cin >> x;
            q[i][0].push(x);
        }
        // cout << i << ' ';
    }

    for(int t = 1; t <= r; t++){
        
        int dir = t % 2;    // 홀수 1 , 짝수 0

        // Top- down
        if(!q[ROOT][dir].empty()){
            ans += q[ROOT][dir].front(); 
            q[ROOT][dir].pop();
        }

        for(int i = 1; i < leaf_en; i++){
            int p_idx = (i-1) / 2;
            int p_dir = i % 2;   // 짝수 0, 홀수 1
            
            if(i >= leaf_st){
                if(q[i][0].empty()) continue;
                
                q[p_idx][p_dir].push(q[i][0].front());
                q[i][0].pop();
            } else {
                if(q[i][dir].empty()) continue;

                q[p_idx][p_dir].push(q[i][dir].front());
                q[i][dir].pop();
            }
        }




    }
    



    cout << ans;


}