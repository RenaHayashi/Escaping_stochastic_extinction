#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 関数定義
double exp_function(double b, double x, double a, double dt) {
  double e;
  e = (b*x - a)*dt;
  return e;
}

double domi_function(double b, double x, double e, double dt) {
  double domi;
  double ee;
  ee = -1*e;
  domi = (b*x*exp(e))*dt;
  return domi;
}

// メイン
int main(void){

// 変数・型宣言
  int i, j, k, l, m, n, ft, T;
  double min, max, tt, dt;
  double p;
  double lambda, b, bm, d, a;
  double e1, e2, ee1, ee2, domi, domi1;
  double t[100000], x[100000], y[100000];
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
  // 読み込み確認
  // printf("%f,%f,%f\n", t[35], x[35], y[35]);
  // 書き込み
  fp1=fopen("p_caliculate_integral.csv","w");

// パラメーター
  lambda = 5*pow(10, 4);
  d = 1*pow(10, 0);
  b = 2.5*pow(10, -4);
  a = 5*pow(10, 0);

  bm = 1.2*b;
  // ft = 1000.0;
  // n = 100000;
  // dt = ft/n;
  dt = 0.01;
  // printf("dt = %f",dt);
  // p(t)の時刻, 探索
  min = 0;
  T = 1000;
  max = 1000;

  for (m = min; m <= T; m++){
  // モデル
    e1 = 0;
    e2 = 0;
    domi = 0;
    domi1 = 0;
    p = 0;

    for ( k = m; k <= max; k++){
      e1 += (bm*x[k] - a + bm*x[k+1] - a)*dt/2;
      ee1 = -1*e1;
      e2 += (bm*x[k+1] - a + bm*x[k+2] - a)*dt/2;
      ee2 = -1*e2;

      domi += ( exp(ee1) + bm*x[k]*exp(ee1) + exp(ee2) + bm*x[k+1]*exp(ee2))*dt/2;
    }

    // p(t)算出確認
    // printf("domi = %f, ", domi);
    p = 1 / domi;
    // // p(t)算出確認
    // printf("p = %f\n", p);
    tt = m*dt;
    fprintf(fp1,"%f,%f\n", tt, p);
  
  }
  fclose(fp1);
  return 0;
}
