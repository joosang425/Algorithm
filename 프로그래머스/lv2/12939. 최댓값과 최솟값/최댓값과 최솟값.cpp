#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

string solution(string s) {
    string answer = "";
    
    vector<int> v;
    
    string token;
    stringstream ss(s);
    while(ss >> token) {
        v.push_back(stoi(token));
    }
    
    sort(v.begin(), v.end());
    
    answer += to_string(v[0]);
    answer += " ";
    answer += to_string(v[v.size() - 1]);
    
    return answer;
}