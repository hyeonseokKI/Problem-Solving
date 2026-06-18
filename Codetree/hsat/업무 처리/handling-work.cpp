/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = (1 << 12);
int h,k,r;
int x;
// int t[MX * MX * MX];
queue<int> q[MX][2];

const int ROOT = 0; // 0 - indexed 선언. 
int cur_t;
int ans;
int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> h >> k >> r;


    int under_cnt = (1 << h);
    int under_idx = (1 << h) - 1;
    // cout <<under_cnt << '\n';

    for(int i = 0 ; i < under_cnt;  i++ ) {
        for(int j = 0; j <k; j ++){
            cin >> x;
            q[under_idx + i][0].push(x);
            // cout << x << ' ';
        }
        // cout  << under_idx + i << ' ';
        // cout << '\n';
    }


    while(cur_t < r){
        cur_t ++;
        // if(cur_t <= r) break;
        // cout << "cur_t : " << cur_t << '\n';
        if(!q[ROOT][cur_t%2].empty()){
            // cout << "처리 : " <<  q[ROOT][cur_t%2].front() << '\n';
            ans += q[ROOT][cur_t%2].front();
            q[ROOT][cur_t%2].pop();
        }


        // ROOT 를 제외한 
        for(int i = 1; i <= h; i++ ){
            int st_node = (1 << i) - 1;
            int st_cnt = (1 << i);
            // cout << st_node << ' ' << st_cnt << '\n';

            vector<int> cur_h_odd_idx, cur_h_even_idx;
            
            for(int j = 0; j < st_cnt; j+=2 ) cur_h_odd_idx.push_back(st_node+j);
            for(int j = 1; j < st_cnt; j+=2 ) cur_h_even_idx.push_back(st_node+j);

            // for(auto c : cur_h_odd_idx) cout << c << ' ';
            // cout << '\n';
            // for(auto c : cur_h_even_idx) cout << c << ' ';
            // cout << '\n';

            for(auto idx : cur_h_odd_idx){
                // 말단일때, 
                if(i == h ){
                    if(q[idx][0].empty()) continue;  
                    int cur = q[idx][0].front(); q[idx][0].pop();
                    int p_idx = (idx - 1) / 2;
                    q[p_idx][1].push(cur);
                    // cout << "c -> p " <<  idx << ' ' << p_idx << ' ' << cur << '\n';
                } else{
                    if(q[idx][cur_t%2].empty()) continue;
                    int cur = q[idx][cur_t%2].front(); q[idx][cur_t%2].pop();
                    int p_idx = (idx - 1) / 2;
                    q[p_idx][1].push(cur);
                    // cout << "c -> p " <<  idx << ' ' << p_idx << ' ' << cur << '\n';
                }
            }
            for(auto idx : cur_h_even_idx){
                // 말단일때, 
                if(i == h ){
                    if(q[idx][0].empty()) continue;  
                    int cur = q[idx][0].front(); q[idx][0].pop();
                    int p_idx = (idx - 1) / 2;
                    q[p_idx][0].push(cur);      // 짝수 
                    // cout << "c -> p " <<  idx << ' ' << p_idx << ' ' << cur << '\n';
                } else{
                    if(q[idx][cur_t%2].empty()) continue;
                    int cur = q[idx][cur_t%2].front(); q[idx][cur_t%2].pop();
                    int p_idx = (idx - 1) / 2;
                    q[p_idx][0].push(cur);
                    // cout << "c -> p " <<  idx << ' ' << p_idx << ' ' << cur << '\n';
                }
            }
            

            
            // for(auto s : sel_idx){
            //     if(q[s].empty()) continue;
            //     int cur = q[s].front(); q[s].pop();
            //     int p_idx = (s - 1) / 2;
            //     q[p_idx].push(cur);

            //     // cout << "c -> p " <<  s << ' ' << p_idx << ' ' << cur << '\n';
            // }

        }
        // cout << '\n';

        

    }


    cout << ans;


}