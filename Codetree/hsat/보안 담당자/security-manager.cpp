/*
    Main Logic
        

        1 .어떤 시점에서도 들어온 수 >= 나간 수
        2. 마지막까지 확인했을때, 들어온 수 = 나간 수 
*/

#include<bits/stdc++.h>
using namespace std;

int n;
string s;
stack<int> in_st,qu_st;

bool isvalid = true;
string ans = "No";

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;
    cin >> s;

    if(s.size() % 2 != 0 ) isvalid = false;
    for(int i = 0 ; i < n ; i ++){
        if(!isvalid) break;
        if(s[i] == '('){
            in_st.push(i);
        } else if(s[i] == ')'){
            if(!in_st.empty()) in_st.pop();
            else if(!qu_st.empty()) qu_st.pop();
            else isvalid = false;
        } else if(s[i] == '?'){
            qu_st.push(i);
        }

    }
    while(!in_st.empty() && !qu_st.empty()){
            if(in_st.top() > qu_st.top()) {
                isvalid = false;
                break;
            }
            in_st.pop();
            qu_st.pop();
        }

    if(!in_st.empty()) isvalid = false;
    if(isvalid) ans = "Yes";

    cout << ans;
}