#include <string>
#include <vector>
#include <algorithm>
using namespace std;

long long solution(long long n) {
    long long answer = 0;
    
    vector<int> v;
    
    while(n) {
        v.push_back(n % 10);
        n /= 10;
    }
    
    sort(v.begin(), v.end());
    
    string temp = "";
    for(int i = v.size() - 1; i >= 0; i--)
        temp += to_string(v[i]);
    
    answer = stol(temp);
    
    return answer;
}