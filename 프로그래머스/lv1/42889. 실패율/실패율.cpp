#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(pair<double, int> a, pair<double, int> b) {
    if(a.first == b.first) 
        return a.second < b.second;
    
    return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<pair<double, int>> temp;
    vector<int> answer;
    vector<int> nums(N + 1, 0);
    
    for(int i = 0; i < stages.size(); i++)
        nums[stages[i] - 1]++;
    
    int total_user = stages.size();
    
    for(int i = 0; i < N; i++) {
        if(nums[i] == 0 || total_user == 0) {
            temp.push_back({0, i + 1});
            cout << 0 << ' ';
            continue;
        }
        
        double percent = (double)nums[i] / total_user;     
        total_user -= nums[i];
        
        cout << percent << ' ';
        temp.push_back({percent, i + 1});
    }
    
    sort(temp.begin(), temp.end(), cmp);
    
    for(int i = 0; i < temp.size(); i++)
        answer.push_back(temp[i].second);
    
    return answer;
}