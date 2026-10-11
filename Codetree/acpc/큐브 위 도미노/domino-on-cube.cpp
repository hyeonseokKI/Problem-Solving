#include<bits/stdc++.h>
using namespace std;

const int CMX = 64;

int n;


long long cnt_bb,cnt_wb;    // n = 99'999 일때 오버플로우 


int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    long long n;
    cin >> n;

    // 각각 독립적인 시나리오에서 구한 최댓값
    long long max_ww = 6LL * n - 6;
    long long max_bb = 6LL * n - 6;
    long long max_wb = 3LL * n * n;

    cout << max_ww << ' ' << max_bb << ' ' << max_wb << '\n';
}