#include "addnoise.h"
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

void addnoise(SuHead *hd,float *data,int ns,map<string,string> pars){
    std::string::size_type sz;
    
    float sigma = std::stof( pars.find("sigma")->second, &sz);  
    srand((unsigned)time(NULL));
    for (int i=0; i<ns;++i){
        data[i] += float( rand()*(2*sigma)/RAND_MAX) -sigma;
    }
}
    
