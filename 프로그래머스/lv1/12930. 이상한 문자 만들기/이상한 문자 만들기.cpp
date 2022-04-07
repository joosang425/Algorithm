#include <string>
#include <vector>

using namespace std;

string solution(string s) {
    string answer = "";
    
    int cnt = 0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == ' ') {
            answer += ' ';
            cnt = 0;
        }
        else {
            if(cnt % 2 == 0) {
                if(s[i] >= 'a' && s[i] <= 'z') 
                    answer += (char)(s[i] - 32);
                else
                    answer += s[i];
            }
            else {
                if(s[i] >= 'A' && s[i] <= 'Z') 
                    answer += (char)(s[i] + 32);
                else
                    answer += s[i];
            }
            cnt++;
        }
    }
    
    return answer;
}