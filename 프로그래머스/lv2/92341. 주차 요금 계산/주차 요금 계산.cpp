#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
using namespace std;

// map을 in, out으로 나누어서 생성
map<string, vector<int>> in;
map<string, vector<int>> out;

// 주차 요금 계산을 위한 시간 -> 분 변경
int to_minute(string str) {
    int pos = str.find(':');
    
    string hour = str.substr(0, pos);
    string minute = str.substr(pos + 1);
    
    int value = (stoi(hour) * 60) + stoi(minute);
    
    return value;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    
    // 공백을 기준으로 문자열 나누기
    for(int i = 0; i < records.size(); i++) {
        string token;
        stringstream ss(records[i]);
        
        string str[3];
        int idx = 0;
        
        while(ss >> token)
            str[idx++] = token;
        
        string time = str[0];
        string car_number = str[1];
        string inout = str[2];
        
        if(inout == "IN") {
            int num = to_minute(time);
            
            in[car_number].push_back(num);
        }
        else {
            int num = to_minute(time);
            
            out[car_number].push_back(num);
        }
    }
    
    // 여러 번 입차가 가능하기 때문에 for문으로 전체 시간 계산
    for(auto it : in) {
        int total_fee = 0;
        int dis = 0;
        string temp = it.first;
      
        int size = in[temp].size();
        
        for(int i = 0; i < size; i++) { 
            int in_time = in[temp][0];
            int out_time = 0;
            
            // in 맵 기준으로 돌리고 23:59분은 기록되지 않는 것을 방지하기 위한 if문
            if(out[temp].empty())
                out_time = 1439;    // 23:59은 분으로 계산하면 1439
            else {
                out_time = out[temp][0];
                out[temp].erase(out[temp].begin());
            }
            
            in[temp].erase(in[temp].begin());
            
            dis += out_time - in_time;
        }
        
        // 시간이 기준 시간보다 클 경우 기본 요금을 더 해주고 현재 시간에서 빼준다.
        total_fee += fees[1];
        dis -= fees[0];
            
        // 기준 시간을 뺀 뒤에도 시간이 남은 경우 단위 요금 책정
        if(dis > 0) {
            int remain_fee = 0;
            
            // 올림을 위한 if문
            if(dis % fees[2] != 0) 
                remain_fee = dis / fees[2] + 1;
            else
                remain_fee = dis / fees[2];
                
            total_fee += remain_fee * fees[3];
        }
        
        answer.push_back(total_fee);
    }
    
    return answer;
}