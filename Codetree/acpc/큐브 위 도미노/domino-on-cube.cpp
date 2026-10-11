/*
    Main Logic
        모서리 6개 테두리 12개 각각 조사 
        
        타입 0 : 흑으로 시작  , 1  : 백으로 시작 
        n 은 홀수
        x,y,z 왼쪽 아래 꼭지점 기준 

        ww,bb 찾기 
        step 1 :  모서리 
            각 꼭지점은 x,y,z 으로 8개의 모서리에서 세 개의 평면의 첫번째 색의 갯수 (BB) 2개 이상 이면 +1
            
        step 2 : 테두리
            12개의 테두리 에서 2개의 평면 만나는 테두리 선택해서, 같은 타입인지 확인
                같은 타입이면서, 흑으로 시작하면, b w b w b  이므로, w b w 중 1개이다. == (n-3) / 2
                같은 타입이면서, 백으로 시작하면, w b w b w  이므로, b w b 중 2개이다. == (n-1) / 2

        
        

        wb 는 격자식으로 모두를 펼치면 모든 쌍을 만들 수 있다. 
        따라서 전체 격자 수는 n * n * 6(면)
        2개가 한 쌍이므로 /2
        = n * n * 3
*/

#include<bits/stdc++.h>
using namespace std;

const int CMX = 64;

int n;


long long cnt_bb,cnt_wb;    // n = 99'999 일때 오버플로우 


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;


    for(int i = 0 ; i < CMX; i++){

        // 0 : 흑 , 1 : 백 
        int states[6] = {} ;
        int brute = i;
        for(int j = 0; j < 6; j ++){
            states[j] = brute % 2 ;
            brute/=2;
        }

        // 모서리 
        int ens[2] = {0, n-1};
        long long cnt_tmp_bb = 0;
        for(int x : ens){
            for(int y : ens){
                for(int z : ens){
                    int s_x = (x == 0 ? 0 : 1); // 앞 뒤
                    int s_y = (y == 0 ? 2 : 3); // 왼 오
                    int s_z = (z == 0 ? 4 : 5); // 아 위

                    int c_x = (states[s_x] + y + z) % 2;
                    int c_y = (states[s_y] + x + z) % 2;
                    int c_z = (states[s_z] + x + y) % 2;
                    int cnt_tmp = c_x + c_y + c_z;
                    if(cnt_tmp <= 1) cnt_tmp_bb++;
                }
            }
        }
        // for(int s : states) cout << s ;
        // cout <<'\n';

        // 테두리 
        for(int x : ens){
            for(int y : ens){
                int s_x = (x == 0 ? 0 : 1); // 앞 뒤
                int s_y = (y == 0 ? 2 : 3); // 왼 오

                int p_x = (states[s_x] + y) % 2;
                int p_y = (states[s_y] + x) % 2;
                if(p_x == p_y) {
                    // if(p_x == 0 && )        
                    // w b w || w b w b w || w b w b w b w 
                    // b w b || b w b w b || b w b w b w b 
                    if(p_x == 0){    // b로 시작한다면 
                        cnt_tmp_bb += (n-3) / 2;
                    } else{
                        cnt_tmp_bb += (n-2 + 1) / 2;
                        
                    }
                    // cnt_tmp_bb += (n-2) / 2;
                    // cout << n-2 << ' ';
                }
            }
        }

        for(int y : ens){
            for(int z : ens){
                int s_y = (y == 0 ? 2 : 3); // 왼 오
                int s_z = (z == 0 ? 4 : 5); // 아 위

                int p_y = (states[s_y] + z) % 2;
                int p_z = (states[s_z] + y) % 2;
                if(p_y == p_z) {
                    if(p_y == 0){    // b로 시작한다면 
                        cnt_tmp_bb += (n-3) / 2;
                    } else{
                        cnt_tmp_bb += (n-2 + 1) / 2;
                        
                    }
                }
            }
        }

        for(int x : ens){
            for(int z : ens){
                int s_x = (x == 0 ? 0 : 1); // 앞 뒤
                int s_z = (z == 0 ? 4 : 5); // 아 위


                int p_x = (states[s_x] + z) % 2;
                int p_z = (states[s_z] + x) % 2;
                if(p_x == p_z) {
                    if(p_x == 0){    // b로 시작한다면 
                        cnt_tmp_bb += (n-3) / 2;
                    } else{
                        cnt_tmp_bb += (n-2 + 1) / 2;
                        
                    }
                }
            }
        }


        // cout << '\n';


        cnt_bb = max(cnt_bb, cnt_tmp_bb);
    }


    cnt_wb = 1LL * 3 * n * n;
    cout << cnt_bb << ' ' <<cnt_bb << ' ' << cnt_wb ;
}