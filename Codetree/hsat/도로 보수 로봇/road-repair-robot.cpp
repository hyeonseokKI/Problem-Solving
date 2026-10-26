/*
    Main Logic
        
        최적화 문제 -> 결정 문제로 변환 (바킹독 이분탐색)
            최대 K를 활용하여 최소 길이 구하기
            -> 길이가 x 일때, k 를 이상인지 아닌지.
        step 1. 길이 최소값과 최댓값 설정.

        step 2 . 
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 100'000 + 2;
const int K_MX = 1'000'000'000;
int n,k;
int arr[MX];
int ans;
int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    


    cin >> n >> k;
    for(int i = 0 ; i < n ; i ++ ) cin >> arr[i];

    
    int st = 1;
    int en = arr[n-1] - arr[0] + 1;

    while(st <= en){
        int cnt = 0 ;
        int mid = (st + en) / 2;    // 보수 패치의 길이 ex) 1,4 일떄, 길이 2임.
        
        int val = arr[0] + mid - 1 ;    // 첫 단추 
        cnt++;

        for(int i = 1; i < n; i ++){
            if(arr[i] <= val) continue;
            else{
                cnt++;
                val = arr[i] + mid - 1;
            }
        }

        // cnt 가 k개를 넘는 순간 종료
        if(cnt <= k){
            ans = mid;  // 최솟값으로 갱신됨.
            en = mid - 1;
        } else{
            st = mid + 1;
        }
    }
    cout << ans;
}