/*
    Main Logic
        
    버스트 모드 i 선택시,  |Ai-1 - Ai|  + |Ai- Ai+1| -> |Ai-1 - Ai*2|  + |Ai*2 - Ai+1|

*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 5'000 + 10;
int n;
int arr[MX];

int init_ans;
int ans;

void solve_n3();

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

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
    // solve_On3();


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
