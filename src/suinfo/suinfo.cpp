#include <suhead.h>
#include <sufile.h>
#include <msg.h>
using namespace std;

int main(int argc, char **argv){
    if (argc<2){
        msg("usage:\n suinfo <in.su>\n");
        return 0;
    }
    SuFile fin(argv[1]);
    int ns,ntr;
    fin.view(&ns,&ntr);
    
    msg("file information");
    msg_int("ns",ns);
    msg_int("ntr",ntr);
    return 0;
    
}