#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    
    for(int i = 1; i <= n; i++) {
        int temp = n, cur = i;
        
        while(temp > 0) {
            temp -= cur;
            cur++;
        }
        
        if(temp == 0)
            answer++;
    }
    
    return answer;
}