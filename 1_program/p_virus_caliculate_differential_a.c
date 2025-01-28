#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// メイン
int main(void){

// 変数・型宣言
  int i, j, k, l, m, n, T, TT;
  double ft, dt;
  double p, pp, xx, tt;
  double lambda, beta, betam, r, d, a;
  double e, ee, e2, domi, domi1;
  double t[160000], x[160000], y[160000];
  FILE *fp, *fp1;
//データファイルの読み込み-配列格納(fp)
  fp=fopen("x_virus_caliculate_a.csv","r");
  if(fp==NULL){
    printf("ファイルオープン失敗\n");
    return -1;
  }

  for(i=0; i<=150002; i++){
    fscanf(fp, "%lf,%lf,%lf", &t[i], &x[i], &y[i] );    
  }
  fclose(fp);
  t[0] = 0;
  x[0] = 5*pow(10, 4);
  y[0] = 1*pow(10, 2);
  // 読み込み確認
  // printf("%f\n", t[500]);
  // 書き込み
  fp1=fopen("p_virus_caliculate_differential_a.csv","w");

// パラメーター
  lambda = 5*pow(10, 4);
  d = 1*pow(10, 0);
  beta = 1*pow(10, -4);
  r = 2.5*pow(10, 0);
  // a = 5*pow(10, 0);
  betam = beta*1.2;
  
  ft = 1000.0;
  n = 50000;
  dt = ft/n;
  T = 50000;
  // printf("dt = %f",dt);
  for ( j = 0; j <= 2; j++){

    a = 5*pow(10, 0)*(1 + 0.2*(j-1));
    // p(t)の算出
    p = 1;
    T = 50000*(j+1) + j;
    fprintf(fp1,"%f,%f\n", t[T], p);

    for ( i = 1; i <= T; i++){
  
      tt = t[T-i];
      xx = x[T-i];
      pp = p + (r - r*exp(-betam*xx*p) - r*p - a*p)*dt;

      p = pp;
      fprintf(fp1,"%f,%f\n", tt, p);
    // printf("%f\n", p);
    }

  }
  
  fclose(fp1);
  return 0;
}
