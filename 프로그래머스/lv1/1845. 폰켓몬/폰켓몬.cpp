#include <vector>
#include <set>
#include <algorithm>
using namespace std;

set<int> s;

int solution(vector<int> nums)
{
    int answer = 0;
    
    for(int i = 0; i < nums.size(); i++) 
        s.insert(nums[i]);
    
    answer = min(nums.size() / 2, s.size());
    
    return answer;
}