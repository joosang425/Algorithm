#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> numbers) {
    int answer = 0;
    
    sort(numbers.begin(), numbers.end());
    
    int idx = 0;
    for(int i = 0; i < 10;) {
        if(numbers[idx] != i)
            answer += i++;
        else {
            idx++;
            i++;
        }
    }
    
    return answer;
}