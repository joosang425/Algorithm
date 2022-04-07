#include <string>
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

stack<int> s;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    
    for(int i = 0; i < moves.size(); i++) {
        int idx = moves[i] - 1;
        
        for(int y = 0; y < board.size(); y++) {
            if(board[y][idx] != 0) {
                if(s.empty())
                    s.push(board[y][idx]);
                else if(!s.empty() && s.top() == board[y][idx]){
                    s.pop();
                    answer += 2;
                }
                else if(!s.empty() && s.top() != board[y][idx])
                    s.push(board[y][idx]);
                
                board[y][idx] = 0;
                break;
            }
        }
    }
    
    return answer;
}