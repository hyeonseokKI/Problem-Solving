/*
    
        step 2 : 가장 가까운 바다로 이동
            1. 현재칸에서 가장 가까운 칸으로 이동
                
            2.  행 번호가 가장 작은 칸을 선택,
                행 번호도 같다면 열 번호가 가장 작은 칸을 선택

            3. 그러한 칸이 여러 개라면 좌, 하, 우, 상 순서의 우선순위로 선택    
                3.1     q 입력 순서로 통제

                == 막힌 곳에서 4방향이 나올 수 없음.(막힌 방향) == 3방향 이상 나올 수 없음.(이미 거처온 곳 == 막힌 반대 방향) 
                == 그럼 최소 2개가 남는데 4 x 3 (ex: 좌 상 ) 이라면 무조건 행이나 열이 최대 1개만 같으므로 상관없다.
                == next_sea 큐  dir 순서는 상관없다.
*/

#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

const int INF = 0x3f3f3f3f;
// 0 : 상, 1 : 하 , 2: 좌 3 : 우 
int dx[4] ={-1,1,0,0};
int dy[4] ={0,0,-1,1};

int nxt_d[4][4] = { { 0,2,3,1 } , { 1,3,2,0 } , {2,1,0,3 } , {3,0,1,2 }};

// 2단계 용 방향 배열 좌, 하, 우, 상 
int nxt_d2[4] = {2,1,3,0};

int n,r,c,d;
int board[100][100];
bool vis[100][100];
int cur_X,cur_Y,cur_D;

int debug_board[100][100];
int idx ;

vector<pair<int,int>> path;


bool go(){
    

    for(int dir = 0 ; dir < 4; dir++){
        int nx = cur_X + dx[nxt_d[cur_D][dir]];
        int ny = cur_Y + dy[nxt_d[cur_D][dir]];
        
        if(nx <= 0 || ny <= 0 || nx >n || ny > n ) continue;
        if(board[nx][ny]) continue;
        if(vis[nx][ny]) continue;

        vis[nx][ny] = 1;
        cur_X = nx;
        cur_Y = ny;
        cur_D = nxt_d[cur_D][dir];
        return 1;
    }



    return 0;
}

tuple<int,int,int> next_sea(){
    tuple<int,int,int> nxt = {-1,-1,INF};   // nxt_r,nxt_c, nxt_d;
    
    vector<tuple<int,int,int,int>> cand;      // r,c,d,dist
    queue<tuple <int,int,int,int>> q;        // r,c,d,dist
    int dist[100][100] ;
    for(int i = 1 ; i <=n; i++) fill(dist[i]+1,dist[i]+101,-1);

    q.push({cur_X,cur_Y,cur_D,0});
    dist[cur_X][cur_Y] = 0;

    while(!q.empty()){
        int cx,cy,cd,cdist;
        tie(cx,cy,cd,cdist) = q.front(); q.pop();
        cand.push_back({cx,cy,cd,cdist});
        for(int dir = 0 ; dir < 4 ; dir ++){
            int nx = cx + dx[nxt_d2[dir]];
            int ny = cy + dy[nxt_d2[dir]];
            int nd = nxt_d2[dir];
            if(nx <= 0 || ny <= 0 || nx >n || ny > n ) continue;
            if(board[nx][ny]) continue;
            if(dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[cx][cy] + 1;
            q.push({nx,ny,nd,dist[nx][ny]});
        }

    }
    tuple<int,int,int,int> bdist = {INF,INF,INF,INF};
    
    for(int i = 0 ; i < cand.size(); i ++){
        int cx,cy,cd,cdist;

        tie( cx,cy,cd,cdist) = cand[i];
        if(vis[cx][cy]) continue;
        if(cdist < get<3>(bdist) )  bdist =  cand[i];
        else if(cdist ==get<3>(bdist) &&  cx <  get<0>(bdist) ) bdist = cand[i];
        else if(cdist ==get<3>(bdist) &&  cx ==  get<0>(bdist) && cy < get<1>(bdist)) bdist = cand[i];
    }
    nxt = { get<0>(bdist),get<1>(bdist), get<2>(bdist)};

    return nxt;
}

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    

    cin >> n >> r >> c >> d;
    for(int i = 1 ; i <=n ; i++){
        for(int j = 1 ; j <=n; j++){
            cin >> board[i][j];
        }
    }

    d-=1;
    cur_X = r, cur_Y = c, cur_D = d;


    vis[cur_X][cur_Y] = 1;
    path.push_back({cur_X,cur_Y});
    while(1){

        // step 1 : 항해
        bool ismoved = false;
        ismoved = go();
        if(ismoved) {
            path.push_back({cur_X,cur_Y});
            continue;
        }

        // step 2 : 가까운 바다 찾기 
        tie(cur_X,cur_Y,cur_D) = next_sea();
        if(cur_D == INF) break;
        path.push_back({cur_X,cur_Y});
        vis[cur_X][cur_Y]  = 1;

    }




    for(auto p : path ) cout << p.X << ' ' << p.Y << '\n';

    
}



