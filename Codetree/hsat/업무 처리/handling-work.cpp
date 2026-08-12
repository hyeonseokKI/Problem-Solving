/*
    Main Logic

        1. R일 동안 업무가 위로 올라간다.
        2. 홀수번째 날짜는 왼쪽 부하 업무가 올라가고, 짝수번째 오른쪽 부하 업부
        3. 업무를 올리는 건 그 다음날 처리 가능하다. 


        wq[노드번호][왼,오] : 왼쪽 1 오른쪽 0 
        
*/

#include<bits/stdc++.h>
using namespace std;

const int ROOT = 0;
const int MX = (1 << 11) + 20;

int h,k,r;
int x;

queue<int> wq[MX][2];
int ans;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);

    
    cin >> h >> k >> r;

    int st_node = (1 << h) -1;
    int en_node = st_node * 2;

    for(int i = st_node; i <= en_node; i ++){
        
        for(int j = 0 ; j < k ; j ++){
            cin >> x;
            wq[i][0].push(x);   // 말단 노드는 0에 저장
        }
    }

    for(int day = 1; day <= r; day++){

        int is_odd = ((day % 2)) ;  // 홀수 = 왼쪽
        // 부서장 처리
        if(!wq[ROOT][is_odd].empty()) {
            ans += wq[ROOT][is_odd].front();
            wq[ROOT][is_odd].pop();
        }

        // 1번 부터 말단 전까지 
        for(int node_num = 1; node_num < st_node; node_num++){
            // cout << node_num << '\n';
            if(wq[node_num][is_odd].empty()) continue;
            wq[(node_num-1)/2][node_num%2].push(wq[node_num][is_odd].front());
            wq[node_num][is_odd].pop();

        }
        // 말단까지 업무 위로 올리기 
        for(int node_num = st_node; node_num <= en_node; node_num++){
            if(wq[node_num][0].empty()) continue;
            wq[(node_num-1)/2][node_num%2].push(wq[node_num][0].front());   // 좌우 구분하여 위로 올리기
            wq[node_num][0].pop();
        }

    }


    cout << ans;

    // cout << st_node << '\n';
    // cout << en_node << '\n';
    // cout << MX << '\n';

    
}