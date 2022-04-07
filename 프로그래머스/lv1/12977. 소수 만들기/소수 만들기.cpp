#include <vector>
#include <iostream>
using namespace std;

const int MAX = 50000;

int answer;
bool isTrue[MAX + 1], selected[50];

void check() {
    for(int i = 2; i <= MAX; i++)
        isTrue[i] = true;
    
    for(int i = 2; i * i <= MAX; i++) {
        if(isTrue[i]) {
            for(int j = i * i; j <= MAX; j += i)
                isTrue[j] = false;
        }
    }
}

void dfs(vector<int> nums, int idx, int cnt, int sum) {
    if(cnt == 3) {
        if(isTrue[sum])
            answer++;
        
        return;
    }
    
    for(int i = idx; i < nums.size(); i++) {
        if(selected[i])
            continue;
        
        selected[i] = true;
        dfs(nums, i + 1, cnt + 1, sum + nums[i]);
        selected[i] = false;
    }
}

int solution(vector<int> nums) {   
    check();
    
    dfs(nums, 0, 0, 0);

    return answer;
}