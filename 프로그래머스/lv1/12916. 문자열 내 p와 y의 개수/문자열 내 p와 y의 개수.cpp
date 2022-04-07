#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool solution(string s)
{
    bool answer = true;

    transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    int p_cnt = 0, y_cnt = 0;
    
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == 'p')
            p_cnt++;
        else if(s[i] == 'y')
            y_cnt++;
    }
    
    if(p_cnt == 0 && y_cnt == 0)
        answer = true;
    else if(p_cnt == y_cnt)
        answer == true;
    else 
        answer = false;

    return answer;
}