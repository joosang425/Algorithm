#include <string>
#include <vector>
using namespace std;

int maxdif = 0;
vector<int> answer(1, -1);

bool cmp(vector<int> ryan) {
    for(int i = 10; i >= 0; i--) {
        if(ryan[i] > answer[i])
            return true;
        else if(ryan[i] < answer[i])
            return false;
    }
}

void calc(vector<int> ryan, vector<int> apeach) {
    int r_score = 0, a_score = 0;
    
    for(int i = 0; i < 11; i++) {
        if(ryan[i] > apeach[i])
            r_score += 10 - i;
        else if(apeach[i] > 0)
            a_score += 10 - i;
    }
    
    int dif = r_score - a_score;
    if(dif > 0 && maxdif <= dif) {
        if(maxdif == dif && !cmp(ryan))
            return;
        
        maxdif = dif;
        answer = ryan;
    } 
}

void solve(int idx, int arrow, vector<int> ryan, vector<int> apeach) {
    if(idx == 11 || arrow == 0) {
        ryan[10] += arrow;
        calc(ryan, apeach);
        ryan[10] -= arrow;
        
        return;
    }
    
    if(apeach[idx] < arrow) {
        ryan[idx] += apeach[idx] + 1;
        solve(idx + 1, arrow - apeach[idx] - 1, ryan, apeach);
        ryan[idx] -= apeach[idx] + 1;
    }
    
    solve(idx + 1, arrow, ryan, apeach);
}

vector<int> solution(int n, vector<int> info) {
    vector<int> ryan(11, 0);
    
    solve(0, n, ryan, info);
    
    if(answer.empty())
        answer.push_back(-1);
    
    return answer;
}