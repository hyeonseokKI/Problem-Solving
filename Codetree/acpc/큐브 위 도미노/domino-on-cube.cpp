/*
    Main Logic
        
        step 1 : 모든 경우의 수는 2 ^ 6  = 64;
            
        step 2 : 꼭지점 과 선 (꼭지점 제외한 가운데만)  계산
            n이 짝수,홀수에 따라 꼭지점 색상 달라짐. 

            꼭지점 8 개 조사
            선 12개 조사

        
        

*/

#include<bits/stdc++.h>
using namespace std;

const int TOT = 64;

int n;
int n_side;
long long mx_bb,mx_wb;


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n;

    // 테두리 선 가운데 길이
    n_side = n - 2;
    // cout << n_side << '\n';

    // 0 : 위 , 1 : 아래, 
    // 2 : 앞,  3 : 뒤 
    // 4, 왼쪽, 5: 오른쪽
    for(int i = 0 ; i < TOT; i ++){

        // 0 : 최좌측 흑, 
        // 1 : 최좌측 백
        int states[6] = {};
        int brute = i;
        for(int idx = 0 ; idx < 6 ; idx++){
            states[idx] = brute% 2;  
            brute/= 2;
        }

        // 꼭지점 
        long long cur_bb = 0;

        int ends[2] = {0,n-1};
        for(int x : ends){
            for(int y : ends){
                for(int z : ends){
                    int f_x,f_y,f_z;
                    int c_x,c_y,c_z;
                    f_x = (x == 0) ? 0 : 1; // 위 아래
                    f_y = (y == 0) ? 2 : 3; // 앞 뒤 
                    f_z = (z == 0) ? 4 : 5; // 왼 오른

                    c_x = (states[f_x] + y + z) % 2;
                    c_y = (states[f_y] + x + z) % 2;
                    c_z = (states[f_z] + x + y) % 2;
                    
                    int cnt = c_x + c_y + c_z;
                    if(cnt >= 2) cur_bb++;
                }
            }
        }

        // 테두리 

        for(int x : ends){
            for(int y : ends){
                int f_x = (x == 0) ? 0 : 1;
                int f_y = (y == 0) ? 2 : 3;
                
                int p_x = (states[f_x] + y) % 2;
                int p_y = (states[f_y] + x) % 2;
                
                if(p_x == p_y){
                    cur_bb += ((n-2)/2);
                    if(n% 2 !=0 && p_x == 0){
                        cur_bb++;
                    }
                    // if(n % 2 == 0)  cur_bb += ((n-2)/2);
                    // else{
                    //     cur_bb += ((n-2)/2);
                    //     if(p_x == 0){ // 흑이면
                    //         cur_bb ++;
                    //     }    
                    // }
                }

            }
        }

        for(int x : ends){
            for(int z : ends){
                int f_x = (x == 0) ? 0 : 1;
                int f_z = (z == 0) ? 4 : 5;
                
                int p_x = (states[f_x] + z) % 2;
                int p_z = (states[f_z] + x) % 2;

                if(p_x == p_z){
                    cur_bb += ((n-2)/2);
                    if(n% 2 !=0 && p_x == 0){
                        cur_bb++;
                    }
                }
            }
        }
        for(int y : ends){
            for(int z : ends){
                int f_y = (y == 0) ? 2 : 3;
                int f_z = (z == 0) ? 4 : 5;

                int p_y = (states[f_y] + z) % 2;
                int p_z = (states[f_z] + y) % 2;

                if(p_y == p_z){
                    cur_bb += ((n-2)/2);
                    if(n% 2 !=0 && p_y == 0){
                        cur_bb++;
                    }
                }
            }
        }
        

        mx_bb = max(mx_bb, cur_bb);
    }



    // wb 는 6 * n^2  / 2  전체가 체스판 처럼 되면 가능 
    mx_wb = 1LL * n * n * 6 / 2 ;

    cout << mx_bb << ' ' << mx_bb << ' ' << mx_wb << '\n';

    


}