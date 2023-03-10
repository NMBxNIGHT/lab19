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

void importDataFromFile(string filename,vector<string> &name,vector<int> &scores,vector<char> &grade){
  
    ifstream file;
    file.open(filename.c_str());
    string data;
    int score[3];
    char format[]="%[^:]: %d %d %d",S_name[500]={};
    
    while(getline(file,data)){
    sscanf(data.c_str(),format,S_name,&score[0],&score[1],&score[2]);
    name.push_back(S_name);
    scores.push_back(score[0]+score[1]+score[2]);
    grade.push_back(score2grade(score[0]+score[1]+score[2]));
    }
    file.close();
}

void getCommand(string &command,string &key){
    string text;
    cout <<"Please input your command: ";
    getline(cin,text);
 
    char format[]="%s %[^\n]\n";
    char ss[50],bb[1000];
    sscanf(text.c_str(),format,&ss,&bb);
    command = ss;
    key = bb;    
}

void searchName(vector<string> name,vector<int> scores,vector<char> grade,string key){
    unsigned int check=0;
    cout<<"---------------------------------\n";
    for(unsigned int i=0;i<scores.size();i++){
        string keycheck=name.at(i);
        keycheck=toUpperStr(keycheck);
        if(key==keycheck){
           printf("%s's score = %d\n",name[i].c_str(),scores[i]); 
           printf("%s's grade = %c\n",name[i].c_str(),grade[i]);
        }else{
            check++;
        }
    }

    if(check == scores.size()){
        cout << "Cannot found.\n";
    }
    cout<<"---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grade,string key){
 unsigned int check=0;
 cout<<"---------------------------------\n";
    for(unsigned int i=0;i<scores.size();i++){
        char keyy=key[0];
        if(keyy == grade[i]){
         printf("%s (%d)\n",names[i].c_str(),scores[i]);
        }else{
            check++;
        }
    }

    if(check == scores.size()){
        cout<<"Cannot found.\n";
    }
    cout<<"---------------------------------\n";
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