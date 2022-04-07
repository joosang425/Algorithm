#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string result;
    map<string, int> completion_check;
    
    for(int i = 0; i < participant.size(); i++)
        completion_check[participant[i]]++;
    
    for(int i = 0; i < completion.size(); i++)
        completion_check[completion[i]]--;
    
    for(int i = 0; i < participant.size(); i++) {
        if (completion_check[participant[i]] != 0)
            result = participant[i];
    }
    
    return result;
}