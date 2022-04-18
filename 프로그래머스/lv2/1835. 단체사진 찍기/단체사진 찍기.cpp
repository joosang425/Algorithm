#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

char member[8] = {'A', 'C', 'F', 'J', 'M', 'N', 'R', 'T'};
int answer;
bool selected[8];
vector<string> arr;

void dfs(string temp) {
    if(temp.length() == 8) {
        for(int i = 0; i < arr.size(); i++) {
            char first = arr[i][0];
            char second = arr[i][2];
            char op = arr[i][3];
            int dis = arr[i][4] - '0';
            
            int f_pos = temp.find(first);
            int s_pos = temp.find(second);
            
            int pos_dis = abs(f_pos - s_pos) - 1;
            
            if(op == '=') {
                if(dis != pos_dis)
                    return;
            }
            else if(op == '<') {
                if(dis <= pos_dis)
                    return;
            }
            else {
                if(dis >= pos_dis)
                    return;
            }
        }
        
        answer++;
        return;
    }
    
    for(int i = 0; i < 8; i++)  {
        if(selected[i])
            continue;
        
        selected[i] = true;
        dfs(temp + member[i]);
        selected[i] = false;
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {
    memset(selected, false, sizeof(selected));
    answer = 0;
    arr = data;
    
    // 조합
    dfs("");
    
    return answer;
}
