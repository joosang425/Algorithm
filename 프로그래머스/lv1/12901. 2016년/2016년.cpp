#include <string>
#include <vector>

using namespace std;

string arr[] = {"FRI", "SAT", "SUN", "MON", "TUE", "WED", "THU"};
int month[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

string solution(int a, int b) {
    string answer = "";
    
    int sum = 0;
    
    sum += (b - 1);
    
    for(int i = 1; i < a; i++) 
        sum += month[i];
    
    answer = arr[sum % 7];
    
    return answer;
}