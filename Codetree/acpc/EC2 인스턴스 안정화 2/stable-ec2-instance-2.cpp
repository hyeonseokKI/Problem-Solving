/*
    Main Logic
        
    버스트 모드 i 선택시,  |Ai-1 - Ai|  + |Ai- Ai+1| -> |Ai-1 - Ai*2|  + |Ai*2 - Ai+1|

*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 5'000 + 10;
int n;
int arr[MX];
int diff[MX];
int init_ans;

int diff_mx;
int ans;

void solve_On3();
void solve_On2();


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n;
    for(int i = 1; i <=n ; i++) cin >> arr[i];
    
    for(int i = 1; i < n; i ++ ) init_ans += abs(arr[i] - arr[i+1]);
    for(int i = 1 ; i <=n ; i++){
        int normal = 0 ,burst = 0;
        if(i > 1){
            normal += abs(arr[i] - arr[i-1]);
            burst += abs(arr[i]* 2 - arr[i-1]);
        }
        if(i < n){
            normal += abs(arr[i] - arr[i+1]);
            burst += abs(arr[i] * 2- arr[i+1]);
        }
        diff[i] = burst - normal;

    }

    // 인접할 경우 (i + 1 == j)
    for(int i = 1; i <n; i++ ){
        int j = i +1;

        int normal = 0;
        normal = abs(arr[i] - arr[j]);
        if(i > 1) normal += abs(arr[i] - arr[i-1]);
        if(j < n) normal += abs(arr[j] - arr[j+1]);

        int burst = 0;
        burst = abs(arr[i]*2 - arr[j]*2);
        if(i > 1) burst += abs(arr[i]*2 - arr[i-1] *2);
        if(j < n) burst += abs(arr[j]*2 - arr[j+1] *2);

        diff_mx = max(diff_mx, burst - normal);

    }

    // 인접하지 않을 경우 (n 이 3 이상)
    // j == 3 , i = 1 
    // j == 5 , i = 1 , 2 ,3  
    int prev_mx = diff[1];
    for(int j = 3; j <=n; j++){
        
        diff_mx = max(diff_mx, prev_mx + diff[j]);
        prev_mx = max(prev_mx, diff[j-1]);
    }

    cout << init_ans + diff_mx;

    // for(int i = 1 ; i <=n ; i++){
        // int tmp = 
    // }



    // solve_On2();
    // solve_On3();


}



void solve_On2(){

const int MX = 5'000 + 10;
int n;
int arr[MX];

int init_ans = 0;
int ans = 0;;

        cin >> n ;
    for(int i = 1; i <=n ; i++ ) cin  >> arr[i];

    for(int i = 1 ; i < n ; i++ ) init_ans += abs(arr[i] - arr[i+1]);

    for(int i = 1 ; i <=n ; i++){
        for(int j = i+1; j <=n ; j++){
            int tmp = init_ans;

            // 인접할때,
            if(i + 1 == j){
                if(i == 1){
                    tmp -= abs(arr[i] - arr[i+1]);
                    if(n !=2)tmp -= abs(arr[j] - arr[j+1]);

                    tmp += abs(arr[i] * 2 - arr[i+1] * 2);
                    if(n !=2) tmp += abs(arr[j] * 2 - arr[j+1]);
                }
                else if(j == n){
                    tmp -= abs(arr[i] - arr[i-1]);
                    tmp -= abs(arr[i] - arr[j]);
                    
                    tmp += abs(arr[i] *2 - arr[i-1]);
                    tmp += abs(arr[i] *2 - arr[j]* 2);
                }
            } 
            // 인접하지 않을때,
            else{
                if(i == 1){
                    tmp -= abs(arr[i] - arr[i+1]);

                    tmp += abs(arr[i]*2 - arr[i+1]);
                } else{
                    tmp -= abs(arr[i] - arr[i-1]);
                    tmp -= abs(arr[i] - arr[i+1]);

                    tmp += abs(arr[i]*2 - arr[i-1]);
                    tmp += abs(arr[i]*2 - arr[i+1]);
                }
                if(j == n){
                    tmp -= abs(arr[j] - arr[j-1]);
                
                    tmp += abs(arr[j]*2 - arr[j-1]);


                } else{
                    tmp -= abs(arr[j] - arr[j-1]);
                    tmp -= abs(arr[j] - arr[j+1]);

                    tmp += abs(arr[j]*2 - arr[j-1]);
                    tmp += abs(arr[j]*2 - arr[j+1]);

                }

            }


            ans = max(ans, tmp);

        }
    }


    cout << ans ;
}

void solve_On3(){
    
    const int MX = 5'000 + 10;
    int n;
    int arr[MX];

    int ans = 0;

    cin >> n;
    for(int i = 1; i <=n ; i++ ) cin >> arr[i];



    for(int i = 1 ; i <=n ; i ++){
        for(int j = i+1; j <=n ; j++){

                int tmp = 0;
                int arr2[n+1];
                for(int k = 1; k <=n ; k++ ) arr2[k] = arr[k];
                arr2[i] = arr[i] *2;
                arr2[j] = arr[j] *2;

                for(int k = 1 ; k <n ; k++){
                    tmp += abs(arr2[k] - arr2[k+1]);
                }
                
                ans = max(ans, tmp);
        }
    }


    cout << ans;
    



}
