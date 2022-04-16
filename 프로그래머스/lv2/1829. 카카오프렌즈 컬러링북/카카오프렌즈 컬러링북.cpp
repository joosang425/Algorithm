#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

vector<vector<int>> arr;
int row_size, col_size;
bool visited[100][100];
int dir[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int bfs(int y, int x) {
    int cnt = 1;
    queue<pair<int, int>> q;
    q.push({y, x});
    visited[y][x] = true;
    
    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();
        
        for(int i = 0; i < 4; i++) {
            int ny = cy + dir[i][0];
            int nx = cx + dir[i][1];
            
            // 범위를 벗어난 경우 or 방문했었던 곳 or 다른 영역인 경우에는 진행 X 
            if(ny < 0 || ny >= row_size || nx < 0 || nx >= col_size || visited[ny][nx] || arr[y][x] != arr[ny][nx])
                continue;
            
            cnt++;
            visited[ny][nx] = true;
            q.push({ny, nx});
        }
    }
    
    return cnt;
}

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    vector<int> answer(2);
    int cnt = 0, max_size = 0;
    
    memset(visited, false, sizeof(visited));
    arr = picture;
    row_size = m, col_size = n;
    
    // bfs 진행
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(picture[i][j] && !visited[i][j]) {
                cnt++;
                max_size = max(max_size, bfs(i, j));
            }
        }
    }
    
    answer[0] = cnt;
    answer[1] = max_size;
    
    return answer;
}