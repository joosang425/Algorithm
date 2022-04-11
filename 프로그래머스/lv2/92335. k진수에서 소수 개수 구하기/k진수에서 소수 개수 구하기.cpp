#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool check(long long num) {
    if(num < 2)
        return false;
    
    for(long long i = 2; i <= sqrt(num); i++) {
        if(num % i == 0)
            return false;
    }
    
    return true;
}

char number[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int solution(int n, int k) {
    int answer = 0;
    
    string temp = "";    
    while(n > 0) {
        temp += number[n % k];
        n /= k;
    }
    
    reverse(temp.begin(), temp.end());
    
    string str = "";
    
    for(int i = 0; i < temp.length(); i++) {
        if(temp[i] == '0' && !str.empty()) {
            long long num = stoll(str);
            if(check(num))
                answer++;
            
            str = "";
        }
        else 
            str += temp[i];
    }
    
    if(!str.empty()) {
        long long num = stoll(str);
        if(check(num))
            answer++;
    }
    
    return answer;
}