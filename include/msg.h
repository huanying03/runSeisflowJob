#ifndef _MSG_H
#define _MSG_H
#include <stdio.h>
#include <iostream>
using namespace std;

extern "C"{
void msg(const char *msg);
void msg_str(const char *name, const char *str);
void msg_int(const char *name, const int value); 
void msg_float(const char *name, const float value);
void msg_double(const char *name,const  double value); 
void msg_array_double(const char *name,double *values,const  int count);
}// extern "C" for  dlsym
  
#endif 
