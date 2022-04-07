#include <string>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

int solution(int n) {
    int answer = 0;
    
    string temp = "";
    while(n) {
        temp = temp + to_string(n % 3);
        n /= 3;
    }
    
    int idx = 0;
    for(int i = temp.size() - 1; i >= 0; i--) {
        if(temp[i] == '0') {
            idx++;
            continue;
        }
        
        answer += (temp[i] - '0') * pow(3, idx++);
    }
    
    return answer;
}