#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

map<string, string> m;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<pair<string,string>> temp;
    
    for(int i = 0; i < record.size(); i++) {
        // 문자열 자르기
        string token;
        stringstream ss(record[i]);
        string arr[3];
        int idx = 0;
        
        while(ss >> token)
            arr[idx++] = token;
        
        // Enter인 경우 다른 vector에 아이디와 "Enter" 문자열 삽입
        // map에 닉네임이 바뀔 수 있도록 아이디를 기준, 닉네임을 값으로 저장
        if(arr[0] == "Enter") {
            temp.push_back({arr[1], "Enter"});
            m[arr[1]] = arr[2];
        }
        // Leave인 경우 vector에 아이디와 "Leave" 문자열 삽입
        else if(arr[0] == "Leave")
            temp.push_back({arr[1], "Leave"});
        // Change인 경우 map에 닉네임만 변경
        else 
            m[arr[1]] = arr[2];
    }
    
    // Enter과 Leave를 저장한 벡터만큼 진행
    for(int i = 0; i < temp.size(); i++) {
        string str = m[temp[i].first];
        
        if(temp[i].second == "Enter") 
            str += "님이 들어왔습니다.";
        else 
            str += "님이 나갔습니다.";
        
        answer.push_back(str);
    }
    
    return answer;
}