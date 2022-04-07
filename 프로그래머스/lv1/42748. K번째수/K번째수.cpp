#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int> array, int i, int j, int k) {
    vector<int> temp;
    
    for(int cur = i; cur <= j; cur++) 
        temp.push_back(array[cur]);
    
    sort(temp.begin(), temp.end());
    
    return temp[k];
}

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    
    for(int t = 0; t < commands.size(); t++) {
        int i = commands[t][0] - 1;
        int j = commands[t][1] - 1;
        int k = commands[t][2] - 1;
        
        answer.push_back(solve(array, i, j, k));
    }
    
    return answer;
}