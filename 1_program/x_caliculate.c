#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(void){

// 変数・型宣言
  int i,n;
  double x, xx, y, yy, t, dt, ft;
  long double lambda, b, d, a;
  FILE *fp;
//データファイルの作成と項目の記入(fp)
  fp=fopen("x_caliculate.csv","w");
  // fprintf(fp,"t,x,y\n");
// パラメーター
  lambda = 5*pow(10, 4);
  d = 1*pow(10, 0);
  b = 2.5*pow(10, -4);
  a = 5*pow(10, 0);
  
  ft = 1000.0;
  n = 100000;
  dt = ft/n;
//初期値
  t = 0;
  x = 5*pow(10, 4);
  y = 1*pow(10, 2);
// 初期値記載
  fprintf(fp,"%f,%f,%f\n", t, x, y);
// モデル
  
  for ( i = 1; i <= n; i++){
    t = dt*i;
    xx = x + (lambda - d*x - b*x*y)*dt;
    yy = y + (b*x*y - a*y)*dt;

    x = xx;
    y = yy;
    fprintf(fp,"%f,%f,%f\n", t, x, y);
  }
  fclose(fp);
  return 0;
}
