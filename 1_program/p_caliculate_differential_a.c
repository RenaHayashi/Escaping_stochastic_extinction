#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// メイン
int main(void){

// 変数・型宣言
  int i, j, k, n, T, TT;
  double ft, dt;
  double p, pp, xx, tt;
  double lambda, b, bm, d, a;
  double e, ee, e2, domi, domi1;
  double t[100000], x[100000], y[100000];
  FILE *fp, *fp1;
//データファイルの読み込み-配列格納(fp)
  fp=fopen("x_caliculate_a.csv","r");
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
  fp1=fopen("p_caliculate_differential_a.csv","w");

// パラメーター
  lambda = 5*pow(10, 4);
  d = 1*pow(10, 0);
  b = 2.5*pow(10, -4);
  // a = 5*pow(10, 0);
  
  ft = 1000.0;
  n = 100000;
  dt = ft/n;
  T = 10000;
  printf("dt = %f",dt);

  bm = 1.2*b;
  for ( k = 0; k <= 4; k++){
    a = 5*pow(10, 0)*pow(2, k-2);
    TT = 10000*(k+1) + k;
    // p(t)の算出
    p = 1;
    // fprintf(fp1,"%f,%f\n", t[T], p);

    for ( j = 0; j <= T; j++){

      tt = t[TT-j];
      xx = x[TT-j];
      pp = p + (-p*p*bm*xx - (a - bm*xx)*p)*dt;

      p = pp;
      fprintf(fp1,"%f,%f\n", tt, p);
      // printf("%f\n", p);
    }
  }
  fclose(fp1);
  return 0;
}
