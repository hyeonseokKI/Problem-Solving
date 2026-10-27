/*
    Main Logic
        

        1 .어떤 시점에서도 들어온 수 >= 나간 수
        2. 마지막까지 확인했을때, 들어온 수 = 나간 수 
*/

#include<bits/stdc++.h>
using namespace std;

int n;
string s;
stack<char> st;

bool isvalid = true;
string ans = "No";
int in_mx, in_mn;

int main(void){
    cin.tie(0);
    ios::sync_with_stdio(0);
    
    cin >> n;
    cin >> s;

    // test
    // cout << n << ' ' << s << '\n';

    if(s.size() % 2 == 1) isvalid = false;

    for(int i = 0 ; i < s.size(); i ++){
        if(!isvalid)  break;
        
        if(s[i] == '(') {
            in_mx ++;
            in_mn ++;
        } else if(s[i] == ')'){
            in_mx --;
            in_mn --;
            if(in_mn < 0) in_mn+=2;
        } else if(s[i] == '?'){
            in_mx ++;
            if(in_mn > 0)in_mn --;
            else in_mn++;
        }

        // if(in)
        // cout << in_mx << ' ' << in_mn << '\n';

        if(in_mx < 0 ) isvalid =false;

    }

    // in_mn >= 0 
    if(in_mn != 0 ) isvalid = false;


    if(isvalid) ans = "Yes";

    cout << ans;
}