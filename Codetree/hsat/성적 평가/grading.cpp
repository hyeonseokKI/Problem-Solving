/*
    Main Logic
        solve 함수
            1. 점수를 정렬 -> 큰 수 부터 읽으려고 
            2. 갯수 저장 -> 동점자 반영하려고
            3. 점수에 대한 랭크 저장 -> 등수 확인하려고 

        solve_2() 
            1. 점수에 대한 갯수, 점수에 대한 랭크 배열 생성 -> O(1) 에 접근하려고 인덱스를 활용한거임 대신에 수의 범위가 작았을때만 사용 가능 
                1.1 그게 아니라면 solve 처럼 점수에 대한 갯수는 map, arr 복사하여 sort 한 것 을 점수 큰 순서대로 점수에 대한 rank 이용 
            2. 점수에 대한 갯수를 큰 수부터  읽으면서,  랭크 지정, 동점자를 고려하여 next_rank + 현재 동점자로 갱신 
*/

#include<bits/stdc++.h>
using namespace std;

const int M = 3;
const int N = 100'001;
int n;
int scores[M + 1][N];

void solve(){

    int n;
    
    // 전역 변수로 이동해야 됨. 스택 오버플로우 
    int a[100'001],b[100'001],c[100'001],tot[100'001];
    int tmp_a[100'001],tmp_b[100'001],tmp_c[100'001],tmp_tot[100'001];

    cin >> n;

    for(int i = 0 ; i < n ; i ++) cin >> a[i] ;
    for(int i = 0 ; i < n ; i ++) cin >> b[i] ;
    for(int i = 0 ; i < n ; i ++) cin >> c[i] ;
    for(int i = 0 ; i < n ; i ++ ) tot[i] += a[i] +b[i]+c[i];

    for(int i = 0 ; i < n ; i ++) tmp_a[i] = a[i] ;
    for(int i = 0 ; i < n ; i ++) tmp_b[i] = b[i] ;
    for(int i = 0 ; i < n ; i ++) tmp_c[i] = c[i] ;
    for(int i = 0 ; i < n ; i ++ ) tmp_tot[i] = tot[i];

    sort(tmp_a,tmp_a+n);
    sort(tmp_b,tmp_b+n);
    sort(tmp_c,tmp_c+n);
    sort(tmp_tot,tmp_tot+n);

    map<int,int> mp_a,mp_b,mp_c,mp_tot; // 점수, 갯수 저장 
    for(int i = 0 ; i < n ; i ++ ) mp_a[tmp_a[i]]++;
    for(int i = 0 ; i < n ; i ++ ) mp_b[tmp_b[i]]++;
    for(int i = 0 ; i < n ; i ++ ) mp_c[tmp_c[i]]++;
    for(int i = 0 ; i < n ; i ++ ) mp_tot[tmp_tot[i]]++;

    map<int,int> ra,rb,rc,rtot; // 점수 랭크 저장
    int idxa = 1,idxb = 1, idxc = 1 ,idxtot = 1;
    int mxa = -1, mxb = -1 , mxc = -1, mxtot = -1;
    for(int i = n -1 ; i >= 0; i--){
        if(mxa != tmp_a[i]) {
            ra[tmp_a[i]] = idxa;
            idxa += mp_a[tmp_a[i]];
            mxa = tmp_a[i];
        }
        if(mxb != tmp_b[i]) {
            rb[tmp_b[i]] = idxb;
            idxb += mp_b[tmp_b[i]];
            mxb = tmp_b[i];
        }        
        if(mxc != tmp_c[i]) {
            rc[tmp_c[i]] = idxc;
            idxc += mp_c[tmp_c[i]];
            mxc = tmp_c[i];
        }
        if(mxtot != tmp_tot[i]) {
            rtot[tmp_tot[i]] = idxtot;
            idxtot += mp_tot[tmp_tot[i]];
            mxtot = tmp_tot[i];
        }
    }

    for(int i = 0 ; i < n ; i ++ )   cout << ra[a[i]] << ' ';
    cout << '\n';
    for(int i = 0 ; i < n ; i ++ )   cout << rb[b[i]] << ' ';
    cout << '\n';
    for(int i = 0 ; i < n ; i ++ )   cout << rc[c[i]] << ' ';
    cout << '\n';
    for(int i = 0 ; i < n ; i ++ )   cout << rtot[tot[i]] << ' ';
    cout << '\n';
    // for(auto r : ra) cout << r.first << ' ' << r.second << '\n';

}


void solve_2(){
      cin >> n;

    for(int i = 0 ; i < M ; i ++ ){
        for(int j = 0 ; j < n; j ++){
            cin >> scores[i][j];
            scores[3][j] += scores[i][j];
        }
    }


    // for(int i = 0 ; i <= M ; i ++ ){
    //     for(int j = 0 ; j < n; j ++){
    //         cout << scores[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    // 1,2,3,tot rank 구하는 방법 1 
    for(int i = 0 ; i <= M; i ++){
        int counts[3'010] = {};
        int ranks[3'010] = {};

        // 점수의 갯수 배열 
        for(int j = 0; j < n ; j ++ ) counts[scores[i][j]]++;

        // 점수의 랭크 저장 
        int cur_rank = 1;
        for(int j = 3'000; j >= 0; j-- ) {
            if(counts[j]){
                ranks[j] = cur_rank;
                cur_rank += counts[j];
            }
        }
        

        for(int j = 0 ; j < n ; j ++ ) cout << ranks[scores[i][j]] << ' ';
        cout << '\n';


    }
}

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    


    // solve();
    


    solve_2();

  

}