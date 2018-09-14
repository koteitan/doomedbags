#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

float gete(int b, int l, float *memo, int bs){
  if(memo[bs*(l-1)+b-1]!=0) return memo[bs*(l-1)+b-1];
  float mine = FLT_MAX;
  if(b==1){
    mine=0;
  }else{
    if(l==2){
      return ((float)b-1.0f)/(float)b*gete(b-1, 2, memo, bs)+1.0f;
    }
    float rb=1.0f/(float)b;
    int p0=1;
    int p1;
    int p2;
    int p3=b;
    int eps=10;
    while(p3-p0>eps){
      p1=(p3-p0)/3;
      p2=(p3-p0)/3;
      p1+=p0;
      p2+=p0;
      int q1=b-p1;
      int q2=b-p2;
      float e1=(float)p1*rb*(float)gete(p1,l-1,memo, bs)
              +(float)q1*rb*(float)gete(q1,l  ,memo, bs)+1.0f;
      float e2=(float)p2*rb*(float)gete(p2,l-1,memo, bs)
              +(float)q2*rb*(float)gete(q2,l  ,memo, bs)+1.0f;
      if(e1<e2){ // e1 is smaller
        p3=p2;
      }else{ // e2 is smaller
        p0=p1;
      }
    }
    for(int p=p0;p<p3;p++){
      int q=b-p;
      float e=(float)p*rb*(float)gete(p,l-1,memo, bs)
             +(float)q*rb*(float)gete(q,l  ,memo, bs)+1.0f;
      if(e<mine) mine=e;
    }
  }
  memo[bs*(l-1)+b-1]=mine;
  return mine;
}

int main(int argc, char **argv){
  int B=atoi(argv[1]);
  int L=atoi(argv[2]);
  float *memo = (float*)malloc(sizeof(float)*B*L);
  memset(memo, 0, sizeof(float)*B*L);
  for(int b=1;b<=B;b++){
    for(int l=2;l<=L;l++){
      printf("E(%d,%d)=%1.10f\n",b,l,gete(b,l,memo,B));
    }
  }
  if(memo)free(memo);
  return EXIT_SUCCESS;
}

