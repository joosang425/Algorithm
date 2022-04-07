#include <string>
#include <vector>
#include <iostream>
using namespace std;

string solution(string s, int n) {
    string answer = "";
    
    for(int i = 0; i < s.length(); i++) {
 
        if(s[i] >= 'a' && s[i] <= 'z') {
            cout << s[i] + n - 'a' <<' ';
        
            answer += (s[i] + n - 'a') % 26 + 'a';
        }
        else if(s[i] >= 'A' && s[i] <= 'Z'){
            cout << s[i] + n - 'A' <<' ';
            
            answer += (s[i] + n - 'A') % 26 + 'A';
        }
        else
            answer += s[i];
    }
    
    return answer;
}