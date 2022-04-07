#include <string>
#include <vector>
using namespace std;

const int MAX = 1000000;

bool check[MAX];

void eratones() {
    for(int i = 2; i <= MAX; i++) 
        check[i] = true;
    
    for(int i = 2; i * i <= MAX; i++) {
        if(check[i]) {
            for(int j = i * i; j <= MAX; j += i) 
                check[j] = false;
        }
    }
}

int solution(int n) {
    int answer = 0;
    
    eratones();
    
    for(int i = 1; i <= n; i++) {
        if(check[i])
            answer++;
    }
    
    return answer;
}