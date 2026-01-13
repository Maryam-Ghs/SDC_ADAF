// test_saxpy.c
#include <stdio.h>
#include <cblas.h>

int main(void)
{
    const int n = 5;
    const float alpha = 2.0f;

    float x[5] = {1, 2, 3, 4, 5};
    float y[5] = {10, 20, 30, 40, 50};

    // y := alpha * x + y
    cblas_saxpy(n, alpha, x, 1, y, 1);

    printf("Result y:\n");
    for (int i = 0; i < n; ++i) {
        printf("y[%d] = %f\n", i, y[i]);
    }

    return 0;
}

