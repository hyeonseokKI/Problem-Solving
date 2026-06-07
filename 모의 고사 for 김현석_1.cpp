/*
문제 설명
    다음 규칙을 지키는 문자열을 올바른 괄호 문자열이라고 정의합니다.
        (), [], {} 는 모두 올바른 괄호 문자열입니다.
    만약 A가 올바른 괄호 문자열이라면, (A) [A], {A} 도 올바른 괄호 문자열입니다. 
        예를 들어, [] 가 올바른 괄호 문자열이므로, ([]) 도 올바른 괄호 문자열입니다.
    
    만약 A, B가 올바른 괄호 문자열이라면, AB 도 올바른 괄호 문자열입니다. 
        예를 들어, {}와([])가 올바른 괄호 문자열이므로, {}([])도 올바른 괄호 문자열입니다.
    
    올바른 괄호 문자열에서 딱 하나의 문자가 제거된 문자열이 있을 때, 당신은 이 문자열에 제거된 문자 를 다시 삽입함으로써 다시 올바른 괄호 문자열로 만들고자 합니다. 
    이때, 문자열을 삽입할 수 있는 위 치가 여러 개일 수 있습니다.
    올바른 괄호 문자열에서 딱 하나의 문자가 제거된 문자열 s가 매개변수로 주어집니다. 
    s에 제거된 문자 하나를 삽입해서 s를 올바른 괄호 문자열로 만들 수 있는 위치의 개수를 return 하도록 solution 함수를 완성해주세요.

    조건 10s, 2GB
    1 <= s <= 500'000

        입력 : []([[]){}    예상 출력 : 3
        입력 : {([()]))}    예상 출력 : 4
        입력 : (()()()      예상 출력 : 7


    1. 
*/
#include<bits/stdc++.h>
using namespace std;

int ans;
string s;

char match_missing_char(char c){
    if(c == ')') return '(';
    if(c == '}') return '{';
    if(c == ']') return '[';
    return '*';
}

