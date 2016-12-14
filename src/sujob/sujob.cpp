#include <suhead.h>
#include <sufile.h>
#include <msg.h>
#include <stdlib.h>
#include <assert.h>
#include <map>
#include <vector>

using namespace std;


struct SFM{
    string name;
    map<string,string> pars;
};


int main(int argc, char **argv){
    /*
    if (argc<2){
        msg("usage:\n sujob <job.xml>\n");
        return 0;
    }
    */
    //  job.xml ->  vector< SFM >  sfm
    vector< SFM > sfms;
    SFM t;
    t.name ="suinput";
    t.pars.insert(pair<string,string>("filename","../../data/tmp.su")); 
    sfms.push_back(t);
    /*
    t.name ="sunorm";
    t.pars.clear();
    t.pars.insert(pair<string,string>("factor","1.0"));
    t.pars.insert(pair<string,string>("direction","0"));
    ms.push_back(t);
    */
    t.pars.clear();
    t.name ="suoutput";
    t.pars.insert(pair<string,string>("filename","../../data/out.su")); 
    sfms.push_back(t);
    
    int sfms_count = sfms.size();
    cout<<"sfms.size()="<<sfms_count <<endl;
    
    map<string,string>::iterator it;
    for (int i=0; i<sfms_count; ++i){
        cout<<sfms[i].name<<":"<<endl;
        for (it =sfms[i].pars.begin(); it!=sfms[i].pars.end();++it){
            cout<<it->first<<"=>"<<it->second<<endl;
        }
    } 
    //
    
    SuFStream fin(sfms[0].pars.find("filename")->second.c_str());
    fin.open("r");
    //SuFile fin(sfms[0].pars.find("filename")->second.c_str());
    
    int ns,ntr;
    fin.view(&ns,&ntr);
    msg("file information");
    msg_int("ns",ns);
    msg_int("ntr",ntr);
    //return 0; 
     
    float *d=(float*)calloc(ns,sizeof(float));
    assert(d!=NULL);
    SuHead hd;
    
    //
    SuFStream fout(sfms[sfms_count -1 ].pars.find("filename")->second.c_str());
    fout.open("w");
    //
    for (int i=0; i<ntr;++i){
        msg_int("read trace",i+1);
        fin.read(d,&hd);
        fout.write(d,hd,ns);
    }
    // free
    free(d);
    
   fin.close();
   fout.close();
    return 0;
    
}