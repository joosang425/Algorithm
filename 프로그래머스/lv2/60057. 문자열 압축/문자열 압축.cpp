#include <string>
#include <vector>
using namespace std;

int solution(string s) {
    int answer = s.length();
    
    // 최대 압축 가능 길이가 문자열 크기의 반
    for(int i = 1; i <= s.length() / 2; i++) {
        string str = "";
        // 압축 길이 만큼 잘라서 저장
        string temp = s.substr(0, i);
        int cnt = 1;
        
        for(int j = i; j < s.length(); j += i) {
            // 현재 문자열과 같은 크기로 자른 뒤 비교 진행
            if(temp == s.substr(j, i))
                cnt++;
            else {
                // 2개 이상이면 숫자를 저장한 뒤 문자열 저장
                if(cnt > 1) 
                    str += to_string(cnt);
                
                str += temp;
                // 같지 않은 경우 현재 위치에서 i 크기 만큼 잘라서 for문 진행
                temp = s.substr(j, i);
                cnt = 1;
            }
        }
        
        if(cnt > 1) 
            str += to_string(cnt);
        str += temp;
        
        if(answer > str.length())
            answer = str.length();  
    }
    
    return answer;
}