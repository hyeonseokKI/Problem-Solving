/*
    Main Logic
        1. 수와 갯수를 정렬 
        2. 뒤애서 부터 수를 읽고 갯수 만큼 더하면 동점 처리 가능 
*/

#include<bits/stdc++.h>
using namespace std;

int n;
int a[100'001],b[100'001],c[100'001],tot[100'001];
int tmp_a[100'001],tmp_b[100'001],tmp_c[100'001],tmp_tot[100'001];

map<int,int> ra;    // 점수, 랭크 저장 
int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

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

    map<int,int> mp_a,mp_b,mp_c,mp_tot;
    for(int i = 0 ; i < n ; i ++ ) mp_a[tmp_a[i]]++;
    for(int i = 0 ; i < n ; i ++ ) mp_b[tmp_b[i]]++;
    for(int i = 0 ; i < n ; i ++ ) mp_c[tmp_c[i]]++;
    for(int i = 0 ; i < n ; i ++ ) mp_tot[tmp_tot[i]]++;

    map<int,int> ra,rb,rc,rtot;
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