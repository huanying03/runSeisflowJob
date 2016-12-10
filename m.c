#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//#include <stdlib.h> // atoi()
using namespace std;
/*
lushuqin

workflow: m1 -> m2 -> m3

version 1.0 
*/
int m1(int *a){//  +1 
    static int i=0;
    i++;
    *a=i;
    if (i>3) 
        return -1;
    return 0;
}

void m2(int *b){//  + j*j
    static int j=1;
    j++;
    *b += j*10;
}
void m3(int *c){
    static int k=2;
    k++;
    *c += k*100;
}
  //version 1.1
int tm1(int *a, map<string,string> pars){//  +1 
    static int begin = stoi(pars.find("begin")->second);
   // cout<<"tm1:begin="<<begin<<endl;
    static int inc = stoi(pars.find("inc")->second);
    begin += inc;
    *a= begin;
    if (begin >3) 
        return -1;
    return 0;
}  
void tm2(int *b, map<string,string> pars){//  + j*j
    static int begin = stoi(pars.find("begin")->second);
    //cout<<"tm2:begin="<<begin<<endl;
    static int inc = stoi(pars.find("inc")->second);
   begin += inc;
    *b += begin*10;
}
void tm3(int *c, map<string,string> pars){
    static int begin = stoi(pars.find("begin")->second);
    //cout<<"tm2:begin="<<begin<<endl;
    static int inc = stoi(pars.find("inc")->second);
    begin += inc;
    *c += begin*100;
}
    
//模块定义的数据结构
//模块名 ， 模块函数名， 模块库名
// string name;-> libname, funcname
//模块参数对（参数名，参数值）
//<string name,string value>
struct Model{
    string name;
    map<string,string> pars;
};
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
        for (it =ms[i].pars.begin(); it!=ms[i].pars.end();++it){
            cout<<it->first<<"=>"<<it->second<<endl;
        }
    }
    it = ms[1].pars.find("begin");
    cout<<"tm2:begin="<<it->second<<endl;
    //return 0;
    
    int modelCount = 3; 
    int d=0;
    while (-1 !=tm1(&d,ms[0].pars)){
        printf("m1:d=%d\n",d);
        tm2(&d,ms[1].pars);
        printf("m2:d=%d\n",d);
        tm3(&d,ms[2].pars);
        printf("m3:d=%d\n",d);
    }
    return 0; 
}
