#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(int n) {
    int answer = 0;
    
    int first_cnt = 0, temp = n;
    while(temp > 0) {
        if(temp % 2) 
            first_cnt++;
        
        temp /= 2;
    } 
    
    for(int i = n + 1;;i++) {
        int cnt = 0, temp = i;
        
        while(temp > 0) {
            if(temp % 2)
                cnt++;
            
            temp /= 2;
        }
        
        if(cnt == first_cnt) {
            answer = i;
            break;
        }
    }
    
    return answer;
}