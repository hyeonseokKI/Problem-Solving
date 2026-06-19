/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

int q,x;
int n,s,v,idx,k;

int n_idx;
map<int,int> mp;    // n_idx, s

const int INF = 0x3f3f3f3f;
int d[3'010][3'010];


int solve_4(int tar){

    vector<int> vec;
    for(auto m : mp) vec.push_back(m.second);

    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());

    int n = vec.size();

    for(int i = 0 ; i <=n; i++) fill(d[i],d[i]+tar+1, INF);
    for(int i = 0 ; i <= n; i++) d[i][0] = 0;
    
    for(int i = 1 ; i <= n; i ++){
        int ve = vec[i-1];
        for(int j = 1 ; j <=tar; j ++){
            d[i][j] = d[i-1][j];

            if(j >= ve && d[i][j -ve] != INF){
                d[i][j] = min(d[i][j], d[i][j-ve] + 1);
            }

        }
        
    }


    if(d[n][tar] == INF) return -1;
    return d[n][tar];

    

}


int solve_5(int tar){
    bool isfind = false;
    int cnt = 0;
    vector<int> vec;
    for(auto m : mp) vec.push_back(m.second);
    sort(vec.begin(),vec.end());
    for(int i = 0 ; i < vec.size(); i++ ){
        for(int j = 0 ; j < vec.size(); j++){
            int f = tar - vec[i] - vec[j];
            int tmp_cnt = vec.end() -lower_bound(vec.begin(),vec.end(),f);
            cnt  += tmp_cnt;
            // cout << tmp_cnt << ' ';
            // cout << f << " 보다 큰 수 찾기 : " << *lower_bound(vec.begin(),vec.end(),f) << '\n';
        }
    }


    // if(cnt == 0 )    return -1;
    return cnt;

}

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin>> q;
    while(q--){
        cin >> x;
        // cout << "x : " << x << '\n';

        if(x == 1){
            cin >> n;
            for(int i = 0 ; i < n ; i++)   {
                cin >> s;
                mp[++n_idx] = s;
            }
        } else if (x == 2){
            cin >> v;
            mp[++n_idx] = v;
        } else if(x == 3){
            cin >> idx;
            if(mp.find(idx) == mp.end()) {
                cout << -1 << '\n';
            } else {
                cout << mp[idx] << '\n';
                mp.erase(mp.find(idx));
            }

        } else if(x == 4){
            cin >> k;
            int s4= solve_4(k);
            cout << s4 << '\n';
        } else if(x == 5){
            cin >> k;
            int cnt = solve_5(k);
            cout << cnt << '\n';
        }



    }
    
}




/*
int solve_4(int tar){
    
    int mx = mp.size() * mp.size() - 1;
    vector<int> vec;
    for(auto m : mp) vec.push_back(m.second);
    sort(vec.begin(),vec.end());
    for(int i = 1; i <= mx; i ++){
        
        vector<int> sel;
        for(int j = 0; j < i ; j ++) sel.push_back(0);
        for(int j = 0; j < (int)vec.size()-1 ; j ++) sel.push_back(1);

        
        do{
            int sel_idx = 0;
            int tmp = 0 ;
            // vector<int> test;
            for(int j = 0 ; j < sel.size(); j++){
                if(sel[j] == 0 ){
                    tmp += vec[sel_idx];
                    // test.push_back(vec[sel_idx]);
                } else{
                    sel_idx++;
                }
            }

            if(tmp == tar) {
                // for(auto t : test) cout << t << ' ';
                // cout << '\n';
                return i;
            }

        } while(next_permutation(sel.begin(),sel.end()));
    }


    return -1;

}


*/
    

/*


int solve_4(int tar){

    vector<int> vec;
    for(auto m : mp) vec.push_back(m.second);

    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());

    fill(d,d+tar+1,INF);
    d[0] = 0;
    
    for(auto v : vec){

        for(int i = v ; i <= tar; i ++){
            if(d[i-v] == INF) continue;
            d[i] = min(d[i],d[i-v]+1);
        }
    }

    if(d[tar] == INF) return -1;
    return d[tar];

    

}

*/