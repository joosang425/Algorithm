#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    
    vector<int> v(n, 1);
    
    for(int i = 0; i < reserve.size(); i++) {
        int num = reserve[i] - 1;
        
        v[num]++;
    }
    
    for(int i = 0; i < lost.size(); i++) {
        int num = lost[i] - 1;
        
        v[num]--;
    }
    
    for(int i = 0; i < n; i++) {
        if(v[i] == 0) {
            if(i - 1 >= 0 && v[i - 1] >= 2) {
                v[i - 1]--;
                v[i]++;
            }
            else if(i + 1 < n && v[i + 1] >= 2) {
                v[i + 1]--;
                v[i]++;
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(v[i] >= 1) 
            answer++;
    }
    
    return answer;
}