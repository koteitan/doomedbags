#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

long double *makee(int B1, int L1){
  int bs=B1+1;
  long double *elist = (long double*)malloc(sizeof(long double)*(B1+1)*(L1+1));
  for(int l=2;l<=L1;l++) elist[1+l*bs]=0;
  for(int b=2;b<=B1;b++)
    elist[b+2*bs]=((long double)b-1.0f)/(long double)b*elist[b-1+2*bs]+1.0f;
  for(int l=3;l<=L1;l++){
    for(int b=2;b<=B1;b++){
      long double rb=1.0f/(long double)b;
      
      //ternary search
      int p0=1;
      int p1;
      int p2;
      int p3=b-1;
      while(p3-p0>10){
        p1=(p3-p0)/3;
        p2=p1*2;
        p1+=p0;
        p2+=p0;
//        printf("  %d,%d  %d,%d,%d,%d\n",b,l,p0,p1,p2,p3);
        int q1=b-p1;
        int q2=b-p2;
        long double e1=(long double)p1*rb*(long double)elist[p1+(l-1)*bs]
                      +(long double)q1*rb*(long double)elist[q1+(l  )*bs]+1.0f;
        long double e2=(long double)p2*rb*(long double)elist[p2+(l-1)*bs]
                      +(long double)q2*rb*(long double)elist[q2+(l  )*bs]+1.0f;
//        printf("e(%d,%d)=%1.10Lf, e(%d,%d)=%1.10Lf\n",p1,l-1,elist[p1+(l-1)*bs],q1,l,elist[q1+(l  )*bs]);
//        printf("e(%d,%d)=%1.10Lf, e(%d,%d)=%1.10Lf\n",p1,l-1,elist[p1+(l-1)*bs],q1,l,elist[q2+(l  )*bs]);
        if(e1<e2){ // e1 is smaller
          p3=p2;
        }else{ // e2 is smaller
          p0=p1;
        }
      }
      
      long double mine = FLT_MAX;
      for(int p=p0;p<=p3;p++){
        int q=b-p;
        long double e=(long double)p*rb*(long double)elist[p+(l-1)*bs]
                     +(long double)q*rb*(long double)elist[q+(l  )*bs]+1.0f;
//        printf("e(%d,%d)=%1.10Lf, e(%d,%d)=%1.10Lf\n",p,l-1,elist[p+(l-1)*bs],q,l,elist[q+(l  )*bs]);
        if(e<mine) mine=e;
      }//p
      elist[b+l*bs]=mine;
//        printf("-> e(%d,%d)=%1.10Lf\n",b,l,elist[b+l*bs]);
    }//b
  }//l
  return elist;
}

int main(int argc, char **argv){
  int B0=atoi(argv[1]);
  int L0=atoi(argv[2]);
  int B1=B0;
  int L1=L0;
  if(argc==5){
    B1=atoi(argv[3]);
    L1=atoi(argv[4]);
  }
  long double* elist=makee(B1,L1);
  for(int b=B0;b<=B1;b++){
    for(int l=L0;l<=L1;l++){
//      printf("E(%d,%d)=%1.10Lf\n",b,l,elist[b+l*(B1+1)]);
    }
  }
      int b=B1;int l=L1;
      printf("E(%d,%d)=%1.10Lf\n",b,l,elist[b+l*(B1+1)]);
  if(elist!=NULL)free(elist);
  return EXIT_SUCCESS;
}

