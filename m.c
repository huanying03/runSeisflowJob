#include <stdio.h>
#include <map>
#include <string>
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
    
    int d=0;
    while (-1 !=m1(&d)){
        printf("m1:d=%d\n",d);
        m2(&d);
        printf("m2:d=%d\n",d);
        m3(&d);
        printf("m3:d=%d\n",d);
    }
    return 0; 
}
