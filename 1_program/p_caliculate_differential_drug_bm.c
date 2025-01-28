#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// メイン
int main(void){

// 変数・型宣言
  int i, j, k, l, m, n, T;
  double ft, dt;
  double p, pp, xx, tt;
  double lambda, b, bm, d, a;
  double e, ee, e2, domi, domi1;
  double t[100001], x[100001], y[100001];
  FILE *fp, *fp1;
//データファイルの読み込み-配列格納(fp)
  fp=fopen("x_caliculate_drug.csv","r");
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
  // 読み込み確認
  printf("%f\n", t[500]);
  // 書き込み
  fp1=fopen("p_caliculate_differential_drug_bm.csv","w");

// パラメーター
  lambda = 5*pow(10, 4);
  d = 1*pow(10, 0);
  b = 2.5*pow(10, -4);
  a = 5*pow(10, 0);
  
  ft = 1000.0;
  n = 100000;
  dt = ft/n;
  T = 50000;
  printf("dt = %f",dt);

  bm = 0.98*b;
  // p(t)の算出
  p = 1;
  fprintf(fp1,"%f,%f\n", t[T], p);

  for ( i = 1; i <= T; i++){

    tt = t[T-i];
    xx = x[T-i];
    pp = p + (-p*p*bm*xx - (a - bm*xx)*p)*dt;

    p = pp;
    fprintf(fp1,"%f,%f\n", tt, p);
    // printf("%f\n", p);
  }
  
  fclose(fp1);
  return 0;
}
