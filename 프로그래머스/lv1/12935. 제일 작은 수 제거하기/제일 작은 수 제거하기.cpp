#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> arr) {
    vector<int> answer;
    
    int num = 987654321, idx = 0;
    for(int i = 0; i < arr.size(); i++) {
        if(num > arr[i]) {
            num = arr[i];
            idx = i;
        }
    }
    
    arr.erase(arr.begin() + idx);
    
    if(arr.empty())
        answer.push_back(-1);
    else
        answer = arr;
    
    return answer;
}