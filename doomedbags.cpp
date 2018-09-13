#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

float gete(int b, int l, float *memo, int bs){
  if(memo[bs*(l-1)+b-1]!=0) return memo[bs*(l-1)+b-1];
  float mine = FLT_MAX;
  float minp;
  if(b==1){
    mine=0;
    minp=0;
  }else{
    if(l==2) return b-1;
    for(int p=1;p<b;p++){
      int q=b-p;
      float rb=1.0f/(float)b;
      float e=(float)p*rb*(float)gete(p,l-1,memo, bs)
             +(float)q*rb*(float)gete(q,l  ,memo, bs)+1.0f;
      if(e<mine){//renew
        mine=e;
        minp=p;
      }
    }
  }
  memo[bs*(l-1)+b-1]=mine;
  return mine;
}

int main(int argc, char **argv){
  int B=10000L;
  int L=6;
  float *memo = (float*)malloc(sizeof(float)*B*L);
  memset(memo, 0, sizeof(float)*B*L);
  for(int l=2;l<=L;l++){
    printf("E(%d,%d)=%1.10f\n",B,l,gete(B,l,memo,B));
  }
  if(memo)free(memo);
  return EXIT_SUCCESS;
}

