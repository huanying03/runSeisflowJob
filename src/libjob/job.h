#ifndef _JOB_H
#define _JOB_H

#include <map>
#include <vector>
#include <string>
using namespace std;


/* define SFM */
typedef struct SFM{
    string name;
    map<string,string> pars;
};

/* load define of SFM in job */
//  will: job.xml ->  vector< SFM >  sfms
//  now: set sfms
void job_load(vector< SFM > *sfms);

void job_view(vector<SFM> sfms);

#endif