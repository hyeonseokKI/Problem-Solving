/*


*/

#include<bits/stdc++.h>
using namespace std;

int mx =  -0x7f7f7f7f;
int mn = 0x7f7f7f7f;

int n;
int arr[11];
int add_cnt,sub_cnt,mul_cnt;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);


    cin >> n ;
    for(int i = 0 ; i < n ; i ++ ) cin >> arr[i];
    cin >> add_cnt >> sub_cnt >> mul_cnt;


    // for(int i = 0 ; i < n ; i ++ ) cout << arr[i] << ' ';
    // cout << '\n';
    // cout << add_cnt << sub_cnt << muL_cnt << '\n';

    vector<int> sel;
    for(int i = 0 ; i < add_cnt; i++) sel.push_back(1);
    for(int i = 0 ; i < sub_cnt; i++) sel.push_back(2);
    for(int i = 0 ; i < mul_cnt; i++) sel.push_back(3);

    int sz = (int)sel.size();

    do{
        int tmp = arr[0] ;
        for(int i = 0 ; i < sz;i ++){
            if(sel[i] == 1)  {
                tmp += arr[i+1];
            } else if(sel[i] == 2){
                tmp -=  arr[i+1];
            } else if(sel[i] == 3){
                tmp *=  arr[i+1];
                
            }

            // cout << sel[i];
        }
        // cout << '\n';

        mn = min(tmp,mn);
        mx = max(tmp,mx);
        // cout << mn << ' ' << mx << '\n';

    } while(next_permutation(sel.begin(),sel.end()));
    // for(auto s : sel ) cout << s << ' ';

    
    
    cout << mn << ' ' << mx;
}
