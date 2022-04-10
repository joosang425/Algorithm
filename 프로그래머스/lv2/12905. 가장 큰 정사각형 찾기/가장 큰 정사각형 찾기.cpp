#include <iostream>
#include<vector>
using namespace std;

int solution(vector<vector<int>> board)
{
    int answer = board[0][0];  
    int arr[1000][1000];
    
    for(int i = 1; i < board.size(); i++) {
        for(int j = 1; j < board[0].size(); j++) {
            if(board[i][j]) {
                board[i][j] = 1 + min(min(board[i - 1][j - 1], board[i - 1][j]), board[i][j - 1]);
                answer = max(answer, board[i][j]);
            }
        }
    }
    
    return answer * answer;
}