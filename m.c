#include <stdio.h>
/*
lushuqin

workflow: m1+m2+m3
version 1.0 
*/
int m1(int *a){//  +1 
    static int i=0;
    i++;
    *a=i;
    if (i>5) 
        return -1;
    return 0;
}

void m2(int *b){//  + j*j
    static int j=1;
    j++;
    *b += j*10;
}
void m3(int *c){
    static int k=2;
    k++;
    *c += k*100;
}
    
int main(){
    int d=0;
    while (-1 !=m1(&d)){
        printf("m1:d=%d\n",d);
        m2(&d);
        printf("m2:d=%d\n",d);
        m3(&d);
        printf("m3:d=%d\n",d);
    }
    return 0; 
}
