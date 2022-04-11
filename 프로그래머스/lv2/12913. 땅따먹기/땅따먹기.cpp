#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[100000][4];

int solution(vector<vector<int> > land)
{
    int answer = 0;

    dp[0][0] = land[0][0];
    dp[0][1] = land[0][1];
    dp[0][2] = land[0][2];
    dp[0][3] = land[0][3];
    
    for(int i = 1; i < land.size(); i++) {
        for(int j = 0; j < 4; j++) {
            int num = 0;
            for(int s = 0; s < 4; s++) {
                if(j == s)
                    continue;
                
                num = max(num, dp[i - 1][s]);
            }
            
            dp[i][j] = num + land[i][j];
        }
    }
    
    for(int i = 0; i < 4; i++)
        answer = max(answer, dp[land.size() - 1][i]);

    return answer;
}