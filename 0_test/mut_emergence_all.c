#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "MT.h"

int BinarySearch(double *vals, int size, double target) {
    int start = 0;
    int end = size - 1;
    int mid;

    if (target < vals[start] || target > vals[end]) {
        return -1;
    }

    while (start <= end) {
        mid = (start + end) / 2;
        if (mid == (start+1) && (target >= vals[start]) && (target < vals[mid])) {
            return start;
        } else if (target < vals[mid]) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    if (end < start) {
        return end;
    }
    return start;
}

int main(void){

// 変数・型宣言
  int i,i1,i2,i3,i4,j,jj,l,l1,l2,l3,l4,n,m,m1,m2,p,p1,p2,a,a1,b,c,y,z;
  int num_mut, num_mut2,ev,ev2,sho,count,count1,drug_mut,drug_mut2,drug_mut3,non_mut,non_mut2,non_mut3;
  int size, size1, bars_num, ee2_num, ee2_num2, full, mut, mut_incre;
  long int k;
  int sum_mut_virus, sum_drug_virus,max_drug, sum_max_drug,sum_drug_mut, sum_full, sum_mut;
  double rate_mut_virus, max_rate_mut_virus, sum_rate_mut_virus;
  double average_drug_mut, average_rate_mut_virus, average_max_drug, average_full, average_mut;
  double t,tt, ev_rate, ev_rate2;
  double tc,betaw,betam,gammaw,gammam,deltaw,deltam,myu,myu2,genome,genome2,epsilon,zeta,rate;
  double x[100000],xx[100000],e[200000],e2[0],ee[200000], ee2[150000];
  double bars[200010];
  double ran,ran2,probability;
  FILE *fp;
  // fp=fopen("emergence_t=4_rate1_heatmap.csv","w");
// パラメーター
  betaw = 3.68*pow(10, -6);
  betam = betaw;
  gammaw = 5.11;
  rate = 1;
  gammam = gammaw*rate;
  deltaw = 0.877;
  deltam = deltaw;
  tc = 1.33*pow(10,5);


// 枠の数
  y = 5;
  z = 50000;

  
  genome = 29903;
  genome2 = genome - 1;
  myu = 1*pow(10,-6);
  myu2 = 1 - myu;
  epsilon = genome*myu*(pow(myu2, genome2));

  bars[0] = 0;
  for (b = 1; b <= 9; b++){
    bars[b] = 0.09*b;
  }
  for (c = 0; c <= 200000; c++){
    bars[10+c] = 0.9 + 0.0000005*c;
  }
  
  size = sizeof(bars)/sizeof(bars[0]);
  // printf("%f\n", bars[5]);

//データの項目の記入(fp)
  // fprintf(fp,"Rate,Zeta,Probability\n");

//
  init_genrand((unsigned)time(NULL));
    a1 = 100;
    zeta = 0;
    count = 0;
    probability = 0;
   
  for (a = 1; a <= a1; a++){
  
    x[1]=1.33*pow(10,5);//標的細胞
    x[2]=20701;//野生型ウイルス
    //変異型ウイルス
    for (j=1; j <= z+7; j++) {
      jj=2+j;
      x[jj]=0;
    }
    // printf("%d", z);
    t=0;
    ev = 0;
    count = 0;
    count1 = 0;
    drug_mut = 0;
    drug_mut2 = 0;
    drug_mut3 = 0;

    max_drug = 0;
    non_mut = 0;
    non_mut2 = 0;
    non_mut3 = 0;

    num_mut = 0;//変異の回数
    num_mut2 = 0;
  
// 200000000000
    for(k=1;k<=400000000000;k++){

      e[1]=betaw*x[1]*x[2];
      e[2]=(1-zeta)*(gammaw/tc)*x[1]*x[2];
      e[3]=(1-zeta)*epsilon*(1/genome)*(gammaw/tc)*x[1]*x[2];
      e[4]=(1-zeta)*epsilon*(1-1/genome)*(gammaw/tc)*x[1]*x[2];
      e[5]=deltaw*x[2];
      e[0]=e[1]+e[2]+e[3]+e[4]+e[5];

     

      for (i = 1; i <= y; i++) {
        i1=2+i;
        i2=3*(i+1);
        i3=3*(i+1)+1;
        i4=3*(i+1)+2;

        e[i2]=betam*x[1]*x[i1];
        e[i3]=(gammam/tc)*x[1]*x[i1];
        e[i4]=deltam*x[l1];
        e2[0]=e[0] + e[i2] + e[i3] + e[i4] ;
        e[0]=e2[0];
      }
      // printf("%f", e[0]);
      for (l = 1; l <= z; l++) {
        l1=l+y+2;
        l2=3*(l1);
        l3=3*(l1)+1;
        l4=3*(l1)+2;

        e[l2]=betam*x[1]*x[l1];
        e[l3]=(1-zeta)*(gammam/tc)*x[1]*x[l1];
        e[l4]=deltam*x[l1];
        e2[0]=e[0] + e[l2] + e[l3] + e[l4] ;
        e[0]=e2[0];
      }

        ee[0]=0;
        ee2[0]=0;

      m1 =3*(z+5)+5;

      for (m = 1; m <= m1; m++) {
        ee[m]=e[m]/e[0];
        ee2[m] = ee[m] + ee2[m-1];
      }


      ran=genrand_real1();
      while(ran==0||ran==1){
        ran=genrand_real1();
      }

      tt=t+log(1/ran)/e[0];
      t=tt;

      // 乱数が8等分のどこに近いか
      ran2=genrand_real1();

      bars_num = BinarySearch(bars, size, ran2);
      
      // 乱数が近かった等分に一番近いee2は何番か
      size1 = sizeof(ee2)/sizeof(ee2[0]);
      ee2_num = BinarySearch(ee2, size1, bars[bars_num]);
      ev_rate = ee2[ee2_num];

      // printf("bars_num = %d, %f, ee2_num = %d, %f\n", bars_num, bars[bars_num], ee2_num2, ee2[ee2_num2]);
      // printf("%d, %f\n", ee2_num, ev_rate);

      if (ev_rate >= ran2){
        for ( p = 0; p <=1000000 ; p++){
          ee2_num2 = ee2_num - 1;
          ev_rate = ee2[ee2_num2];
          // printf("%d, %f, %f\n", ee2_num2, ee[ee2_num2], ev_rate);
          ee2_num = ee2_num2;

          if (ev_rate < ran2){
            ee2_num2 = ee2_num + 1;
            n = ee2_num2;
            // printf("n = %d, %f, ran2 = %f\n", n, ee2[n], ran2);
            break;
          }

        }
      }else{
        // n=1;
        for ( p = 1; p <=1000000 ; p++){
          ee2_num2 = ee2_num + 1;
          ev_rate = ee2[ee2_num2];
          ee2_num = ee2_num2;
          // printf("%d, %f, %f\n", ee2_num, ee2[ee2_num], ev_rate);

          if (ev_rate > ran2){
            n = ee2_num2;
            // printf("n = %d, %f, ran2 = %f\n", n, ee2[n], ran2);
            break;
          }

        }
      }
    
      if (n==1){
        xx[1]=x[1]-1;
        x[1]=xx[1];
      }
      else if (n==2){
        xx[2]=x[2]+1;
        x[2]=xx[2];
      }
      else if (n==3){
        num_mut2 = num_mut +1;//変異の回数のカウント
        drug_mut2 = drug_mut +1;
        drug_mut3 = drug_mut2 +2;//x[]の何番目か（1,2が標的細胞と野生型ウイルスであるため）
        xx[2]=x[2]-1;
        x[2]=xx[2];
        xx[drug_mut3]=x[drug_mut3]+1;
        x[drug_mut3]=xx[drug_mut3];
        num_mut = num_mut2;
        drug_mut = drug_mut2;
      }
      else if (n==4){
        num_mut2 = num_mut +1;//変異の回数のカウント
        non_mut2 = non_mut +1;
        non_mut3 = non_mut2 + y + 2;//x[]の何番目か（1,2が標的細胞と野生型ウイルスであるため）
        xx[2]=x[2]-1;
        x[2]=xx[2];
        // xx[non_mut3]=x[non_mut3]+1;
        // x[non_mut3]=xx[non_mut3];
        num_mut = num_mut2;
        non_mut = non_mut2;
      }
      else if (n==5){
        xx[2]=x[2]-1;
        x[2]=xx[2];
      }
      else if (n>=6 && n%3==0){
        // xx[1]=x[1]-1;
        // x[1]=xx[1];
      }
      else if (n>=6 && n%3==1){ 
        // sho = 1 + n/3;
        // xx[sho]=x[sho]+1;
        // x[sho]=xx[sho];
        // mut_incre += 1;
      }
      else if (n>=6 && n%3==2){
        // sho = n/3;
        // xx[sho]=x[sho]-1;
        // x[sho]=xx[sho];
      }
      
      ev2 = ev + 1;
      ev = ev2;

      // printf("t = %f, ee[0] = %f, ran2 = %f, ee2[4] = %f, ee2[5] = %f\n", t, ee[0], ran2, ee2[4], ee2[5]);
      // printf("t = %f, n = %d, %f, ran2 = %f, bars[%d] = %f, ee2[%d]=%f\n", t, n, ee2[n], ran2, bars_num, bars[bars_num], ee2_num2, ee2[ee2_num2]);

      sum_mut_virus = 0;
      sum_drug_virus = 0;
      // ウイルス総数
      for ( p1 = 2; p1 <=y+z+1 ; p1++){
        sum_mut_virus += x[p1];
        if (p1 > 8 && x[p1 + 1] <= 0){
          break;
        }
      }
      // 変異型ウイルス総数, 変異型最大コピー数
      for ( p2 = 3; p2 <=y+2 ; p2++){
        sum_drug_virus += x[p2];
        if(max_drug < x[p2]){
          max_drug = x[p2];
        }
      }
      // 変異型ウイルスの割合
      rate_mut_virus = sum_drug_virus/sum_mut_virus;

      // ウイルス全体における変異型の最大割合
      if(max_rate_mut_virus < rate_mut_virus){
        max_rate_mut_virus = rate_mut_virus;
        // full = sum_mut_virus;
        // mut = sum_drug_virus;
      }

      if (10<t){
        max_rate_mut_virus*=100;

        // 侵入判断
        if(max_rate_mut_virus > 0.1){
          count += 1;
        }
        sum_drug_mut += drug_mut;
        sum_rate_mut_virus += max_rate_mut_virus;
        sum_max_drug += max_drug;
        sum_full += full;
        sum_mut += mut;
        printf("%d回目, 出現回数=%d, ウイルス総数=%d, 変異ウイルス最大コピー数=%d, 変異ウイルス最大割合=%f\n", a, drug_mut, sum_mut_virus, max_drug, max_rate_mut_virus);
        break;
      }
    }

    

  }
  average_drug_mut = sum_drug_mut/a1;
  probability = 100*count/a1;
  average_rate_mut_virus = sum_rate_mut_virus/a1;
  average_max_drug = sum_max_drug/a1;
  average_full = sum_full/a1;
  average_mut = sum_mut/a1;
  printf("rate = %f,zeta = %f, 変異出現回数 = %f, ウイルス総数平均=%f, 変異ウイルス数= %f, 侵入確率 = %f, ウイルス全体における変異型の最大割合 = %f, 変異型最大コピー数 = %f\n",rate,zeta,average_drug_mut,average_full,average_mut,probability,average_rate_mut_virus,average_max_drug);
  // printf("rate = %f,zeta = %f, Finish\n",rate,zeta);
  // fclose(fp);
  

  return 0;
}
