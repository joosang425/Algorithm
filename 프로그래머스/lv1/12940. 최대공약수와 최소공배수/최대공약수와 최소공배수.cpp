#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int n, int m) {
    vector<int> answer;

    int temp = 0;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0 && m % i == 0)
            temp = max(temp, i);
    }
    
    answer.push_back(temp);
    
    int num = temp * (n / temp) * (m / temp);
    
    answer.push_back(num);
    
    return answer;
}