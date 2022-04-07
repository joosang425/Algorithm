#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool selected[201];

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    
    for(int i = 0; i < numbers.size() - 1; i++) {
        for(int j = i + 1; j < numbers.size(); j++) {
            if(selected[numbers[i] + numbers[j]])
                continue;
            
            answer.push_back(numbers[i] + numbers[j]);
            selected[numbers[i] + numbers[j]] = true;
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}