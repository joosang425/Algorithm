#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

string solution(string new_id) {
    string answer = "";
    
    // 1단계
    transform(new_id.begin(), new_id.end(), new_id.begin(), ::tolower);
        
    // 2단계
    string str = "";
    
    for(int i = 0; i < new_id.length(); i++) {
        if((new_id[i] >= 'a' && new_id[i] <= 'z') || (new_id[i] >= '0' && new_id[i] <= '9') || new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.')
            str += new_id[i];
    }

    new_id = str;
    
    // 3단계
    str.clear();
    for(int i = 0; i < new_id.length(); i++) {
        if(new_id[i] == '.') {
            str += '.';
            int cnt = 0;
            
            for(int j = i + 1; new_id[j] == '.'; j++)
                cnt++;
            
            i += cnt;
        }
        else 
            str += new_id[i];
    }
    
    new_id = str;
    
    // 4단계
    if(new_id.front() == '.')
        new_id.erase(new_id.begin());
    if(new_id.back() == '.') 
        new_id.erase(new_id.end() - 1);
    
    // 5단계
    if(new_id.length() == 0) 
        new_id.push_back('a');
    
    // 6단계
    if(new_id.length() >= 16)
        new_id = new_id.substr(0, 15);
    if(new_id.back() == '.')
        new_id.erase(new_id.end() - 1);
    
    // 7단계
    if(new_id.length() <= 2) {
        char temp = new_id[new_id.length() - 1];
        
        while(new_id.length() < 3)
            new_id += temp;
    }
    
    answer = new_id;
    
    return answer;
}