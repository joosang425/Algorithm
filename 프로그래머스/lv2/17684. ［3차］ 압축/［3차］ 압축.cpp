#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map<string, int> m;

vector<int> solution(string msg) {
    vector<int> answer;
    string str = "";
    
    for(int i = 0; i < 26; i++) {
        str += 'A' + i;
        m[str] = i + 1;
        str = "";
    }
    
    int cur = 27;
    
    for(int i = 0; i < msg.length(); i++) {
        string temp = "";
        temp += msg[i];
        int next = i + 1;
        int cnt = 0;
        
        while(m.find(temp) != m.end()) {
            temp += msg[next++];
            cnt++;
        }
        
        i += cnt - 1;
        m[temp] = cur++;
        temp = temp.substr(0, temp.length() - 1);
        answer.push_back(m[temp]);
    }
    
    return answer;
}