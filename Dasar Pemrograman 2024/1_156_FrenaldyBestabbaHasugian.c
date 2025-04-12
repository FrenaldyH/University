#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define dd double
#define ll long long
#define el printf("\n")
#define bgd(a) printf("%d ", a)
#define sizearray(a) (sizeof(a) / sizeof(a[0]))

/*
    int = d
    u = unsigned int
    hi = short
    hu = unsigned short
    ld = long
    lu = unsigned long
    lld = long long
    llu = unsigned long long
    f = float
    lf = double
*/

void rec(int x)
{
    double a = pow(( (2.0 * (dd)x + 1.0) / (2.0 * (dd)x - 1.0) ), (dd)x), b = exp((dd)1);
    if(fabs(a - b) < 1e-6)
    {
        printf("Nilai e dari fungsi pustaka : %0.7lf\nNilai e dari fungsi buatan : %0.7lf\nNilai x : %d\n", b, a, x);
    }
    else
    {
        //printf("%lf %lf\n", a, b); <- Debug 1
        return rec(x + 1);
    }
}

int main()
{
    //for(int i = 0; i < 10; i++) printf("%d = %lf\n", i, exp((dd)i)); <- Debug 2
    rec(1);
    return 0;
}