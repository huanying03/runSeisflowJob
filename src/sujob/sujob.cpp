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

typedef void(*pf_t)(SuHead *,float*,int,map<string,string>);

bool sfm_load(pf_t *f,const char *name){
    void *handle=NULL;
    string lib_name="lib";
    lib_name.append(name);
    lib_name.append(".so");
    //libaddnoise.so
    cout<<"libname="<<lib_name<<endl;
    handle = dlopen(lib_name.c_str(),RTLD_LAZY);
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
    
    // SFM: dlopen  
    vector<pf_t> f;
    pf_t ft;
    if (sfms_count >2){
        for (int i=1; i<sfms_count-1; ++i){
            bool ok = sfm_load(&ft,sfms[i].name.c_str());//"addnoise");
            if ( !ok) return 0; 
            f.push_back(ft);
        }
    }
    cout<<"sfm_load, count="<< f.size()<<endl;

    
    //run 
    for (int i=0; i<ntr;++i){
        msg_int("read trace",i+1);
        fin.read(d,&hd);
        for (int j=0; j<f.size(); ++j){
            f[j](&hd,d,ns,sfms[j+1].pars);//f(hd,d,ns,sfms[1].pars);
        }
        
        fout.write(d,hd,ns);
    }
    // free
    free(d);
    
   fin.close();
   fout.close();
    return 0;
    
}