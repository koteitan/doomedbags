#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

/* *getStrategy_bestexp(slist,elist,B1,L1) makes:
  out:
    slist[b+l*(B1+1)] = number of bags in the servant room againt the problem (b,l).
    elist[b+l*(B1+1)] = expected value of days to find doom.
  in:
    b, l = index of bags and lives
    B1, L1 = max number of bags and lives */
void *getStrategy_bestexp(long double *slist,long double *elist, int B1, int L1){
  int bs=B1+1;
  elist = (long double*)malloc(sizeof(long double)*(B1+1)*(L1+1));
  slist = (long double*)malloc(sizeof(long double)*(B1+1)*(L1+1));
  for(int l=2;l<=L1;l++){
    int b=1; /* when bag is 1 */
    slist[b+l*bs]=0; /* no trial */
    elist[b+l*bs]=0; /* doom is found in zero day */
  }
  for(int b=2;b<=B1;b++){
    int l=2; /* when life is 2 */
    slist[b+l*bs]=1; /* try 1 bag */
    /* e = 0(=found) + (b-1)/b*e(b-1,l) (=not found) */
    elist[b+l*bs]=((long double)b-1.0f)/(long double)b*elist[b-1+l*bs]+1.0f;
  }
  for(int l=3;l<=L1;l++){
    for(int b=2;b<=B1;b++){
      long double rb=1.0f/(long double)b;
      
      //ternary search
      int p0=1;
      int p1;
      int p2;
      int p3=b-1;
      while(p3-p0>10){ /* until 10 bags */
        p1=(p3-p0)/3;
        p2=p1*2;
        p1+=p0;
        p2+=p0;
        int q1=b-p1; /* left bags */
        int q2=b-p2; /* left bags */
        long double e1=(long double)p1*rb*(long double)elist[p1+(l-1)*bs]
                      +(long double)q1*rb*(long double)elist[q1+(l  )*bs]+1.0f;
        long double e2=(long double)p2*rb*(long double)elist[p2+(l-1)*bs]
                      +(long double)q2*rb*(long double)elist[q2+(l  )*bs]+1.0f;
        if(e1<e2){ /* if e1 is smaller */
          p3=p2; /* update right boundary */
        }else{ /* if e2 is smaller */
          p0=p1; /* update left boundary */
        }
      }/*while*/
      
      /* normal search for left bags */
      long double mine = FLT_MAX;
      int minp;
      for(int p=p0;p<=p3;p++){
        int q=b-p; /* left bags */
        long double e=(long double)p*rb*(long double)elist[p+(l-1)*bs]
                     +(long double)q*rb*(long double)elist[q+(l  )*bs]+1.0f;
        if(e<mine){
          mine = e; 
          minp = p;
        }
      }/*for p*/
      slist[b+1*bs]=minp;
      elist[b+l*bs]=mine;
    }/*for b*/
  }/*for l*/
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
  long double* elist;
  int *slist;
  getStrategy_bestexp(slist,elist,B1,L1);
  for(int b=B0;b<=B1;b++){
    for(int l=L0;l<=L1;l++){
      printf("E(%d,%d)=%1.10Lf\n",b,l,elist[b+l*(B1+1)]);
    }
  }
//      int b=B1;int l=L1;
//      printf("E(%d,%d)=%1.10Lf\n",b,l,elist[b+l*(B1+1)]);
  if(elist!=NULL)free(elist);
  return EXIT_SUCCESS;
}

