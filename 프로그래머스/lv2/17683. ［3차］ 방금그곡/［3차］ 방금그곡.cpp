#include <string>
#include <vector>
using namespace std;

void change(string& str) {
    for(int j = 0; j < str.length();) {
        if(str[j] == '#') {
            str[j - 1] = tolower(str[j - 1]);
            str.erase(str.begin() + j);
        }
        else 
            j++;
    }
}

string solution(string m, vector<string> musicinfos) {
    int large = 0;
    string answer = "";
    
    change(m);
    
    for(int i = 0; i < musicinfos.size(); i++) {
        string h1 = musicinfos[i].substr(0, 2);
        string m1 = musicinfos[i].substr(3, 2);
        string h2 = musicinfos[i].substr(6, 2);
        string m2 = musicinfos[i].substr(9, 2);
        
        int time = abs(stoi(h2) - stoi(h1)) * 60;
        if(m1 > m2) {
            time -= 60;
            time += (stoi(m2) - stoi(m1)) + 60;
        }
        else 
            time += stoi(m2) - stoi(m1);
        
        string temp = musicinfos[i].substr(12);
        
        string title = temp.substr(0, temp.find(','));
        string melody = temp.substr(title.length() + 1);
    
        change(melody);
        
        string str = melody;
        
        while(str.length() < time) 
            str += melody;
        
        str = str.substr(0, time);
        
        if(str.find(m) != string::npos) {
            if(large < str.length()) {
                large = str.length();
                answer = title;
            }
        }
    }
    
    if(answer == "")
        answer = "(None)";
    
    return answer;
}