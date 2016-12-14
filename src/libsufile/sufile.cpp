#include "sufile.h"
/**********************************************************/
int SuFStream::view(int *ns, int *ntr)
{ 
    SuHead first;
    fread( (char *)&first, sizeof(SuHead), 1, stream); 
    *ns = first.ns ;  
    // get file size 
    fseek(stream, 0, SEEK_END);
    long filesize = ftell( stream);
    *ntr = filesize/  ( sizeof(SuHead) + sizeof(float)*first.ns); 
 fseek( stream, 0, SEEK_SET); 
    return 0; 
}
/**********************************************************/
int SuFStream::seek(long offset, int location)
{
    fseek( stream, offset, location); 
}
/**********************************************************/

int SuFStream::read(float  *d, SuHead *h )
{  
 fread(  h, sizeof(SuHead), 1, stream );     
 fread( d, sizeof(float), h->ns,stream );  
 return 0; 
}
/**********************************************************/

int SuFStream::read(float **d, SuHead *h, int ntr)
{ 
    for (int ix=0 ; ix< ntr; ix++)
    {  
 fread(  &h[ix], sizeof(SuHead), 1, stream );     
 fread( &d[ix][0], sizeof(float), h[ix].ns,stream ); 
    }  
    return 0; 
}

/**********************************************************/
int SuFStream::write(float *d, SuHead h, int ns)
{  
 h.ns=ns; 
 fwrite( &h, sizeof(SuHead), 1, stream);
 //msg("SuFStream::write(): ns",ns);
 fwrite( d, sizeof(float), ns  , stream ); 
    return 0; 
}
/**********************************************************/
int SuFStream::write(float **d, SuHead *h, int ns, int ntr)
{  
    for (int ix=0 ; ix< ntr ; ix++)
    {
 h[ix].ns=ns; 
 fwrite( &h[ix], sizeof(SuHead), 1, stream);
 fwrite( &d[ix][0], sizeof(float), ns  , stream ); 
    } 
    return 0; 
}

/**********************************************************/
/**********************************************************/
int SuFile::view(int *ns, int *ntr)
{
    FILE *sufile=fopen(sufn,"r");
    if (sufile==NULL)
    {
 perror("Can't open file\n"); 
 return 1; 
    }  
    SuHead first;
    fread( (char *)&first, sizeof(SuHead), 1, sufile); 
    *ns = first.ns ;  
    // get file size 
    fseek(sufile, 0, SEEK_END);
    long filesize = ftell(sufile);
    *ntr = filesize/  ( sizeof(SuHead) + sizeof(float)*first.ns);
    // file close 
    fclose( sufile ); 
    return 0; 
}
/**********************************************************/

int SuFile::read(float **d, SuHead *h, int ntr)
{
    FILE *rfile;
    rfile = fopen( sufn, "r");
    if ( rfile == NULL) 
    {
 perror("Can't open file\n");  
 return 1;
    }  
    for (int ix=0 ; ix< ntr; ix++)
    {  
 fread(  &h[ix], sizeof(SuHead), 1, rfile );     
 fread( &d[ix][0], sizeof(float), h[ix].ns, rfile ); 
    } 
    fclose( rfile ); 
    return 0; 
}

/**********************************************************/
int SuFile::write(float **d, SuHead *h, int ns, int ntr)
{ 
    FILE *sfile;
    sfile = fopen( sufn, "w");
    if ( sfile == NULL)
    { 
 perror("Can't open file\n");
 return 1; 
    } 
    for (int ix=0 ; ix< ntr ; ix++)
    {
 h[ix].ns=ns; 
 fwrite( &h[ix], sizeof(SuHead), 1, sfile);
 fwrite( &d[ix][0], sizeof(float), ns  , sfile ); 
    }
    fclose( sfile );
    return 0; 
}
