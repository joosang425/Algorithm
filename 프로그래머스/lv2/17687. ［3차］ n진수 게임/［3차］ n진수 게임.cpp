#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char number[18] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

// 진법 변환
string to_n(int num, int n) {
    string temp = "";
    if(num == 0)
        return "0";
    
    while(num > 0) {
        temp += number[num % n];
        num /= n;
    }
    
    reverse(temp.begin(), temp.end());
    return temp;
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    string str = "";
    
    for(int i = 0; str.size() <= (m * t); i++) {
        string temp = to_n(i, n);
        str += temp;
    }
    
    for(int i = 0; i < t; i++) 
        answer += str[(m * i) + (p - 1)];
    
    return answer;
}