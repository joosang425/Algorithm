#include <string>
#include <vector>
using namespace std;

vector<vector<int>> board;
int one, zero;

void solve(int y, int x, int size) {
    int temp = board[y][x];
    bool flag = true;
    
    if(size == 1) {
        if(temp == 1) 
            one++;
        else
            zero++;
    }
    else {
        for(int i = y; i < y + size; i++) {
            for(int j= x; j < x + size; j++) {
                if(temp != board[i][j]) {
                    flag = false;
                    break;
                }
            }
            if(!flag)
                break;
        }
        
        if(!flag) {
            solve(y, x, size / 2);
            solve(y, x + size / 2, size / 2);
            solve(y + size / 2, x, size / 2);
            solve(y + size / 2, x + size / 2, size / 2);
        }
        else {
            if(temp == 1)
                one++;
            else 
                zero++;
        }
    }
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> answer;
    
    board = arr;
    solve(0, 0, arr.size());
    
    answer = {zero, one};
    
    return answer;
}