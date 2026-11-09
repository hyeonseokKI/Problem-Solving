/*
    Main Logic

        step 1. s - > x -> t 에서 x 찾기
        step 2. s -> x 일때, x == t 일때는  목적지 정점을 방문시 이동x 조건 
        step 3. x -> t 일때, 역방향 그래프 이용해서 t -> x 찾기. x == s 여도 이동o

        
        
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

void solve(int st, int en, bool solchk[MX]){
    bool chk[MX],chk2[MX];
    fill(chk,chk+n+1,0);
    fill(chk2,chk2+n+1,0);

    //st -> x 
    chk[st] = 1;
    chk[en] = 1;
    q.push(st);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int nxt : adj[cur]){
            if(chk[nxt]) continue;
            chk[nxt] = 1;
            q.push(nxt);
        }
    }

    // x -> en == en -> x       st 거쳐도 됨.
    chk2[en] = 1;
    q.push(en);
    while(!q.empty()){
        int cur = q.front();q.pop();
        for(int nxt : rev_adj[cur]){
            if(chk2[nxt]) continue;
            chk2[nxt] = 1;
            q.push(nxt);
        }
    }

    for(int i = 1; i <=n; i++){
       if(chk[i] && chk2[i]) solchk[i] = 1;
    }

}




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
    
    solve(s,t,gchk);
    solve(t,s,gchk2);

    // s->t, t->s 공통 확인 
    for(int i = 1 ; i <=n; i++){
        if(gchk[i] && gchk2[i]){
            // cout << i << ' ';
             ans++;
        }
    }

    
    cout << ans - 2;
    
}