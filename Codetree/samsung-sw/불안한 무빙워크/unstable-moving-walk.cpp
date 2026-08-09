/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 210;

int n,k;

int r ;
int en;
int rail[MX];   // 각 칸의 안정성 
bool ishuman[MX];
int cur_k;
int cnt;

void print_rail();

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> k ;
    en = n * 2 ;
    for(int i =1  ; i <= en; i ++) {
        cin >> rail[i];
    }
    fill(ishuman,ishuman+en+1,0);


    while(1){


        // step 1 : 한 칸 회전.
        int tmp = rail[en];
        for(int i = en; i >= 2; i --){
            rail[i] = rail[i-1];        // 
        }
        rail[1] = tmp;

        // bool tmph = ishuman[n];
        for(int i = n; i >= 2; i --){
            ishuman[i] = ishuman[i-1];        
        }
        ishuman[1] = ishuman[n] = false;    // n은 내리고, 2n칸에서 오는건, 0이므로  


        // step 2 : 앞사람 부터 한 칸 이동 , 앞선 칸에 안정성 0 or 이미있으면 이면 이동 x
        // 사람은 1 ~ n 에만 존재

        // n에 도착하면 즉시 내림
        ishuman[n] = false;

        for(int i = n-1; i >= 1; i--){
            // 사람이 없는 경우 패스
            if(!ishuman[i]) continue;

            int nxt_idx  = i + 1;


            if(ishuman[nxt_idx]) continue;
            if(!rail[nxt_idx]) continue;
        
            // 이동
            ishuman[nxt_idx] = true;
            rail[nxt_idx]--;
            ishuman[i] = false;
        
            if(nxt_idx == n) ishuman[n] = false; // 즉시내리기
            

        }
        
        // step 3 : 1번 칸 사람이 없고 안정성이 0이 아니라면 사람 올림
        if(!ishuman[1] && rail[1] != 0) {
            rail[1] --;
            ishuman[1] = true;
        }



        
        cnt++;

        // step 4 : 0인 칸 k개 이상이면 종료
        cur_k = 0;
        for(int i = 1 ; i <= en ; i ++)
            if(!rail[i]) cur_k++;
        if(cur_k >= k) break;
        // print_rail();
        // if(cnt >= 4 ) break;
    }



    
    cout << cnt;
    
}

void print_rail(){
    for(int i = 1 ; i <= en ; i ++){
        cout << i << ' ';
    }
        cout << '\n';


    for(int i = 1 ; i <= en ; i ++){
        cout << rail[i] << ' ';
    }
        cout << '\n';

    for(int i = 1 ; i <= en ; i ++){
        cout << ishuman[i] << ' ';
    }
    cout << '\n';
    
    cout << '\n';
}

