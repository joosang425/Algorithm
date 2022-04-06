#include <string>
#include <vector>
#include <map>
using namespace std;

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    map<char, int> m;
    
    for(int i = 0; i < skill.size(); i++) 
        m[skill[i]] = i + 1;
    
    for(auto skt : skill_trees) {
        int cnt = 1;
        bool check = false;
        
        for(int i = 0; i < skt.length(); i++) { 
            if(m[skt[i]] > cnt) {
                check = true;
                break;
            }
            else if(m[skt[i]] == cnt) 
                cnt++;
        }
        
        if(!check) 
            answer++;
    }
    
    return answer;
}