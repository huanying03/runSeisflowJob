#ifndef _ADDNOISE_H
#define _ADDNOISE_H

#include "suhead.h"
#include <map>
#include <string>
using namespace std;
extern "C"{
void addnoise(SuHead *hd,float *data,int ns,map<string,string> pars);
}
#endif