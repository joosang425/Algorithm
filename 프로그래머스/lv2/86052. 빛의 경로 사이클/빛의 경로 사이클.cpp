#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> arr;
int row_size, col_size;

int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool visited[501][501][4];

int ch_d(char d, int num) {
    if(d == 'L'){
        if(num == 0) return 2;
        else if(num == 1) return 3;
        else if(num == 2) return 1;
        else return 0;
    }
    else {
        if(num == 0) return 3;
        else if(num == 1) return 2;
        else if(num == 2) return 0;
        else return 1;
    }
}

int solve(int y, int x, int d, int cnt) {
    if(visited[y][x][d])
        return cnt;
    
    visited[y][x][d] = true;
       
    if(arr[y][x] != 'S')
        d = ch_d(arr[y][x], d);
    
    y += dir[d][0];
    if(y == row_size)
        y = 0;
    else if(y < 0)
        y = row_size - 1;
    
    x += dir[d][1];
    if(x == col_size)
        x = 0;
    else if(x < 0)
        x = col_size - 1;
    
    return solve(y, x, d, cnt + 1);
}

vector<int> solution(vector<string> grid) {
    arr = grid;
    row_size = grid.size();
    col_size = grid[0].size();
    
    vector<int> answer;
    
    for(int i = 0; i < row_size; i++) {
        for(int j = 0; j < col_size; j++) {
            for(int k = 0; k < 4; k++) {
                int cnt = solve(i, j, k, 0);                
                if(cnt != 0)
                    answer.push_back(cnt);
            }
        }
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}