int main(void) {

    cin >> s;

    // missing char 찾기
    char missing_c;
    int open_0 = 0, close_0 = 0;
    int open_1 = 0, close_1 = 0;
    int open_2 = 0, close_2 = 0;

    for(auto& c : s){
        if(c == '(') open_0++; 
        else if(c == ')') close_0 ++;
        else if(c == '{') open_1 ++; 
        else if(c == '}') close_1 ++;
        else if(c == '[') open_2 ++; 
        else if(c == ']') close_2 ++;    
    }
    int sub_0 = open_0 - close_0;
    int sub_1 = open_1 - close_1;
    int sub_2 = open_2 - close_2;
    
    bool is_open = false ;
    if(sub_0 == 1) {missing_c = ')'; }
    else if(sub_1 == 1) {missing_c = '}';} 
    else if(sub_2 == 1) {missing_c = ']'; }
    else if(sub_0 == -1) {missing_c = '('; is_open = true;}
    else if(sub_1 == -1) {missing_c = '{'; is_open = true;}
    else if(sub_2 == -1) {missing_c = '[';is_open = true;}


    if(is_open){
        reverse(s.begin(),s.end());
        for(auto& c : s){
            if(c == '(') c = ')';
            else if(c == '{') c = '}';
            else if(c == '[') c = ']';
            else if(c == ')') c = '(';
            else if(c == '}') c = '{';
            else if(c == ']') c = '[';
        }

        if(missing_c == '(') missing_c =')';
        else if(missing_c == '{') missing_c ='}';
        else if(missing_c == '[') missing_c =']';
    }

    // 이제 무조건 필요한 문자열은 여는 괄호 == 부족한 문자열 : 닫는 괄호 
   
    
    // cout << is_open << '\n';
    // cout << missing_c << '\n';
    // cout << target_c << '\n';
    // cout << s << '\n';
     char target_c = match_missing_char(missing_c);
     int N = s.size();


    // ==================================================================
    const int P = 337;
    const long long MOD1 = 1'000'000'007;
    const long long MOD2 = 1'000'000'003;
    // ==================================================================
    vector<int> L_len_arr(N+1,0);
    vector<bool> L_valid(N+1,0);

    vector<long long> L_h1(N+1,0);
    vector<long long> L_h2(N+1,0);
    vector<long long> L_h1_m(N+1,0);
    vector<long long> L_h2_m(N+1,0);

    vector<char> L_stack(N+1,0);
    vector<int> L_top(N+1,0);

    int L_len = 0;
    bool is_valid = true;

    for(int i = 0 ; i <= N ; i++){
        L_valid[i] = is_valid;
        L_len_arr[i] = L_len;
        L_top[i] = (L_len > 0) ? L_stack[L_len-1] : 0;
        L_h1_m[i] = (L_len > 0) ? L_h1[L_len-1] : 0;
        L_h2_m[i] = (L_len > 0) ? L_h2[L_len-1] : 0;

        if(i >= N) continue;
        if(!is_valid) continue;
        
        char c = s[i];
        if(c == '(' || c =='{' || c== '['){
            L_stack[L_len] = c;
            L_len++;
            L_h1[L_len] = (L_h1[L_len-1] * P + c) % MOD1;
            L_h2[L_len] = (L_h2[L_len-1] * P + c) % MOD2;
        } 
        else{
            if(L_len == 0 || L_stack[L_len-1] != match_missing_char(c) ) {
                is_valid = false;
            } else L_len--;
            
        }
    }
    // ====================================================================

    vector<int> R_len_arr(N+1,0);
    vector<bool> R_valid(N+1,0);

    vector<long long> R_h1(N+1,0);
    vector<long long> R_h2(N+1,0);
    vector<long long> R_h1_m(N+1,0);
    vector<long long> R_h2_m(N+1,0);

    vector<char> R_stack(N+1,0);
    vector<int> R_top(N+1,0);
    int R_len = 0;
    is_valid = true;

    for(int i = N; i >= 0 ; i--){
        R_len_arr[i] = R_len;
        R_valid[i] = is_valid;
        R_h1_m[i] = R_h1[R_len];
        R_h2_m[i] = R_h2[R_len];
        
        if(i <= 0) continue;
        if(!is_valid) continue;

        char c = s[i-1];
        if(c == ')'|| c== ']' || c == '}'){
            char open_c =match_missing_char(c);
            R_stack[R_len] =open_c;
            R_len ++;
            R_h1[R_len] = (R_h1[R_len-1] * P + open_c) % MOD1;
            R_h2[R_len] = (R_h2[R_len-1] * P + open_c) % MOD2;
        } else{
            if(R_len == 0 || R_stack[R_len-1] != c ) is_valid = false;
            else R_len --;
        }
        
    }

    for(int i = 0; i <= N ; i++){
        if(!L_valid[i] || !R_valid[i]) continue;
        if(L_len_arr[i] != R_len_arr[i] + 1) continue;
        if(L_top[i] != target_c) continue;

        if(R_h1_m[i] == L_h1_m[i] && R_h2_m[i] == L_h2_m[i]) ans++;
    }

    cout << ans;




    cout << '\n';

// ================== 디버깅용 깔끔한 표 출력 ==================
    cout << "\n=================================================================\n";
    cout << setw(3) << "i" << " | " 
         << "char" << " | " 
         << setw(5) << "L_len" << " | " 
         << setw(5) << "L_val" << " | " 
         << setw(5) << "R_len" << " | " 
         << setw(5) << "R_val" << " | " 
         << setw(5) << "L_top" << " | "
         << "Match?" << "\n";
    cout << "-----------------------------------------------------------------\n";

    for(int i = 0 ; i <= N; i++) {
        // 보기 좋게 문자 처리 (마지막 인덱스는 문자가 없으므로 공백 처리)
        char ch = (i < N) ? s[i] : ' ';
        char top_ch = (L_top[i] == 0) ? '-' : L_top[i];
        
        // 현재 인덱스가 정답 조건에 맞는지 확인
        bool is_match = false;
        if(L_valid[i] && R_valid[i] && L_len_arr[i] == R_len_arr[i] + 1 && L_top[i] == target_c) {
            if(R_h1_m[i] == L_h1_m[i] && R_h2_m[i] == L_h2_m[i]) is_match = true;
        }

        cout << setw(3) << i << " | " 
             << setw(4) << ch << " | " 
             << setw(5) << L_len_arr[i] << " | " 
             << setw(5) << (L_valid[i] ? "T" : "F") << " | " 
             << setw(5) << R_len_arr[i] << " | " 
             << setw(5) << (R_valid[i] ? "T" : "F") << " | " 
             << setw(5) << top_ch << " | " 
             << (is_match ? "  O " : "  X ") << "\n";
    }
    cout << "=================================================================\n";
    cout << "Final Answer : " << ans << '\n';
    return 0;
}