#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "MT.h"

int main(void){

  int i,j,l,m,n,p;
  int count,num;
  long int k;
  double tt, ttt;
  double lambda, b, bm, d, a;
  double ft, dt, tstart, kt;
  double t[100001], x[100001], y[100001];
  double ran,ran2;
  double z[10], zz[10];
  double e[14],ee[13];
  FILE *fp, *fp1;

//データファイルの読み込み-配列格納(fp)
  fp=fopen("x_caliculate.csv","r");
  if(fp==NULL){
    printf("ファイルオープン失敗\n");
    return -1;
  }

  for(i=0; i<=100000; i++){
    fscanf(fp, "%lf,%lf,%lf", &t[i], &x[i], &y[i] );    
  }
  fclose(fp);
  t[0] = 0;
  x[0] = 5*pow(10, 4);
  y[0] = 1*pow(10, 2);
  z[1] = 1;

  // パラメーター
  lambda = 5*pow(10, 4);
  d = 1*pow(10, 0);
  b = 2.5*pow(10, -4);
  bm = 1.2*b;
  a = 5*pow(10, 0);
  
  ft = 1000.0;
  n = 100000;
  dt = ft/n;

  init_genrand((unsigned)time(NULL));

  fp1=fopen("p_caliculate_direct.csv","w");
  for (p = 0; p <= 10; p++){
    tstart = p*0.5;
    kt = tstart*100;
    // fprintf(fp1,"%f",tstart);

    for (m = 1; m <= 100; m++){
      count = 0;
      for(j=1;j<=100;j++){
        z[1] = 1;

        for(k=kt;k<=2000000000000000;k++){

          num = k;

          e[1]=bm*x[num]*z[1]*dt;
          e[2]=a*z[1]*dt;
        
          ee[0]=0;
          ee[1]=e[1];
          ee[2]=e[1]+e[2];
          ee[3]=1;

          ran2=genrand_real1();

          if (ee[1]>1||ee[2]>1){

            tt = (k-1)/100;
            ran=genrand_real1();
            while(ran==0||ran==1){
              ran=genrand_real1();
            }
            ttt=tt+log(1/ran)/ee[2];
            tt=ttt;
            if (tt>ft){
              break;
            }
            num = tt*100;
            // printf("tt=%f, num=%d\n", tt, num);
            
            e[1]=bm*x[num]*z[1]*dt;
            e[2]=a*z[1]*dt;

            ee[1]=e[1];
            ee[2]=e[1]+e[2];

            ee[3] = e[1]+e[2];
            ee[1] = e[1]/ee[3];
            ee[2] = (e[1]+e[2])/ee[3];

            if(ee[0]<ran2&&ran2<=ee[1]){
              zz[1]=z[1]+1;
              z[1]=zz[1];
            }else if(ee[1]<ran2&&ran2<=ee[2]){
              zz[1]=z[1]-1;
              z[1]=zz[1];
            }
            // printf("z[1]=%f\n", z[1]);
          }else{
            if(ee[0]<ran2&&ran2<=ee[1]){
              zz[1]=z[1]+1;
              z[1]=zz[1];
            }else if(ee[1]<ran2&&ran2<=ee[2]){
              zz[1]=z[1]-1;
              z[1]=zz[1];
            }
            else if(ee[2]<ran2&&ran2<=ee[3]){
              // printf("z[1]=%f\n", z[1]);
            }
          }

          if(z[1]==0){
            break;
          }
          if(z[1]>=200){
            count += 1;
            break;
          }
          if(tt>500&&z[1]>=100){
            count += 1;
            break;
          }
        }//k

        // printf("mutant=%f, count=%d\n",z[1],count);

      }//j
      // printf("count=%d\n",count);
      fprintf(fp1,"%f,%d\n",tstart, count);
    }//m
    // fprintf(fp1,"\n");
  }//p
  fclose(fp1);
  return 0;
}
