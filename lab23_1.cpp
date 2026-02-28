#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream fin(filename.c_str());
    string line;

    while(getline(fin, line)){
        char name[200];
        int s1, s2, s3;
        sscanf(line.c_str(), "%[^:]:%d %d %d", name, &s1, &s2, &s3);
        int total = s1 + s2 + s3;
        
        names.push_back(string(name));
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
    fin.close();

}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    string line;
    getline(cin, line);
    if(line.size() == 0){
        getline(cin, line);
    }
    string::size_type pos = line.find(' ');
    if(pos == string::npos){
        command = line;
        key = "";
    }else{
        command = line.substr(0, pos);
        key = line.substr(pos + 1);
    }

}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
        bool found = false;
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            found = true;
            break;
        }
    }

    if(!found){cout << "Cannot found.\n";}
    cout << "---------------------------------\n";

}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
        bool found = false;
    cout << "---------------------------------\n";

    char g = key[0];
    for(unsigned i = 0; i < grades.size(); i++){
        if(grades[i] == g){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }

    if(!found){cout << "Cannot found.\n";}
    cout << "---------------------------------\n";

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}