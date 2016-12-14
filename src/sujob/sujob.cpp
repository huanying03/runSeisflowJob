#include "suhead.h"
#include "sufile.h"
#include "msg.h"
#include "job.h"
#include <stdlib.h>
#include <assert.h>
#include <map>
#include <vector>
#include <dlfcn.h>//dlopen
#include "tinyxml2.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace tinyxml2;
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

bool init(vector<SFM> *sfms){
    
    //job_set(&sfms);
    
    typedef void(*pf_job)( vector< SFM > *);
    pf_job f_job ;
    
    void *handle=NULL;
    handle = dlopen("libjob.so",RTLD_LAZY);
    if (!handle){
        cout<<"Dlopen Error:"<<dlerror()<<endl;
        return false;
    }
    f_job =(pf_job)dlsym(handle, "job_set");
    char *errInfo;
    errInfo=dlerror();
    if (errInfo!=NULL){
        cout<<"Dlsym Error:"<<errInfo<<endl;
        return false;
    }
    f_job( sfms);
    return true;
}

void init_by_xml(vector< SFM >*sfms, const char *xml_file_name){ 
    msg("=============================================");
    msg("================================ init by xml ");
    msg("=============================================");
    msg_str("xml_file_name ",xml_file_name);
    XMLDocument  doc  ;
	doc.LoadFile( xml_file_name  );
	int errorID = doc.ErrorID();
	msg_int("errorID",errorID);
 
    SFM t;
    int count=0;
	for (const XMLNode *node=doc.FirstChild(); node; node=node->NextSibling()){
	       
        t.pars.clear();
        
	    t.name = node->ToElement()->Attribute( "name" ) ;
	    count++;
	    msg_int("--------------------------- NO. ",count);
	    msg_str( "Module name",t.name.c_str()); 
        
		for( const XMLNode* node2=node->ToElement()->FirstChild(); node2; node2=node2->NextSibling() ){
		    msg_str(node2->ToElement()->Attribute("name"),node2->ToElement()->GetText());
		    
            t.pars.insert(pair<string,string>(node2->ToElement()->Attribute("name"),node2->ToElement()->GetText()));
		}
        sfms->push_back(t);
	}
	
}

int main(int argc, char **argv){
     
    if (argc<2){
        msg("usage:\n sujob <job.xml>\n");
        return 0;
    } 
    
    // job 
    vector< SFM > sfms;
     
    init_by_xml(&sfms, argv[1]);
    //return 0; 
     
    /*
    msg("=============================================");
    msg("========================= information of job ");
    msg("=============================================");
    job_view(sfms);
    */
    //IO
    int sfms_count = sfms.size();
    SuFStream fin(sfms[0].pars.find("filename")->second.c_str());
    fin.open("r");
    SuFStream fout(sfms[sfms_count -1 ].pars.find("filename")->second.c_str());
    fout.open("w");
    
    msg("=============================================");
    msg("====================== information of infile ");
    msg("=============================================");
    int ns,ntr;
    fin.view(&ns,&ntr);  
    msg_int("ns",ns);
    msg_int("ntr",ntr); 
     
    //malloc
    float *d=(float*)calloc(ns,sizeof(float));
    assert(d!=NULL);
    SuHead hd;
    
    // SFM: dlopen  
    msg("=============================================");
    msg("================= loading SFM (uninclude IO) ");
    msg("=============================================");
    vector<pf_t> f;
    pf_t ft;
    if (sfms_count >2){
        for (int i=1; i<sfms_count-1; ++i){
            bool ok = sfm_load(&ft,sfms[i].name.c_str()); 
            if ( !ok) return 0; 
            f.push_back(ft);
        }
    }
    msg_int("sfm_load : Count",f.size());

    
    msg("=============================================");
    msg("===================== information of running ");
    msg("=============================================");
    //run 
    for (int i=0; i<ntr;++i){
        msg_int("trace",i+1);
        fin.read(d,&hd);
        for (int j=0; j<f.size(); ++j){
            f[j](&hd,d,ns,sfms[j+1].pars);
        }
        
        fout.write(d,hd,ns);
    }
    msg("=============================================");
    msg("====================== information of result ");
    msg("=============================================");
    msg_int("trace : totalCount",ntr);
    // free
    free(d);
    
   fin.close();
   fout.close();
    return 0;
    
}