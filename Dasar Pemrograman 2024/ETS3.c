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
int i, j;

void display(bool m[3][4])
{
    for(i = 0; i < 3; i++)
        for(j = 0; j < 4; j++)
            printf("%d", m[i][j]), printf(j == 3 ? "\n" : " ");
}

void get_grid(bool m[3][4])
{
    for(i = 0; i < 3; i++)
        for(j = 0; j < 4; j++)
            scanf("%d", &m[i][j]);
}

bool power_ok(bool m[3][4])
{
    for(i = 0; i < 3; i++)
        for(j = 0; j < 4; j++)
            if(!m[i][j])
                return false;
    return true;
}

void where_of(bool m[3][4])
{
    printf("Daya mati di sektor: ");
    for(i = 0; i < 3; i++)
        for(j = 0; j < 4; j++)
            if(!m[i][j]) printf("(%d,%d) ", i, j);
    printf("\n");
}

int main()
{
    bool m[3][4];
    printf("Masukan : \n"); 
    get_grid(m);

    printf("Tampilkan : \n");
    display(m);

    if(power_ok(m))
        printf("Daya menyala di seluruh jaringan.\n");
    else
        where_of(m);
    return 0;
}
