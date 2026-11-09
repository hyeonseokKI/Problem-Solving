/*
    Main Logic
        
*/

#include<bits/stdc++.h>
using namespace std;

const int MX = 100'000 + 2; 

int n,m,x,y;
int s,t;
vector<int> adj[MX],rev_adj[MX];
queue<int> q;

bool chk[MX],chk2[MX];
bool gchk[MX],gchk2[MX];
int ans;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n >> m;

    while(m--){
        cin >> x >> y;
        adj[x].push_back(y);
        rev_adj[y].push_back(x);
    }
    cin >> s >> t;
    

    // s - > x;
    chk[s] = 1;
    chk[t] = 1;     //미리 방문 표시하여 방문 못하게 
    q.push(s);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int nxt : adj[cur]){
            if(chk[nxt]) continue;
            chk[nxt] = 1;
            q.push(nxt);
        }
    }

    // x -> t == t -> x';
    chk2[t] = 1;
    // chk2[s] = 1;
    q.push(t);
    while(!q.empty()){
        int cur = q.front();q.pop();
        for(int nxt : rev_adj[cur]){
            if(chk2[nxt]) continue;
            chk2[nxt] = 1;
            q.push(nxt);
        }
    }


    // s  -> x -> t 확인
    for(int i = 1; i <=n; i++){
       if(chk[i] && chk2[i]) gchk[i] = 1;
    }

    fill(chk,chk+n+1,0);
    fill(chk2,chk2+n+1,0);

    // t - > x 
    chk[t] = 1;
    chk[s] = 1;
    q.push(t);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int nxt : adj[cur]){
            if(chk[nxt]) continue;
            chk[nxt] = 1;
            q.push(nxt);
        }
    }

     // x -> s == s <- x 
    chk2[s] = 1;
    // chk2[t] = 1;
    q.push(s);
    while(!q.empty()){
        int cur = q.front();q.pop();
        for(int nxt : rev_adj[cur]){
            if(chk2[nxt]) continue;
            chk2[nxt] = 1;
            q.push(nxt);
        }
    }


     // t  -> x -> s 확인
    for(int i = 1; i <=n; i++){
       if(chk[i] && chk2[i]) gchk2[i] = 1;
    }


    // s->t, t->s 공통 확인 
    for(int i = 1 ; i <=n; i++){
        if(gchk[i] && gchk2[i]){
            // cout << i << ' ';
             ans++;
        }
    }

    
    cout << ans - 2;
    
}