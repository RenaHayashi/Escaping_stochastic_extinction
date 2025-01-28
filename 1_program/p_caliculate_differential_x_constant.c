#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// メイン
int main(void){

// 変数・型宣言
  int i, j, T;
  double ft, dt;
  double p, pp, x, xx, tt;
  double lambda, b, bm, d, a;
  double e, ee, e2, domi, domi1;
  FILE *fp;

  // 書き込み
  fp=fopen("p_caliculate_differential_x_constant.csv","w");

// パラメーター
  lambda = 1*pow(10, -6);
  d = 1*pow(10, -12);
  b = 1*pow(10, -5);
  a = 1*pow(10, 1);
  
  ft = 10.0;
  T = 1000;
  dt = ft/T;
  
  // printf("dt = %f",dt);
  bm = 1.2*pow(10, -5);
  // p(t)の算出
  for (j = 0; j <= 4; j++){
    x = 1*pow(10, 5+0.5*j);
    p = 1;
    for ( i = 0; i <= T; i++){
      tt = dt*(T-i);
      fprintf(fp,"%f ,%f\n", tt, p);
      pp = p + (-p*p*bm*x + (bm*x - a)*p)*dt;

      p = pp;
      // printf("%f\n", p);
    }
  }
  
  fclose(fp);
  return 0;
}
