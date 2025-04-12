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



int main()
{
    char s[10001];
    do
    {
        fgets(s, 10000, stdin);
        if(s[0] == '.') break;
        ll i, n = strlen(s), sum = 0;
        for(i = 0; i < n - 1; i++) // Karakter titik dihitung
            sum += (int)s[i];
        //printf("%lld %lld\n", sum, (sum % 64)); <- Debug
        sum = (sum % 64) + (ll)' ';
        printf("checksum : %c\n", (char)sum);
    } while (s[0] != '.');
    return 0;
}
