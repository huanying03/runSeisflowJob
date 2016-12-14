#include "msg.h"
void msg(const char *msg)
{
    printf("%s\n",msg);
}
 
void msg_str(const char *name, char *str)
{
    printf("%s = %s \n",name,str);
}

void msg_int(const char *name, int value)
{
    printf("%s = %d \n",name ,  value ); 
}

void msg_array_double(const char *name, double *values, int count)
{
    for (int i=0; i<count;i++)
 printf("%s[%2d]=%20.2lf\n",name,i,values[i]); 
}

void msg_float(const char *name, float value)
{
    printf("%s = %20.5f \n",name,value); 
}

void msg_double(const char *name, double value)
{
    printf("%s = %20.5lf \n",name,value ); 
} 
