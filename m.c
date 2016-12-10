#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
/*
huanying

workflow: m1 -> m2 -> m3

version 1.0 
*/
  
//模块定义的数据结构
//模块名 ， 模块函数名， 模块库名
// string name;-> libname, funcname
//模块参数对（参数名，参数值）
//<string name,string value>
struct Model{
    string name;
    map<string,string> pars;
};

int tm1(int *a,Model t){ 
    static int begin = stoi(t.pars.find("begin")->second); 
    static int inc = stoi(t.pars.find("inc")->second);
    begin += inc;
    *a= begin;
    if (begin >3) 
        return -1;
    cout<<t.name<<": "<< *a<<endl; 
    return 0;
}  
void tm2(int *b, Model t){ 
    static int begin = stoi(t.pars.find("begin")->second);
    static int inc = stoi(t.pars.find("inc")->second);
   begin += inc;
    *b += begin*10;
    cout<<t.name<<": "<< *b<<endl; 
}
void tm3(int *c, Model t){ 
    static int begin = stoi(t.pars.find("begin")->second);
    static int inc = stoi(t.pars.find("inc")->second);
    begin += inc;
    *c += begin*100;
    cout<<t.name<<": "<< *c<<endl; 
}
    
int main(){
    
    vector< Model > ms;
    Model t;
    t.name ="m1";
    t.pars.insert(pair<string,string>("begin","0"));
    t.pars.insert(pair<string,string>("inc","1"));
    ms.push_back(t);
    
    t.name ="m2";
    t.pars.clear();
    t.pars.insert(pair<string,string>("begin","1"));
    t.pars.insert(pair<string,string>("inc","1"));
    ms.push_back(t);
    
    t.pars.clear();
    t.name ="m3";
    t.pars.insert(pair<string,string>("begin","2"));
    t.pars.insert(pair<string,string>("inc","1"));
    ms.push_back(t);
    cout<<"ms.size()="<<ms.size()<<endl;
    
    map<string,string>::iterator it;
    for (int i=0; i<3; ++i){
        cout<<ms[i].name<<":"<<endl;
        for (it =ms[i].pars.begin(); it!=ms[i].pars.end();++it){
            cout<<it->first<<"=>"<<it->second<<endl;
        }
    } 
    
    int modelCount = 3; 
    int d=0;
    while (-1 !=tm1(&d,ms[0] )){
        tm2(&d,ms[1] );
        tm3(&d,ms[2] );
    }
    return 0; 
}
