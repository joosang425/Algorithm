#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

map<string, int> m;

int solution(string s) {
    int answer = 0;
    
    m.insert({"zero", 0});
    m.insert({"one", 1});
    m.insert({"two", 2});
    m.insert({"three", 3});
    m.insert({"four", 4});
    m.insert({"five", 5});
    m.insert({"six", 6});
    m.insert({"seven", 7});
    m.insert({"eight", 8});
    m.insert({"nine", 9});
    
    map<string, int>::iterator it;
    string store = "";
    string temp = "";
    
    for(int i = 0; i < s.length(); i++) {
        if(s[i] >= '0' && s[i] <= '9')
            store += s[i];
        else {
            temp += s[i];
            
            it = m.find(temp);
            
            if(it != m.end()) {
                store += (m[temp] + '0');
                temp = "";
            }
        }
    }
    
    answer = stoi(store);
    
    return answer;
}