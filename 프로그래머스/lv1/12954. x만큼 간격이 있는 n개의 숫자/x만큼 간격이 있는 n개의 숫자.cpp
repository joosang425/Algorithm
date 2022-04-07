#include <string>
#include <vector>

using namespace std;

vector<long long> solution(int x, int n) {
    vector<long long> answer;
    
    for(int i = x; ; i += x) {
        if(answer.size() == n) 
            break;
        
        answer.push_back(i);
    }
    
    return answer;
}