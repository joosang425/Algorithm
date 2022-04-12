#include <string>
#include <vector>
using namespace std;

string solution(string s) {
    string answer = "";
    
    bool isCur = false;
    for(int i = 0; i < s.length(); i++) {
        if(!isCur) {
            if(s[i] >= '0' && s[i] <= '9')
                answer += s[i];
            else 
                answer += toupper(s[i]);
            
            isCur = true;
        }
        else {
            if(s[i] == ' ' && s[i + 1] != ' ') 
                isCur = false;
            
            answer += tolower(s[i]);
        }
    }
    
    return answer;
}