#include "addnoise.h"
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
using namespace std;

void addnoise(SuHead *hd,float *data,int ns,map<string,string> *pars){

    std::string::size_type sz;
    
    int inputCount = std::stoi(pars->find("input")->second,&sz);
    inputCount++;
    pars->at("input")=to_string(inputCount);
    cout<<"addnoise: inputCount="<< stoi(pars->find("input")->second,&sz)<<endl;
    
    float sigma = std::stof( pars->find("sigma")->second, &sz);  
    cout<<"addnoise : sigma="<<sigma<<endl;
    
    srand((unsigned)time(NULL));
    for (int i=0; i<ns;++i){
        data[i] += float( rand()*(2*sigma)/RAND_MAX) -sigma;
    }
}
    
