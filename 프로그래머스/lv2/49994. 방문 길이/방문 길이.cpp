#include <string>
#include <iostream>
using namespace std;

bool visited[11][11][11][11];

int solution(string dirs) {
    int answer = 0;
    
    int y = 5, x = 5;
    
    for(int i = 0; i < dirs.length(); i++) {
        if(dirs[i] == 'U') {
            if(y - 1 < 0) 
                continue;
            if(!visited[y][x][y - 1][x] && !visited[y - 1][x][y][x])
                answer++;
            
            visited[y][x][y - 1][x] = true;
            visited[y - 1][x][y][x] = true;
            y--;
        }
        else if(dirs[i] == 'L') {
            if(x - 1 < 0) 
                continue;           
            if(!visited[y][x][y][x - 1] && !visited[y][x - 1][y][x])
                answer++;
            
            visited[y][x][y][x - 1] = true;
            visited[y][x - 1][y][x] = true;
            x--;
        }
        else if(dirs[i] == 'D') {
            if(y + 1 > 10)
                continue;
            if(!visited[y][x][y + 1][x] && !visited[y + 1][x][y][x])
                answer++;
            
            visited[y][x][y + 1][x] = true;
            visited[y + 1][x][y][x] = true;
            y++;
        }
        else {
            if(x + 1 > 10)
                continue;
            if(!visited[y][x][y][x + 1] && !visited[y][x + 1][y][x])
                answer++;
            
            visited[y][x][y][x + 1] = true;
            visited[y][x + 1][y][x] = true;
            x++;
        }
    }
    
    return answer;
}