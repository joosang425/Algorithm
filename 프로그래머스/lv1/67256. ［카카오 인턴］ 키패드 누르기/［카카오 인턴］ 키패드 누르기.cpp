#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string solution(vector<int> numbers, string hand) {
    string answer = "";
    
    int left = 10, right = 12;
    
    for(int i = 0; i < numbers.size(); i++) {
        if(numbers[i] == 0)
            numbers[i] = 11;
        
        if(numbers[i] % 3 == 1) {
            answer += 'L';
            left = numbers[i];
        }
        else if(numbers[i] % 3 == 0) {
            answer += 'R';
            right = numbers[i];
        }
        else {
            // 왼
            int temp = abs(left - numbers[i]);
            int leftD = (temp / 3) + (temp % 3);
            
            // 오
            temp = abs(right - numbers[i]);           
            int rightD = (temp / 3) + (temp % 3);
            
            if(leftD < rightD) {
                left = numbers[i];
                answer += 'L';
            }
            else if(rightD < leftD) {
                right = numbers[i];
                answer += 'R';
            }
            else {
                if(hand == "left") {
                    left = numbers[i];
                    answer += 'L';
                }
                else {
                    right = numbers[i];
                    answer += 'R';
                }
            }
        }
    }
    
    return answer;
}