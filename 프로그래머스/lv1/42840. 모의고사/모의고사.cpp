#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int arr1[5] = {1, 2, 3, 4, 5};   
int arr2[8] = {2, 1, 2, 3, 2, 4, 2, 5};
int arr3[10] = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    int arr1_idx = 0, arr2_idx = 0, arr3_idx = 0;
    int arr1_cnt = 0, arr2_cnt = 0, arr3_cnt = 0;
    
    for(int i = 0; i < answers.size(); i++) {
        if(answers[i] == arr1[arr1_idx++ % 5])
            arr1_cnt++;
        if(answers[i] == arr2[arr2_idx++ % 8])
            arr2_cnt++;
        if(answers[i] == arr3[arr3_idx++ % 10])
            arr3_cnt++;
    }
    
    int large = max(arr1_cnt, max(arr2_cnt, arr3_cnt));
    
    if(large == arr1_cnt)
        answer.push_back(1);
    if(large == arr2_cnt)
        answer.push_back(2);
    if(large == arr3_cnt)
        answer.push_back(3);
    
    return answer;
}