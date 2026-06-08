/*


*/

#include<bits/stdc++.h>
using namespace std;

int mx =  -0x7f7f7f7f;
int mn = 0x7f7f7f7f;

int n;
int arr[11];
int add_cnt,sub_cnt,mul_cnt;

void solve(int k, int tot){
    if(k == n){
        mx = max(mx,tot);
        mn = min(mn,tot);
        return;
    }

    if(add_cnt > 0){
        add_cnt --;
        solve(k+1,tot+arr[k]);
        add_cnt++;
    } 
    if(sub_cnt > 0){
        sub_cnt --;
        solve(k+1,tot-arr[k]);
        sub_cnt++;
    }     
    if(mul_cnt > 0){
        mul_cnt --;
        solve(k+1,tot*arr[k]);
        mul_cnt++;
    } 
    
}


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);


    cin >> n ;
    for(int i = 0 ; i < n ; i ++ ) cin >> arr[i];
    cin >> add_cnt >> sub_cnt >> mul_cnt;

    solve(1,arr[0]);

    cout << mn << ' ' << mx;
}
