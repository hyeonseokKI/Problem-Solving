/*
    정확성 시간 제한 / 메모리 제한
        10초/2GB
    문제 설명
        막대와 실, 물체를 이용해 모빌을 만들려 합니다. 
        막대의 양 끝에 실을 이용해 물체나 다른 막대를 연 결할 수 있습니다. 
        막대를 다른 막대의 끝에 매달 때는 매달리는 막대의 중앙에 실을 연결해야 합니다. 
        또, 막대 끝에는 한 번에 하나의 실만 연결해야 합니다.
        모든 막대가 어느 한쪽으로 기울지 않고 바닥과 수평을 이루고 있으면 균형 잡힌 모빌이라고 합니다. 
        다양한 무게의 물체가 주어질 때, 최대한 많은 물체를 매달은 균형 잡힌 모빌 하나를 만들려 합니다.
        단, 실과 막대의 무게는 무시한다고 가정합니다.

        예를 들어 다음과 같은 물체가 있는 경우(숫자는 무게를 나타냅니다)
        2 2 2 2 3 3 5 6
        균형 잡힌 모빌을 만드는 방법은 다음과 같이 3가지 입니다.
            {2 2 2 2}
            {3 3 6}
            {5}

    이때, 가장 많은 물체를 매달은 모빌은 첫 번째 모빌이며, 
    사용한 물체의 무게는 [2, 2, 2, 2]입니다.
    물체들의 무게가 담긴 배열 weights가 매개변수로 주어집니다.
    물체를 최대한 많이 사용해서 균형잡 힌 모빌 하나를 만들었을 때, 
    사용한 물체 개수의 최댓값을 return 하도록 solution 함수를 완성해주세요.

    제한사항
        weights 배열의 길이는 1이상 100,000 이하입니다.
        weights 배열의 원소는 1 이상 100,000 이하인 자연수입니다.

    
    0. 최대 100'000 * 100'000 이므로 long long
    1. map 에는 오름차순으로 정렬된다.
        원소의 사용 개수를 넣는다

    2. 해당 무게의 사용 개수들을 내림차순한다. == 이유는 가장 최댓값을 구하기 위해

    3. 해당 무게의 사용 개수들을 두 개씩 짝지어서, 2 * 해당 무게을 map에 추가한다.

*/
#include<bits/stdc++.h>
using namespace std;


int n;
int weights[100'010];
map<long long, vector<int>> mp;
int ans;

void solve(){
    cin >> n;
    for(int i = 0 ; i < n ; i ++ ) cin >> weights[i];
    for(int i = 0 ; i < n ; i ++ ) mp[weights[i]].push_back(1);
    

    for(auto it = mp.begin(); it != mp.end(); it++){
        long long cur_W = it->first;
        vector<int> counts = it-> second;

        sort(counts.begin(),counts.end(),greater<int>());
        
        ans = max(ans,counts[0]);
        
        // 무게 2의 {2 2 2 2, 1,1 }-> 무게 4 {4, 4, 2}
        for(int i = 0 ; i + 1 < counts.size(); i+=2)
            mp[2*cur_W].push_back(counts[i] + counts[i+1]);
        
    }
    
    cout << ans << "\n";
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);


    solve();

    



    return 0;
}
