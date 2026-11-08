
#include<bits/stdc++.h>
using namespace std;

const int MX = 50'000 + 2;
int n,q;
int arr[MX];

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> q;
    for(int i = 0 ; i < n ; i ++ ) cin >> arr[i];
    sort(arr,arr+n);

    while(q--){
        int m;
        cin >> m;

        int st = 0;
        int en = n - 1;
        int ans = 0;

        while(st <= en){
            int mid = (st + en) / 2;

            if(arr[mid] == m){
                ans = mid * (n - mid - 1);
                break;
            } else if(arr[mid] < m){
                st = mid + 1;
            } else{
                en = mid - 1;
            }
        }
        cout << ans << '\n';
    }
}
