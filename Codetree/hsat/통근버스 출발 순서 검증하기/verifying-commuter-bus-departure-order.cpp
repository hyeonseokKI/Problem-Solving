/*
    Main Logic

        0. 5000 C 3 구해서 stack 에 넣어보는 것은 == 104'041'712'495'000 번이므로 
            어림없는 볼
        0.1 1초 n = 5000 이므로, n2lgn 이하 으로 해결해야됨.


        1. i < j < k 일때 ai < aj이고 ai > ak 이므로 == ak < ai < aj 인걸 찾아야됨.
        2. n^2 풀이 

            k 후보 찾기
                뒤에서부터 순회하여 ak < ai 일때, cnt++
                ak > ai 일때, j 후보이므로 ans += cnt

        
*/

#include<bits/stdc++.h>
using namespace std;

int n;
int arr[5'100];
int ans ;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);

    

    cin >> n ;
    for(int i = 1; i <= n ; i++) cin >> arr[i];



    for(int i = 1 ; i <=n; i++){
        int cnt = 0;

        for(int k = n; k >= i+1; k--){
            if(arr[i] > arr[k]) cnt++;
            else {
                ans +=cnt;
            }
            // cout << i << ' ' << j << '\n';
        }

    }




    cout << ans;
}




