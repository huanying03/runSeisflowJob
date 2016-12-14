#ifndef _MSG_H
#define _MSG_H
#include <stdio.h>
#include <iostream>
using namespace std;

extern "C"{
void msg(const char *msg);
void msg_str(const char *name, char *str);
void msg_int(const char *name, int value); 
void msg_float(const char *name, float value);
void msg_double(const char *name, double value); 
void msg_array_double(const char *name, double *values, int count);
}// extern "C" for  dlsym
  
#endif 
