#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "adad.h"
#include "adaf.h"

#define	ZERO	0.0f

void linear_regression(adaf_array x, adaf_array y, adad n, adaf *s_out, adaf *i_out, adaf *r_out) {
  adad i;
  adaf SX, SY, SXY, SXX, SYY, slope, intercept, corr;
  SX = ZERO;
  SY = ZERO;
  SXY = ZERO;
  SXX = ZERO;
  SYY = ZERO;
  // Calculate sums
  // printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "i", "x[i]", "y[i]", "SX", "SY", "SXY", "SXX", "SYY");
  for (i = 0; i < n; ++i) {
    SX += x[i];
    SY += y[i];
    SXY += x[i] * y[i];
    SXX += x[i] * x[i];
    SYY += y[i] * y[i];
    // printf("%d\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", i, x[i], y[i], SX, SY, SXY, SXX, SYY);
  }
  slope = (n * SXY - SX * SY) / (n * SXX - SX * SX);
  intercept = (SY - slope * SX) / n;
  corr = ( n*SXY - SX*SY ) / sqrtf( (n*SXX - SX*SX)*(n *SYY - SY*SY) );
  *s_out = slope;
  *i_out = intercept;
  *r_out = corr;
}

float rand01() {
  return random() * 4.656612e-10f;
}

int pain(int n) {
  float      *x_data, *y_data, A, B, E, corr, slope, intercept;
  int         i;
  n = 10;
  A = 1.0f;
  B = 2.0f;
  E = 0.2f;
  x_data = (float *) malloc(n * sizeof(float));
  y_data = (float *) malloc(n * sizeof(float));
  for (i=0; i<n; i++) {
    x_data[i] = rand01() - 0.5f;
    y_data[i] = A + B*x_data[i] + rand01()*E;
  }

  adad N = n;
  adaf S, I, C;
  adaf_array XA(x_data, n);
  adaf_array YA(y_data, n);

  linear_regression(XA, YA, N, &S, &I, &C);
  corr = C.val();
  slope = S.val();
  intercept = I.val();
  
  printf("Linear Regression Results: (rho=%.4f)\n", corr);
  printf("Slope (m): %.4f / %.4f\n", slope, B);
  printf("Intercept (b): %.4f / %.4f\n", intercept, A);
  return 0;
}
