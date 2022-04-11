#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct File {
    string file_name;
    string file_head;
    int file_number;
};

File f[1000];

bool compare(File a, File b) {
    if(a.file_head == b.file_head) 
        return a.file_number < b.file_number;
    
    return a.file_head < b.file_head;
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    
    for(int i = 0; i < files.size(); i++) {
        string file = files[i];       
        f[i].file_name = file;  // 파일명
        
        int idx = 0;
        while(file[idx] < '0' || file[idx] > '9') // head
            f[i].file_head += tolower(file[idx++]);
        string temp = "";
        while(file[idx] >= '0' && file[idx] <= '9') 
            temp += tolower(file[idx++]);
        
        f[i].file_number = stoi(temp);  // number
        
        cout << f[i].file_head << ' ' << f[i].file_number << '\n';
    }
    
    stable_sort(f, f + files.size(), compare);
    
    for(int i = 0; i < files.size(); i++) 
        answer.push_back(f[i].file_name);
    
    return answer;
}