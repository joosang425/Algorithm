#include <string>
#include <vector>
#include <cstring>
using namespace std;

int dp[100001];

int fib(int n) {
    if(n <= 2) 
        return 1;
    if(n == 0)
        return 0;
    
    if(dp[n] != -1)
        return dp[n];
    
    dp[n] = (fib(n - 1) + fib(n - 2)) % 1234567;
    
    return dp[n];
}

int solution(int n) {
    int answer = 0;
    
    memset(dp, -1, sizeof(dp));
    answer = fib(n);
    
    return answer;
}