#include <string>
#include <vector>
using namespace std;

string remain[3] = {"4", "1", "2"};

string solution(int n) {
    string answer = "";    
    
    while(n != 0) {
        answer = remain[n % 3] + answer;
        
        if(n % 3 == 0) 
            n = n / 3 - 1;
        else 
            n = n /3;
    }
    
    return answer;
}