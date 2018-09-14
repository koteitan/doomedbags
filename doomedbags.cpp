#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

long double gete(int b, int l, long double *memo, int bs){
  if(memo[bs*l+b]>=0.0f) return memo[bs*l+b];
  long double mine = FLT_MAX;
  if(b==1){
    mine=0;
  }else{
    long double rb=1.0f/(long double)b;
    if(l==2){
      mine=((long double)b-1.0f)*rb*gete(b-1, 2, memo, bs)+1.0f;
    }else{
      int p0=1;
      int p1;
      int p2;
      int p3=b;
      int eps=10;
      while(p3-p0>eps){
        p1=(p3-p0)/3;
        p2=p1*2;
        p1+=p0;
        p2+=p0;
        int q1=b-p1;
        int q2=b-p2;
        long double e1=(long double)p1*rb*(long double)gete(p1,l-1,memo, bs)
                      +(long double)q1*rb*(long double)gete(q1,l  ,memo, bs)+1.0f;
        long double e2=(long double)p2*rb*(long double)gete(p2,l-1,memo, bs)
                      +(long double)q2*rb*(long double)gete(q2,l  ,memo, bs)+1.0f;
        if(e1<e2){ // e1 is smaller
          p3=p2;
        }else{ // e2 is smaller
          p0=p1;
        }
      }
      for(int p=p0;p<=p3;p++){
        int q=b-p;
        long double e=(long double)p*rb*(long double)gete(p,l-1,memo, bs)
                     +(long double)q*rb*(long double)gete(q,l  ,memo, bs)+1.0f;
        if(e<mine) mine=e;
      }
    }
  }
  memo[bs*l+b]=mine;
  return mine;
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
  long double *memo = (long double*)malloc(sizeof(long double)*(B1+1)*(L1+1));
  for(int i=0;i<(B1+1)*(L1+1);i++){
    memo[i]=-1.0f;
  }
  for(int b=B0;b<=B1;b++){
    for(int l=L0;l<=L1;l++){
      printf("E(%d,%d)=%1.10Lf\n",b,l,gete(b,l,memo,B1+1));
      gete(b,l,memo,B1+1);
    }
  }
//  printf("E(%d,%d)=%1.10Lf\n",B1,L1,gete(B1,L1,memo,B1+1));
  if(memo!=NULL)free(memo);
  return EXIT_SUCCESS;
}

