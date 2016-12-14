#include "suhead.h"
#include "sufile.h"
#include "msg.h"
#include "job.h"
#include <stdlib.h>
#include <assert.h>
#include <map>
#include <vector>
#include <dlfcn.h>//dlopen
using namespace std;

typedef void(*pf_t)(SuHead,float*,int,map<string,string>);

bool sfm_load(pf_t *f,const char *name){
    void *handle=NULL;
    
    handle = dlopen("libaddnoise.so",RTLD_LAZY);
    if (!handle){
        cout<<"Dlopen Error:"<<dlerror()<<endl;
        return false;
    }
    *f =(pf_t)dlsym(handle,name);//"addnoise");
    char *errInfo;
    errInfo=dlerror();
    if (errInfo!=NULL){
        cout<<"Dlsym Error:"<<errInfo<<endl;
        return false;
    }
    return true;
        
}
    
int main(int argc, char **argv){
    /*
    if (argc<2){
        msg("usage:\n sujob <job.xml>\n");
        return 0;
    }
    */
    
    vector< SFM > sfms;
    
    // job
    
    job_load(&sfms);
    job_view(sfms);
    
    //IO
    int sfms_count = sfms.size();
    SuFStream fin(sfms[0].pars.find("filename")->second.c_str());
    fin.open("r");
    SuFStream fout(sfms[sfms_count -1 ].pars.find("filename")->second.c_str());
    fout.open("w");
    
    int ns,ntr;
    fin.view(&ns,&ntr);
    msg("file information");
    msg_int("ns",ns);
    msg_int("ntr",ntr); 
     
    //malloc
    float *d=(float*)calloc(ns,sizeof(float));
    assert(d!=NULL);
    SuHead hd;
    
    // dlopen
    pf_t f;
    bool ok = sfm_load(&f,"addnoise");
    if ( !ok) return 0; 
    

    
    //run 
    for (int i=0; i<ntr;++i){
        msg_int("read trace",i+1);
        fin.read(d,&hd);
        //f(hd,d,ns,sfms[1].pars);
        fout.write(d,hd,ns);
    }
    // free
    free(d);
    
   fin.close();
   fout.close();
    return 0;
    
}