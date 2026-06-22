/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

int n;
int arr[5'010];

int init_ans;
int ans;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;
    for(int i = 1; i <=n ; i++ ) cin >> arr[i];
    for(int i = 1; i < n ; i ++ ) init_ans += abs(arr[i] - arr[i+1]);

    for(int i = 1 ; i <= n ; i++){
        for(int j = i +1 ; j <=n; j ++){
            int tmp_ans = init_ans;
            if(i+1 == j){
                if(i == 1){
                    tmp_ans -= abs(arr[i] - arr[i+1]);
                    tmp_ans -= abs(arr[j] - arr[j+1]);
                    
                    tmp_ans += abs(arr[i]* 2 - arr[i+1] *2);
                    tmp_ans += abs(arr[j]* 2 - arr[j+1]);
                } else if(j == n) {
                    tmp_ans -= abs(arr[i-1] - arr[i]);
                    tmp_ans -= abs(arr[i] - arr[j]);

                    tmp_ans += abs(arr[i-1] - arr[i] * 2);
                    tmp_ans += abs(arr[i]* 2 - arr[j] *2);

                } else{

                    tmp_ans -= abs(arr[i-1] - arr[i]);
                    tmp_ans -= abs(arr[i] - arr[i+1]);
                    tmp_ans -= abs(arr[j] - arr[j+1]);

                    tmp_ans += abs(arr[i-1] - arr[i] * 2) ;
                    tmp_ans += abs(arr[i]*2 - arr[i+1]*2);
                    tmp_ans += abs(arr[j]*2 - arr[j+1]);
                }
                
            } else{
                if(i == 1){
                    tmp_ans -= abs(arr[i] - arr[i+1]);
                    // tmp_ans -= abs(arr[j-1] - arr[j]);
                    // tmp_ans -= abs(arr[j] - arr[j+1]);

                    tmp_ans += abs(arr[i]* 2 - arr[i+1]);
                    // tmp_ans += abs(arr[j-1] - arr[j] * 2);
                    // tmp_ans += abs(arr[j] * 2 - arr[j+1]);
                }  else{
                    tmp_ans -= abs(arr[i-1] - arr[i]);
                    tmp_ans -= abs(arr[i] - arr[i+1]);
            
                    tmp_ans += abs(arr[i-1] - arr[i] * 2);
                    tmp_ans += abs(arr[i] * 2 - arr[i+1]);
                }
                if(j == n){
                    // tmp_ans -= abs(arr[i-1] - arr[i]);
                    // tmp_ans -= abs(arr[i] - arr[i+1]);
                    tmp_ans -= abs(arr[j-1] - arr[j]);

                    // tmp_ans += abs(arr[i-1] - arr[i] * 2);
                    // tmp_ans += abs(arr[i] * 2 - arr[i+1]);
                    tmp_ans += abs(arr[j-1] - arr[j] *2);

                } 
                else{
                    tmp_ans -= abs(arr[j-1] - arr[j]);
                    tmp_ans -= abs(arr[j] - arr[j+1]);

                    tmp_ans += abs(arr[j-1] - arr[j] * 2);
                    tmp_ans += abs(arr[j]*2 - arr[j+1]);

                }
                    

            }

            ans = max(tmp_ans,ans);
        }
    }
    if(n == 2) ans = 2*init_ans;
    cout << ans; 
    
}