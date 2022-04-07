#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <set>
using namespace std;

map<string, set<string>> m;  // 유저별 신고한 유저 리스트
map<string, int> resist;    // 유저별 신고 당한 횟수

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    
    for(int i = 0; i < report.size(); i++) {
        string str[2];
        string token;
        stringstream ss(report[i]);
        int idx = 0;
      
        while(ss >> token) 
            str[idx++] = token;
        
        if(m[str[0]].find(str[1]) == m[str[0]].end()) {
            resist[str[1]]++;
            m[str[0]].insert(str[1]);
        }
    }
    
    for(string str : id_list) {
        int cnt = 0;
        for(string temp : m[str]) {
            if(resist[temp] >= k)
                cnt++;
        }
        
        answer.push_back(cnt);
    }
    
    return answer;
}