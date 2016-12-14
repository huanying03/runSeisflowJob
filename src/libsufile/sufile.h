#ifndef _SUFILE_H
#define _SUFILE_H

#include <stdio.h> 
#include <string.h>
#include "suhead.h"
#include "msg.h"
#define NL 256

class SuFStream
{
public :
 SuFStream(const char *fn){ strcpy( streamfn, fn ); }; 
~SuFStream(){};

public : 
 int open(const char *t){ stream=fopen(streamfn,t); if ( stream==NULL) {perror("can't open file\n"); return 1; } return 0; }
 int view(int *ns, int *ntr);// sufile -> ns, ntr 
 int seek( long offset, int location); 
int read(float *d,  SuHead *h);// sufile -> d[ns>=h.ns][ntr] 
int read(float **d,  SuHead *h, int ntr);// sufile -> d[ns>=h.ns][ntr] 
int write(float *d,  SuHead h, int ns); // d[ns]-> sufile
int write(float **d,  SuHead *h, int ns, int ntr); // d[ns][ntr] -> sufile
int close(){ fclose(stream);return 0; };  

private :
 char streamfn[NL];
FILE *stream; 
};



class SuFile
{
public :
SuFile(const char *fn){strcpy(sufn, fn );
};
~SuFile(){};

public :
 int view(int *ns, int *ntr);//  get ns, ntr from sufile
int read(float **d,  SuHead *h, int ntr);// sufile -> d[ns>=h.ns][ntr] 
int write(float **d,  SuHead *h, int ns, int ntr); // d[ns][ntr] -> sufile

private :
char sufn[NL];
};

#endif
