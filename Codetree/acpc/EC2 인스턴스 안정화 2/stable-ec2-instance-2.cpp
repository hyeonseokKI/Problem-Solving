/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

int n;
int arr[5'010];
int diff[5'010];

int init_ans;
int diff_mx;
int ans;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;
    for(int i = 1; i <=n ; i++ ) cin >> arr[i];
    for(int i = 1; i < n ; i ++ ) init_ans += abs(arr[i] - arr[i+1]);

    for(int i = 1 ; i <=n; i++){
        int b = 0 , a=0;
        
        if(i > 1){
            b += abs(arr[i-1] - arr[i]);
            a += abs(arr[i-1] - arr[i] * 2);
        }
        if(i < n){
            b += abs(arr[i] - arr[i+1]);
            a += abs(arr[i]*2 - arr[i+1]);
        }
        diff[i] = a- b;
    }

    for(int i = 1 ; i <n ; i++){
        int a = 0, b = 0;
        
        b = abs(arr[i] - arr[i+1]);
        a = abs(arr[i]*2 - arr[i+1]*2);

        if(i > 1){
            b += abs(arr[i-1] - arr[i]);
            a += abs(arr[i-1] - arr[i]*2);
        }
        if(i + 1 < n){
            b += abs(arr[i+1] - arr[i+2]);
            a += abs(arr[i+1]*2 - arr[i+2]);
        }

        diff_mx = max(diff_mx,a - b );
    }

    int prev_mx = diff[1];
    for(int j = 3; j <=n; j++){
        
        diff_mx = max(diff_mx, prev_mx + diff[j]);
        prev_mx = max(prev_mx, diff[j-1]);
    }

    
    cout << init_ans + diff_mx;

    
}