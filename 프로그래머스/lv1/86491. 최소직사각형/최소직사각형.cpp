#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> sizes) {
    int answer = 0, width = 0, height = 0;
    
    for(int i = 0; i < sizes.size(); i++)
        sort(sizes[i].begin(), sizes[i].end());

    for(int i = 0; i < sizes.size(); i++) {
        width = max(width, sizes[i][1]);
        height = max(height, sizes[i][0]);
    }
    
    answer = width * height;
    
    return answer;
}