#include "job.h" 
#include <iostream>
using namespace std;

/* load define of SFM in job */
//  will: job.xml ->  vector< SFM >  sfms
//  now: set sfms
void job_set(vector< SFM > *sfms){
    SFM t;
    t.name ="suinput";
    t.pars.insert(pair<string,string>("filename","../../data/in.su")); 
    sfms->push_back(t);
    /*
    t.pars.clear();
    t.name ="sunorm";
    t.pars.insert(pair<string,string>("factor","1.0"));
    t.pars.insert(pair<string,string>("direction","0"));
    sfms->push_back(t);
    */
    t.pars.clear();
    t.name = "addnoise";
    t.pars.insert(pair<string,string>("sigma","1.0"));
    sfms->push_back(t);
    
    t.pars.clear();
    t.name ="suoutput";
    t.pars.insert(pair<string,string>("filename","../../data/out-add-noise-1.su")); 
    sfms->push_back(t);
}

 

void job_view(vector<SFM> sfms){
    
    int sfms_count = sfms.size();
    cout<<"sfms.size()="<<sfms_count <<endl;
    
    map<string,string>::iterator it;
    for (int i=0; i<sfms_count; ++i){
        cout<<sfms[i].name<<":"<<endl;
        for (it =sfms[i].pars.begin(); it!=sfms[i].pars.end();++it){
            cout<<it->first<<"=>"<<it->second<<endl;
        }
    } 
}
