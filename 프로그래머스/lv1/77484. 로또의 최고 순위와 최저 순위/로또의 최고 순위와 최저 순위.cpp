#include <string>
#include <vector>

using namespace std;

int arr[7] = {6, 6, 5, 4, 3, 2, 1};

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    
    int zero = 0, same = 0;
    for(int i = 0; i < lottos.size(); i++) {
        if(lottos[i] == 0){
            zero++;
            continue;
        }
        
        for(int j = 0; j < win_nums.size(); j++) {
            if(lottos[i] == win_nums[j]) {
                same++;
                break;
            }
        }
    }
    
    int Max = zero + same;
    int Min = same;
    
    answer.push_back(arr[Max]);
    answer.push_back(arr[Min]);
    
    return answer;
}